#ifndef __SMTMBT__OP_H
#define __SMTMBT__OP_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "theory.hpp"

namespace smtmbt {

enum OpKind
{
  UNDEFINED,
  DISTINCT,
  EQUAL,
  ITE,

  AND,
  OR,
  NOT,
  XOR,
  IMPLIES,

  BV_EXTRACT,
  BV_REPEAT,
  BV_ROTATE_LEFT,
  BV_ROTATE_RIGHT,
  BV_SIGN_EXTEND,
  BV_ZERO_EXTEND,

  BV_CONCAT,
  BV_AND,
  BV_OR,
  BV_XOR,
  BV_MULT,
  BV_ADD,
  BV_NOT,
  BV_NEG,
  BV_REDOR,
  BV_REDAND,
  BV_NAND,
  BV_NOR,
  BV_XNOR,
  BV_COMP,
  BV_SUB,
  BV_UDIV,
  BV_UREM,
  BV_SDIV,
  BV_SREM,
  BV_SMOD,
  BV_SHL,
  BV_LSHR,
  BV_ASHR,
  BV_ULT,
  BV_ULE,
  BV_UGT,
  BV_UGE,
  BV_SLT,
  BV_SLE,
  BV_SGT,
  BV_SGE,
};

std::ostream& operator<<(std::ostream& out, OpKind kind);

struct OpKindHashFunction
{
  size_t operator()(OpKind kind) const;
};

struct OpKindData
{
  OpKindData(OpKind kind,
             int32_t arity,
             uint32_t nparams,
             TheoryId theory_term,
             TheoryId theory_args)
      : d_kind(kind),
        d_arity(arity),
        d_nparams(nparams),
        d_theory_term(theory_term),
        d_theory_args(theory_args)
  {
  }

  bool operator==(const OpKindData& other) const;

  /* The Kind. */
  OpKind d_kind;
  /* The arity of this kind. */
  int32_t d_arity;
  /* The number of parameters if parameterized. */
  uint32_t d_nparams;
  /* The theory of a term of this kind. */
  TheoryId d_theory_term;
  /* The theory of the term arguments of this kind. */
  TheoryId d_theory_args;
};

#if 0
struct Op
{
  Op() : d_kind(OpKind::UNDEFINED), d_indices(){};
  Op(OpKind k, std::vector<uint32_t>& indices)
      : d_kind(k), d_indices(indices){};

  bool operator==(const Op& other) const
  {
    // TODO
    return false;
  }

  OpKind d_kind;
  std::vector<uint32_t> d_indices;

  //  /* The theory of a term of this kind. */
  //  TheoryId d_theory_term;
  //  /* The theory of the term arguments of this kind. */
  //  TheoryId d_theory_args;
};
#endif

using OpKindVector = std::vector<OpKind>;
using OpKindMap    = std::unordered_map<OpKind, OpKindData, OpKindHashFunction>;
using OpKinds      = std::unordered_map<TheoryId, OpKindVector>;

}  // namespace smtmbt

#endif
