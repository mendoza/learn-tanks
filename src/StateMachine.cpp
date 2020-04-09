#include <StateMachine.hpp>

namespace Skeleton {

void StateMachine::addState(StateRef newState, bool isReplacing) {
  this->isAdding = true;
  this->isReplacing = isReplacing;
  this->newState = std::move(newState);
}

void StateMachine::removeState() { this->isRemoving = true; }

void StateMachine::processStateChanges() {
  if (this->isRemoving && !this->_states.empty()) {
    this->_states.pop();
    if (!this->_states.empty()) {
      this->_states.top()->resume();
    }
    this->isRemoving = false;
  }

  if (this->isAdding) {
    if (!this->_states.empty()) {
      if (this->isReplacing) {
        this->_states.pop();
      } else {
        this->_states.top();
      }
    }

    this->_states.push(std::move(this->newState));
    this->_states.top()->init();
    this->isAdding = false;
  }
}

StateRef &StateMachine::getActiveState() { return this->_states.top(); }
}; // namespace Skeleton