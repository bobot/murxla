#ifdef SMTMBT_USE_CVC4

#ifndef __SMTMBT__CVC4_SOLVER_H
#define __SMTMBT__CVC4_SOLVER_H

#include "solver.hpp"

#include "cvc4/api/cvc4cpp.h"

namespace smtmbt {
namespace cvc4 {

/* -------------------------------------------------------------------------- */
/* CVC4Sort                                                                   */
/* -------------------------------------------------------------------------- */

class CVC4Sort : public AbsSort
{
  friend class CVC4Solver;

 public:
  CVC4Sort(CVC4::api::Solver* cvc4, CVC4::api::Sort sort);
  ~CVC4Sort() override;
  size_t hash() const override;
  bool equals(const Sort& other) const override;
  bool is_bool() const override;
  bool is_bv() const override;
  uint32_t get_bv_size() const override;

 private:
  CVC4::api::Solver* d_solver;
  CVC4::api::Sort d_sort;
};

/* -------------------------------------------------------------------------- */
/* CVC4Term                                                                   */
/* -------------------------------------------------------------------------- */

class CVC4Term : public AbsTerm
{
  friend class CVC4Solver;

 public:
  CVC4Term(CVC4::api::Solver* cvc4, CVC4::api::Term d_term);
  ~CVC4Term() override;
  size_t hash() const override;
  bool equals(const Term& other) const override;

 private:
  CVC4::api::Solver* d_solver;
  CVC4::api::Term d_term;
};

/* -------------------------------------------------------------------------- */
/* CVC4Solver                                                                 */
/* -------------------------------------------------------------------------- */

class CVC4Solver : public Solver
{
 public:
  CVC4Solver(RNGenerator& rng) : Solver(rng), d_solver(nullptr) {}

  void new_solver() override;

  void delete_solver() override;

  bool is_initialized() const override;

  void set_opt(const std::string& opt, bool value) const
  {  // TODO:
  }

  Term mk_var(Sort sort, const std::string name) const
  {  // TODO:
    return nullptr;
  }
  Term mk_fun(Sort sort, const std::string name) const
  {  // TODO:
    return nullptr;
  }

  Term mk_value(Sort sort, bool value) const override;
  Term mk_value(Sort sort, uint64_t value) const override;
  Term mk_value(Sort sort, std::string value, Base base) const override;

  Sort mk_sort(const std::string name, uint32_t arity) const
  {  // TODO:
    return nullptr;
  }

  Sort mk_sort(SortKind kind) const override;
  Sort mk_sort(SortKind kind, uint32_t size) const override;

  Sort mk_sort(SortKind kind, std::vector<Sort>& sorts, Sort sort) const
  {  // TODO:
    return nullptr;
  }

  Term mk_const(Sort sort, const std::string name) const;
  Term mk_term(const OpKind& kind,
               std::vector<Term>& args,
               std::vector<uint32_t>& params) const override;

  Sort get_sort(Term term) const;

  void assert_formula(const Term& t) const
  {  // TODO:
  }

  Result check_sat() const
  {  // TODO:
    return Result::UNKNOWN;
  }

  //
  // get_model()
  // get_value()
  // get_proof()
  // get_unsat_core()
  //
  //
 private:
  void init_op_kinds();
  CVC4::api::Sort& get_cvc4_sort(Sort sort) const;
  CVC4::api::Term& get_cvc4_term(Term term) const;

  CVC4::api::Solver* d_solver;
  std::unordered_map<OpKind, CVC4::api::Kind, OpKindHashFunction> d_kinds;
  std::unordered_map<OpKind, CVC4::api::Kind, OpKindHashFunction> d_op_kinds;
};

}  // namespace btor
}  // namespace smtmbt

#endif

#endif

