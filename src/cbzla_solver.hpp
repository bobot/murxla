#ifdef SMTMBT_USE_CBITWUZLA

#ifndef __SMTMBT__CBITWUZLA_SOLVER_H
#define __SMTMBT__CBITWUZLA_SOLVER_H

#include "cbitwuzla/api/c/bitwuzla.h"
#include "fsm.hpp"
#include "solver.hpp"
#include "theory.hpp"

extern "C" {
struct Bitwuzla;
}

namespace smtmbt {
namespace bzla {

/* -------------------------------------------------------------------------- */
/* CBlzaSort                                                                  */
/* -------------------------------------------------------------------------- */

class CBzlaSort : public AbsSort
{
  friend class CBzlaSolver;

 public:
  CBzlaSort(Bitwuzla* bzla, BitwuzlaSort sort);
  ~CBzlaSort() override;
  size_t hash() const override;
  bool equals(const Sort& other) const override;
  bool is_array() const override;
  bool is_bool() const override;
  bool is_bv() const override;
  bool is_fp() const override;
  bool is_fun() const override;
  bool is_int() const override;
  bool is_real() const override;
  bool is_rm() const override;
  bool is_string() const override;
  bool is_reglan() const override;
  uint32_t get_bv_size() const override;
  uint32_t get_fp_exp_size() const override;
  uint32_t get_fp_sig_size() const override;

 private:
  Bzla* d_solver;
  BitwuzlaSort d_sort;
};

/* -------------------------------------------------------------------------- */
/* CBzlaTerm                                                                  */
/* -------------------------------------------------------------------------- */

class CBzlaTerm : public AbsTerm
{
  friend class CBzlaSolver;

 public:
  CBzlaTerm(Bzla* bzla, BitwuzlaTerm* term);
  ~CBzlaTerm() override;
  size_t hash() const override;
  bool equals(const Term& other) const override;
  bool is_array() const override;
  bool is_bool() const override;
  bool is_bv() const override;
  bool is_fp() const override;
  bool is_fun() const override;
  bool is_int() const override;
  bool is_real() const override;
  bool is_rm() const override;
  bool is_string() const override;
  bool is_reglan() const override;

 private:
  Bzla* d_solver        = nullptr;
  BitwuzlaTerm* d_term = nullptr;
};

/* -------------------------------------------------------------------------- */
/* CBzlaSolver                                                                */
/* -------------------------------------------------------------------------- */

class CBzlaSolver : public Solver
{
 public:
  ///** Solver-specific actions. */
  //static const OpKind ACTION_OPT_ITERATOR;
  //static const OpKind ACTION_BV_ASSIGNMENT;
  //static const OpKind ACTION_CLONE;
  //static const OpKind ACTION_FAILED;
  //static const OpKind ACTION_FIXATE_ASSUMPTIONS;
  //static const OpKind ACTION_RESET_ASSUMPTIONS;
  //static const OpKind ACTION_RELEASE_ALL;
  //static const OpKind ACTION_SIMPLIFY;
  //static const OpKind ACTION_SET_SAT_SOLVER;
  //static const OpKind ACTION_SET_SYMBOL;
  ///** Solver-specific operators. */
  //static const OpKind OP_DEC;
  //static const OpKind OP_INC;
  //static const OpKind OP_REDAND;
  //static const OpKind OP_REDOR;
  //static const OpKind OP_REDXOR;
  //static const OpKind OP_UADDO;
  //static const OpKind OP_UMULO;
  //static const OpKind OP_USUBO;
  //static const OpKind OP_SADDO;
  //static const OpKind OP_SDIVO;
  //static const OpKind OP_SMULO;
  //static const OpKind OP_SSUBO;
  ///* Solver-specific states. */
  //static const OpKind STATE_FIX_RESET_ASSUMPTIONS;

  /** Constructor. */
  CBzlaSolver(RNGenerator& rng) : Solver(rng), d_solver(nullptr) {}
  /** Destructor. */
  ~CBzlaSolver() override{};

  void new_solver() override;

  void delete_solver() override;

  Bzla* get_solver();

  bool is_initialized() const override;

  TheoryIdVector get_supported_theories() const override;
  OpKindSet get_unsupported_op_kinds() const override;
  SortKindSet get_unsupported_var_sort_kinds() const override;

  void configure_fsm(FSM* fsm) const override;
  void configure_smgr(SolverManager* smgr) const override;

  void set_opt(const std::string& opt, const std::string& value) override;

  std::vector<std::string> get_supported_sat_solvers();

  bool check_unsat_assumption(const Term& t) const override;

  std::string get_option_name_incremental() const override;
  std::string get_option_name_model_gen() const override;
  std::string get_option_name_unsat_assumptions() const override;

  bool option_incremental_enabled() const override;
  bool option_model_gen_enabled() const override;
  bool option_unsat_assumptions_enabled() const override;

  BitwuzlaTerm* get_bzla_term(Term term) const;

  Term mk_var(Sort sort, const std::string& name) override;

  Term mk_const(Sort sort, const std::string& name) override;

  Term mk_fun(Sort sort, const std::string& name) override
  {  // TODO:
    return nullptr;
  }

  Term mk_value(Sort sort, bool value) override;
  Term mk_value(Sort sort, std::string value, Base base) override;

  Term mk_special_value(Sort sort, const SpecialValueKind& value) override;

  Sort mk_sort(const std::string name, uint32_t arity) override
  {  // TODO:
    return nullptr;
  }

  Sort mk_sort(SortKind kind) override;
  Sort mk_sort(SortKind kind, uint32_t size) override;
  Sort mk_sort(SortKind kind, uint32_t esize, uint32_t ssize) override;
  Sort mk_sort(SortKind kind, const std::vector<Sort>& sorts) override;

  Term mk_term(const OpKind& kind,
               std::vector<Term>& args,
               std::vector<uint32_t>& params) override;

  Sort get_sort(Term term, SortKind sort_kind) const override;

  void assert_formula(const Term& t) override;

  Result check_sat() override;
  Result check_sat_assuming(std::vector<Term>& assumptions) override;

  std::vector<Term> get_unsat_assumptions() override;

  std::vector<Term> get_value(std::vector<Term>& terms) override;

  void push(uint32_t n_levels) override;
  void pop(uint32_t n_levels) override;

  void print_model() override;

  void reset_assertions() override;

  //
  // get_model()
  // get_proof()
  // get_unsat_core()
  //
  //
 private:
  using BzlaFunBoolUnary       = std::function<bool(Bzla*, BitwuzlaTerm*)>;
  using BzlaFunBoolUnaryVector = std::vector<BzlaFunBoolUnary>;

  void init_op_kinds();

  std::vector<Term> bzla_terms_to_terms(
      std::vector<BitwuzlaTerm*>& terms) const;
  std::vector<BitwuzlaTerm*> terms_to_bzla_terms(
      std::vector<Term>& terms) const;

  BzlaFunBoolUnary pick_fun_bool_unary(BzlaFunBoolUnaryVector& funs) const;
  BzlaFunBoolUnary pick_fun_is_bv_const() const;
  void check_is_bv_const(const SpecialValueKind& kind,
                         BitwuzlaTerm* node) const;

  BitwuzlaSort get_bzla_sort(Sort sort) const;
  BitwuzlaTerm* mk_value_bv_uint64 (Sort sort, uint64_t value);

  Bzla* d_solver;
  std::unordered_map<std::string, BzlaOption> d_option_name_to_enum;
  std::unordered_map<std::string, BitwuzlaKind> d_op_kinds;

  uint64_t d_num_symbols;
};

}  // namespace bzla
}  // namespace smtmbt

#endif

#endif