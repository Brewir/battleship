
#include <caf/all.hpp>
#include <string>
#include <chrono>
#include <random>


#include "defensive_actor.h"

using std::vector;
using std::string;

namespace battleship {
const int SHIP_NUMBER = 8;


defensive_actor::defensive_actor(caf::actor_config &config)
  : caf::event_based_actor(config) {

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::uniform_int_distribution<int> distribution_cols(0,5);
  std::uniform_int_distribution<int> distribution_rows(0,8);
  
  int placed_ships = 0;
  while (placed_ships < SHIP_NUMBER) {
    int row = distribution_rows(generator);
    int col = distribution_cols(generator);
    // don't place ship if overlap
    if (grid_[row][col] || grid_[row][col+1] || grid_[row][col+2]) {
      continue;
    }

    grid_[row][col] = true;
    grid_[row][col+1] = true;
    grid_[row][col+2] = true;
    ++placed_ships;
  }

}

caf::behavior defensive_actor::make_behavior() {
  return {
    [this](defense_atom, int row, int col) -> caf::result<string> {
      return grid_[row][col] ? "hit" : "miss";
    },
  };
}

} // battleship
