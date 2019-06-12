#ifndef _BATTLESHIP_OFFENSIVE_ACTOR_
#define _BATTLESHIP_OFFENSIVE_ACTOR_

#include <string>

namespace caf {
  class event_based_actor;
  class actor_config;
  class behavior;
};


namespace battleship {

using attack_atom = caf::atom_constant<caf::atom("attack")>;
using history_atom = caf::atom_constant<caf::atom("history")>;

class offensive_actor : public caf::event_based_actor {
  std::string history_;
  bool parse_target(const std::string& target, std::pair<int, int>& target_value);
public:
  explicit offensive_actor(caf::actor_config &config);
  caf::behavior make_behavior() override;
};

} // battleship

#endif // _BATTLESHIP_OFFENSIVE_ACTOR_