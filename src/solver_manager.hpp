#ifndef __SMTMBT__SOLVER_MANAGER_H
#define __SMTMBT__SOLVER_MANAGER_H

#include <memory>
#include <unordered_map>

namespace smtmbt {

/* -------------------------------------------------------------------------- */

class Action
{
 public:
  Action() = delete;
  Action(const std::string& id) : d_id(id) {}
  virtual ~Action() = default;
  virtual void run() {}
  // virtual void untrace(const char* s) {}
  const std::string& get_id() const { return d_id; }

 private:
  std::string d_id;
};

/* -------------------------------------------------------------------------- */

template <typename TSolver,
          typename TTerm,
          typename TSort,
          typename THashTerm,
          typename THashSort>
class SolverManager
{
 public:
  using TermMap = std::unordered_map<TTerm, size_t, THashTerm>;

  SolverManager() : d_solver(nullptr), d_terms() {}
  // TODO: copy/assignment constructors?
  ~SolverManager() = default;

  void set_solver(TSolver s) { d_solver = s; }

  TSolver get_solver() { return d_solver; }

  void add_term(TTerm term)
  {
    TSort sort = get_sort(term);
    add_sort(sort);
    if (d_terms[sort].find(term) == d_terms[sort].end())
    {
      d_terms[sort].emplace(copy_term(term), 0);
    }
  }

  TTerm pick_term(/* TODO: TheoryId */) {}

  void add_sort(TSort sort)
  {
    if (d_terms.find(sort) == d_terms.end())
    {
      d_terms.emplace(copy_sort(sort), TermMap());
    }
  }

  TSort pick_sort(/* TODO: TheoryId */) {}

  template <class T>
  T* new_action()
  {
    static_assert(std::is_base_of<Action, T>::value,
                  "expected class (derived from) Action");
    T* action             = new T(this);
    const std::string& id = action->get_id();
    if (d_actions.find(id) == d_actions.end())
    {
      d_actions[id].reset(action);
    }
    else
    {
      delete action;
    }
    return static_cast<T*>(d_actions[id].get());
  }

 protected:
  /* Solver specific implementations. */
  virtual TTerm copy_term(TTerm term) { return term; }
  virtual TSort copy_sort(TSort sort) { return sort; }
  virtual TSort get_sort(TTerm term) = 0;

  TSolver d_solver;
  std::unordered_map<TSort, TermMap, THashSort> d_terms;
  std::unordered_map<std::string, std::unique_ptr<Action>> d_actions;
};

/* -------------------------------------------------------------------------- */

}  // namespace smtmbt
#endif
