#include <caf/all.hpp>
#include <iostream>

#include "defensive_actor.h"
#include "offensive_actor.h"
#include "error.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;

using namespace std::chrono_literals;

using namespace battleship;

namespace {

const int NB_PLAYERS = 2;

void caf_main(caf::actor_system &system, const caf::actor_system_config &) {
  int current_player = 0;

  std::array<caf::actor, NB_PLAYERS> offensive_actors;
  offensive_actors[0] = system.spawn<offensive_actor>();
  offensive_actors[1] = system.spawn<offensive_actor>();
  std::array<caf::actor, NB_PLAYERS> defensive_actors;
  defensive_actors[0] = system.spawn<defensive_actor>();
  defensive_actors[1] = system.spawn<defensive_actor>();

  caf::scoped_actor self{system};
  auto display_reply = [](const std::string &reply) { cout << reply << endl; };
  auto error_handler = [&](const caf::error &err) {
    cout << "*** Error received: " << system.render(err) << endl;
  };

  while (true) {
    cout << "command for player " << current_player + 1 << ": " << flush;
    std::string command;
    cin >> command;
    if (command == "quit") {
      break;
    } else if (command == "history") {
      self->request(offensive_actors[current_player], 1s, history_atom::value)
          .receive(display_reply, error_handler);
    } else {
      self->request(offensive_actors[current_player], 1s, attack_atom::value,
                  command, defensive_actors[(current_player + 1) % NB_PLAYERS])
          .receive(display_reply, error_handler);
      current_player = (current_player + 1) % NB_PLAYERS;
    }
  }
}

} // namespace

CAF_MAIN()