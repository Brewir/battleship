
#include <caf/all.hpp>
#include <string>

#include "error.h"

namespace battleship {

caf::error make_error(input_error x) {
  return {static_cast<uint8_t>(x), caf::atom("input")};
}

std::string to_string(input_error x) {
  switch (x) {
    case input_error::wrong_input:
      return "wrong_input";
    default:
      return "-unknown-error-";
  }
}

} // battleship