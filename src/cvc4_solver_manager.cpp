#include "cvc4_solver_manager.hpp"

#include <cassert>
#include <iostream>

#include "util.hpp"

using namespace CVC4::api;

namespace smtmbt {
namespace cvc4 {

#if 0

/* -------------------------------------------------------------------------- */

////// Result
// TODO bool Result::operator==(const Result& r) const;
// TODO bool Result::operator!=(const Result& r) const;
// TODO std::string Result::getUnknownExplanation() const;
// TODO std::string Result::toString() const;
// TODO std::ostream& operator<<(std::ostream& out, const Result& r);

////// Sort
// bool Sort::operator==(const Sort& s) const;
// bool Sort::operator!=(const Sort& s) const;
// bool Sort::isNull() const;
// TODO void Sort::toStream(std::ostream& out) const;
// TODO std::string Sort:: toString() const;

////// Term
// bool Term::operator==(const Term& t) const;
// bool Term::operator!=(const Term& t) const;
// Kind Term::getKind() const;
// TODO std::string Term::toString() const;

//// Term::const_iterator
// TODO const_iterator& Term::const_iterator::operator=(const const_iterator&
// it);
// TODO bool Term::const_iterator::operator==(const const_iterator& it) const;
// TODO bool Term::const_iterator::operator!=(const const_iterator& it) const;
// TODO const_iterator& Term::const_iterator::operator++();
// TODO const_iterator Term::const_iterator::operator++(int);
// TODO Term Term::const_iterator::operator*() const;

// TODO const_iterator Term::begin() const;
// TODO const_iterator Term::end() const;

// TODO std::ostream& operator<<(std::ostream& out, const Term& t);
// TODO std::ostream& operator<<(std::ostream& out, const std::vector<Term>& vector);
// TODO std::ostream& operator<<(std::ostream& out, const std::set<Term>& set) ;
// TODO std::ostream& operator<<(std::ostream& out, const std::unordered_set<Term, TermHashFunction>& unordered_set);
// TODO template <typename V> std::ostream& operator<<(std::ostream& out, const std::map<Term, V>& map);
// TODO template <typename V> std::ostream& operator<<(std::ostream& out, const
// std::unordered_map<Term, V, TermHashFunction>& unordered_map);

//// Op
// TODO bool Op::operator==(const Op& t) const;
// TODO bool Op::operator!=(const Op& t) const;
// TODO Kind Op::getKind() const;
// TODO Sort Op::getSort() const;
// TODO bool Op::isNull() const;
// TODO bool Op::isIsIndexed() const;
// TODO template <typename T> T Op::getIndices() const;
// TODO std::string Op::toString() const;
// TODO std::ostream& Op::operator<<(std::ostream& out, const Op& t);



////// Solver

// Sort Solver::getNullSort() const;

// TODO Term Solver::mkVar(Sort sort, const std::string& symbol) const;

// TODO void Solver::echo(std::ostream& out, const std::string& str) const;
// TODO std::vector<Term> Solver::getAssertions() const;
// TODO std::vector<std::pair<Term, Term>> Solver::getAssignment() const;
// TODO std::string Solver::getInfo(const std::string& flag) const;
// TODO std::string Solver::getOption(const std::string& option) const;
// TODO std::vector<Term> Solver::getUnsatCore() const;
// TODO Term Solver::getValue(Term term) const;
// TODO std::vector<Term> Solver::getValue(const std::vector<Term>& terms) const;
// TODO void Solver::printModel(std::ostream& out) const;

// TODO void Solver::setInfo(const std::string& keyword, const std::string& value) const;
// TODO void Solver::setLogic(const std::string& logic) const;
// TODO Term Solver::ensureTermSort(const Term& t, const Sort& s) const;

/* -------------------------------------------------------------------------- */
/// not BV

// TODO bool Sort::isInteger() const;
// TODO bool Sort::isReal() const;
// TODO bool Sort::isString() const;
// TODO bool Sort::isRegExp() const;
// TODO bool Sort::isRoundingMode() const;
// TODO bool Sort::isFloatingPoint() const;
// TODO bool Sort::isDatatype() const;
// TODO bool Sort::isParametricDatatype() const;
// TODO bool Sort::isFunction() const;
// TODO bool Sort::isPredicate() const;
// TODO bool Sort::isTuple() const;
// TODO bool Sort::isRecord() const;
// TODO bool Sort::isArray() const;
// TODO bool Sort::isSet() const;
// TODO bool Sort::isUninterpretedSort() const;
// TODO bool Sort::isSortConstructor() const;
// TODO bool Sort::isFirstClass() const;
// TODO bool Sort::isFunctionLike() const;
// TODO Datatype Sort::getDatatype() const;
// TODO Sort Sort::instantiate(const std::vector<Sort>& params) const;
//// Function sort
// TODO size_t Sort:: getFunctionArity() const;
// TODO std::vector<Sort> Sort::getFunctionDomainSorts() const;
// TODO Sort Sort::getFunctionCodomainSort() const;

//// Array sort
// TODO Sort Sort::getArrayIndexSort() const;
// TODO Sort Sort::getArrayElementSort() const;

// Set sort
// TODO Sort Sort::getSetElementSort() const;

//// Uninterpreted sort
// TODO std::string Sort::getUninterpretedSortName() const;
// TODO bool Sort::isUninterpretedSortParameterized() const;
// TODO std::vector<Sort> Sort::getUninterpretedSortParamSorts() const;

// Sort constructor sort
// TODO std::string Sort::getSortConstructorName() const;
// TODO size_t Sort::getSortConstructorArity() const;
//// Floating-point sort
// TODO uint32_t Sort::getFPExponentSize() const;
// TODO uint32_t Sort::getFPSignificandSize() const;

//// Datatype sort
// TODO std::vector<Sort> Sort::getDatatypeParamSorts() const;
// TODO size_t Sort::getDatatypeArity() const;

//// Tuple sort
// TODO size_t Sort::getTupleLength() const;
// TODO std::vector<Sort> Sort::getTupleSorts() const;
// TODO std::ostream& operator<<(std::ostream& out, const Sort& s);

////// DatatypeSelectorDecl
// TODO std::string DatatypeSelectorDecl::toString() const;

////// DatatypeConstructorDecl
// TODO void DatatypeConstructorDecl::addSelector(const DatatypeSelectorDecl&
// stor);
// TODO std::string DatatypeConstructorDecl::toString() const;

////// DatatypeDecl
// TODO void DatatypeDecl::addConstructor(const DatatypeConstructorDecl& ctor);
// TODO size_t DatatyepDecl::getNumConstructors() const;
// TODO bool DatatypeDecl::isParametric() const;
// TODO std::string DatatypeDecl::toString() const;

////// DatatypeSelector
// TODO std::string DatatypeSelector::toString() const;

////// DatatypeConstructor
// TODO bool DatatypeConstructor::isResolved() const;
// TODO Term DatatypeConstructor::getConstructorTerm() const;
// TODO DatatypeSelector DatatypeConstructor::operator[](const std::string&
// name) const;
// TODO DatatypeSelector DatatypeConstructor::getSelector(const std::string&
// name) const;
// TODO Term DatatypeConstructor::getSelectorTerm(const std::string& name)
// const;
// TODO std::string DatatypeConstructor::toString() const;

////// DatatypeConstructor::const_iterator
// TODO const_iterator& DatatypeConstructor::const_iterator::operator=(const
// const_iterator& it);
// TODO bool DatatypeConstructor::const_iterator::operator==(const
// const_iterator& it) const;
// TODO bool DatatypeConstructor::const_iterator::operator!=(const
// const_iterator& it) const;
// TODO const_iterator& DatatypeConstructor::const_iterator::operator++();
// TODO const_iterator DatatypeConstructor::const_iterator::operator++(int);
// TODO const DatatypeSelector& DatatypeConstructor::const_iterator::operator*()
// const;
// TODO const DatatypeSelector*
// DatatypeConstructor::const_iterator::operator->() const;
// TODO const_iterator DatatypeConstructor::begin() const;
// TODO const_iterator DatatypeConstructor::end() const;

////// Datatype
// TODO DatatypeConstructor Datatype::operator[](size_t idx) const;
// TODO DatatypeConstructor Datatype::operator[](const std::string& name) const;
// TODO DatatypeConstructor Datatype::getConstructor(const std::string& name)
// const;
// TODO Term Datatype::getConstructorTerm(const std::string& name) const;
// TODO size_t Datatype::getNumConstructors() const;
// TODO bool Datatype::isParametric() const;
// TODO std::string Datatype::toString() const;

////// Datatype::const_iterator
// TODO const_iterator& Datatype::const_iterator::operator=(const
// const_iterator& it);
// TODO bool Datatype::const_iterator::operator==(const const_iterator& it)
// const;
// TODO bool Datatype::const_iterator::operator!=(const const_iterator& it)
// const;
// TODO const_iterator& Datatype::const_iterator::operator++();
// TODO const_iterator Datatype::const_iterator::operator++(int);
// TODO const DatatypeConstructor& Datatype::const_iterator::operator*() const;
// TODO const DatatypeConstructor* Datatype::const_iterator::operator->() const;

// TODO const_iterator Datatype::begin() const;
// TODO const_iterator Datatype::end() const;
// TODO std::ostream& operator<<(std::ostream& out, const DatatypeDecl& dtdecl);
// TODO std::ostream& operator<<(std::ostream& out, const
// DatatypeConstructorDecl& ctordecl);
// TODO std::ostream& operator<<(std::ostream& out, const DatatypeSelectorDecl&
// stordecl);
// TODO std::ostream& operator<<(std::ostream& out, const Datatype& dtype);
// TODO std::ostream& operator<<(std::ostream& out, const DatatypeConstructor&
// ctor);
// TODO std::ostream& operator<<(std::ostream& out, const DatatypeSelector&
// stor);

// Sort Solver::getIntegerSort() const;
// Sort Solver::getRealSort() const;
// Sort Solver::getRegExpSort() const;
// Sort Solver::getRoundingmodeSort() const;
// Sort Solver::getStringSort() const;

// TODO Sort Solver::mkArraySort(Sort indexSort, Sort elemSort) const;

// TODO Sort Solver::mkFloatingPointSort(uint32_t exp, uint32_t sig) const;
// TODO Sort Solver::mkDatatypeSort(DatatypeDecl dtypedecl) const;
// TODO Sort Solver::mkFunctionSort(Sort domain, Sort codomain) const;
// TODO Sort Solver::mkFunctionSort(const std::vector<Sort>& sorts, Sort codomain) const;
// TODO Sort Solver::mkParamSort(const std::string& symbol) const;
// TODO Sort Solver::mkPredicateSort(const std::vector<Sort>& sorts) const;
// TODO Sort Solver::mkRecordSort(const std::vector<std::pair<std::string, Sort>>& fields) const;
// TODO Sort Solver::mkSetSort(Sort elemSort) const;
// TODO Sort Solver::mkUninterpretedSort(const std::string& symbol) const;
// TODO Sort Solver::mkSortConstructorSort(const std::string& symbol, size_t arity) const;
// TODO Sort Solver::mkTupleSort(const std::vector<Sort>& sorts) const;

// TODO Term Solver::mkTuple(const std::vector<Sort>& sorts, const std::vector<Term>& terms) const;

// TODO Term Solver::mkPi() const;
// TODO Term Solver::mkReal(const char* s) const;
// TODO Term Solver::mkReal(const std::string& s) const;
// TODO Term Solver::mkReal(int32_t val) const;
// TODO Term Solver::mkReal(int64_t val) const;
// TODO Term Solver::mkReal(uint32_t val) const;
// TODO Term Solver::mkReal(uint64_t val) const;
// TODO Term Solver::mkReal(int32_t num, int32_t den) const;
// TODO Term Solver::mkReal(int64_t num, int64_t den) const;
// TODO Term Solver::mkReal(uint32_t num, uint32_t den) const;
// TODO Term Solver::mkReal(uint64_t num, uint64_t den) const;
// TODO Term Solver::mkRegexpEmpty() const;
// TODO Term Solver::mkRegexpSigma() const;
// TODO Term Solver::mkEmptySet(Sort s) const;
// TODO Term Solver::mkSepNil(Sort sort) const;
// TODO Term Solver::mkString(const char* s, bool useEscSequences = false) const;
// TODO Term Solver::mkString(const std::string& s, bool useEscSequences = false) const;
// TODO Term Solver::mkString(const unsigned char c) const;
// TODO Term Solver::mkString(const std::vector<unsigned>& s) const;
// TODO Term Solver::mkUniverseSet(Sort sort) const;

// TODO Op mkOp(Kind kind) const;
// TODO Op mkOp(Kind kind, Kind k) const;
// TODO Op mkOp(Kind kind, const std::string& arg) const;

// TODO Term Solver::mkPosInf(uint32_t exp, uint32_t sig) const;
// TODO Term Solver::mkNegInf(uint32_t exp, uint32_t sig) const;
// TODO Term Solver::mkNaN(uint32_t exp, uint32_t sig) const;
// TODO Term Solver::mkPosZero(uint32_t exp, uint32_t sig) const;
// TODO Term Solver::mkNegZero(uint32_t exp, uint32_t sig) const;
// TODO Term Solver::mkRoundingMode(RoundingMode rm) const;
// TODO Term Solver::mkUninterpretedConst(Sort sort, int32_t index) const;
// TODO Term Solver::mkAbstractValue(const std::string& index) const;
// TODO Term Solver::mkAbstractValue(uint64_t index) const;
// TODO Term Solver::mkFloatingPoint(uint32_t exp, uint32_t sig, Term val) const;
// TODO Sort Solver::declareDatatype( const std::string& symbol, const std::vector<DatatypeConstructorDecl>& ctors) const;
// TODO Term Solver::declareFun(const std::string& symbol, Sort sort) const;
// TODO Term Solver::declareFun(const std::string& symbol, const std::vector<Sort>& sorts, Sort sort) const;
// TODO Sort Solver::declareSort(const std::string& symbol, uint32_t arity) const;
// TODO Term Solver::defineFun(const std::string& symbol, const std::vector<Term>& bound_vars, Sort sort, Term term) const;
// TODO Term Solver::defineFun(Term fun, const std::vector<Term>& bound_vars, Term term) const;
// TODO Term Solver::defineFunRec(const std::string& symbol, const std::vector<Term>& bound_vars, Sort sort, Term term) const;
// TODO Term Solver::defineFunRec(Term fun, const std::vector<Term>& bound_vars, Term term) const;
// TODO void Solver::defineFunsRec(const std::vector<Term>& funs, const std::vector<std::vector<Term>>& bound_vars, const std::vector<Term>& terms) const;
#endif

}  // namespace cvc4
}  // namespace smtmbt
