#ifndef _BATTLESHIP_DEFENSIVE_ACTOR_
#define _BATTLESHIP_DEFENSIVE_ACTOR_

#include <array>

namespace caf {
  class event_based_actor;
  class actor_config;
  class behavior;
};


namespace battleship {

const int GIRD_SIZE = 8;

using defense_atom = caf::atom_constant<caf::atom("defense")>;

// TODO
class defensive_actor : public caf::event_based_actor {
  // represents the board with ships presence
  // false -> no ships
  // true -> ship present
  std::array<std::array<bool, GIRD_SIZE>, GIRD_SIZE> grid_;
public:
  explicit defensive_actor(caf::actor_config &config);
  caf::behavior make_behavior() override;
};

} // battleship

#endif //_BATTLESHIP_DEFENSIVE_ACTOR_