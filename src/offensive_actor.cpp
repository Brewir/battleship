
#include <caf/all.hpp>
#include <string>

#include "offensive_actor.h"
#include "defensive_actor.h"
#include "error.h"

using std::string;
using std::pair;
using namespace std::chrono_literals;

namespace battleship {

offensive_actor::offensive_actor(caf::actor_config &config)
  : caf::event_based_actor(config) {
}

bool offensive_actor::parse_target(const string& target, pair<int, int>& target_value)
{
  if (target.size() != 2) {
    return false;
  }
  // realign target to have index
  target_value.second = target.at(0) - 'A';
  target_value.first = target.at(1) - '1';

  // target should be in grid
  return target_value.first >= 0 && target_value.first < GIRD_SIZE &&
      target_value.second >= 0 && target_value.second < GIRD_SIZE;
}

caf::behavior offensive_actor::make_behavior() {
  return {
    [this](attack_atom, const string &target, caf::actor &defenser) -> caf::result<string> {
      pair<int, int> target_value;
      if (!parse_target(target, target_value)) {
        return input_error::wrong_input;
      }
      
      if (!history_.empty()) {
        history_ += "\n";
      }
      history_ += target + " ";

      // call defensive actor
      auto rp = this->make_response_promise<string>();
      this->request(defenser, 1s, defense_atom::value, target_value.first, target_value.second)
        .then([=](const string& result) mutable {
          history_ += result;
          rp.deliver(result);
        });
      return rp;
    },
    [this](history_atom) -> caf::result<string> {
      return history_;
    },
  };
}

} // battleship