#ifndef __SMTMBT__FSM_HPP_INCLUDED
#define __SMTMBT__FSM_HPP_INCLUDED

#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "solver_manager.hpp"
#include "solver_option.hpp"
#include "util.hpp"

/* -------------------------------------------------------------------------- */

#define SMTMBT_TRACE OstreamVoider() & FSM::TraceStream(d_smgr).stream()

#define SMTMBT_TRACE_RETURN \
  OstreamVoider() & FSM::TraceStream(d_smgr).stream() << "return "

/* -------------------------------------------------------------------------- */

namespace smtmbt {
class State;

class Action
{
 public:
  Action() = delete;
  Action(SolverManager& smgr, const std::string& id)
      : d_rng(smgr.get_rng()),
        d_solver(smgr.get_solver()),
        d_smgr(smgr),
        d_id(id)
  {
  }
  virtual ~Action()  = default;

  /* Execute the action. */
  virtual bool run() = 0;

  /**
   * Replay an action.
   *
   * Returns id of created object, if an object has been created, and 0
   * otherwise. Needed to be able to compare this id to the traced id in
   * the trace's return statement.
   */
  virtual uint64_t untrace(std::vector<std::string>& tokens) = 0;

  const std::string& get_id() const { return d_id; }

 protected:
  RNGenerator& d_rng;
  Solver& d_solver;
  SolverManager& d_smgr;

 private:
  std::string d_id;
};

/**
 * Transition from current state to next state without pre-conditions.
 */
class Transition : public Action
{
 public:
  Transition(SolverManager& smgr) : Action(smgr, "") {}
  bool run() override { return true; }
  uint64_t untrace(std::vector<std::string>& tokens) override { return 0; }
};

struct ActionTuple
{
  ActionTuple(Action* a, State* next) : d_action(a), d_next(next){};

  Action* d_action;
  State* d_next;
};

class State
{
  friend class FSM;

 public:
  /** Default constructor. */
  State() : d_id(""), d_is_final(false) {}
  /** Constructor. */
  State(std::string& id, std::function<bool(void)> fun, bool is_final)
      : d_id(id), d_is_final(is_final), f_precond(fun)
  {
  }

  /** Returns the identifier of this state. */
  const std::string& get_id() { return d_id; }
  /** Returns true if state is a final state. */
  bool is_final() { return d_is_final; }

  /** Runs actions associated with this state. */
  State* run(RNGenerator& rng);

  /**
   * Add action to this state.
   * action: The action to add.
   * weight: The weight of the action, determines the probability to choose
   *         running the action.
   * next  : The state to transition into after running the action. Optional,
   *         if not set, we stay in the current state.
   */
  void add_action(Action* action, uint32_t weight, State* next = nullptr);

 private:
  /* A unique string identifying the state. */
  std::string d_id;
  /* True if state is a final state. */
  bool d_is_final;
  /* A function defining the precondition for entering the state. */
  std::function<bool(void)> f_precond;
  /* The actions that can be performed in this state. */
  std::vector<ActionTuple> d_actions;
  /* The weights of the actions associated with this state. */
  std::vector<uint32_t> d_weights;
};

class FSM
{
 public:
  class TraceStream
  {
   public:
    TraceStream(SolverManager& smgr);
    ~TraceStream();
    TraceStream(const TraceStream& astream) = default;

    std::ostream& stream();

   private:
    void flush();
    SolverManager& d_smgr;
  };

  /** Constructor. */
  FSM(RNGenerator& rng,
      Solver* solver,
      std::ostream& trace,
      SolverOptions& options);

  /** Default constructor is disabled. */
  FSM() = delete;

  /**
   * Create and add a new state.
   * id      : A unique string identifying the state.
   * fun     : The precondition for transitioning to the next state.
   * is_final: True if this is the final state.
   */
  State* new_state(std::string id                = "",
                   std::function<bool(void)> fun = nullptr,
                   bool is_final                 = false);

  /** Create new action of given type T. */
  template <class T>
  T* new_action();

  /** Add given action to all configured states. */
  template <class T>
  void add_action_to_all_states(
      T* action,
      uint32_t weight,
      std::unordered_set<std::string> excluded_states = {});

  /** Set given state as initial state. */
  void set_init_state(State* init_state);
  /** Check configured states for unreachable states and infinite loops. */
  void check_states();
  /** Get state with given id. */
  State* get_state(const std::string& id);
  /** Run state machine. */
  void run();
  /** Configure state machine with base configuration. */
  void configure();
  /** Replay given trace. */
  void untrace(std::ifstream& trace);

 private:
  SolverManager d_smgr;
  RNGenerator& d_rng;
  std::vector<std::unique_ptr<State>> d_states;
  std::unordered_map<std::string, std::unique_ptr<Action>> d_actions;
  std::vector<std::tuple<Action*, uint32_t, std::unordered_set<std::string>>>
      d_actions_all_states;
  State* d_init_state = nullptr;
  State* d_cur_state  = nullptr;
};

template <class T>
T*
FSM::new_action()
{
  static_assert(std::is_base_of<Action, T>::value,
                "expected class (derived from) Action");
  T* action             = new T(d_smgr);
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

template <class T>
void
FSM::add_action_to_all_states(T* action,
                              uint32_t weight,
                              std::unordered_set<std::string> excluded_states)
{
  d_actions_all_states.push_back(
      std::tuple<Action*, uint32_t, std::unordered_set<std::string>>(
          action, weight, excluded_states));
}

}  // namespace smtmbt
#endif
