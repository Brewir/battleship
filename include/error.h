#ifndef _BATTLESHIP_ERROR_
#define _BATTLESHIP_ERROR_

namespace battleship {

enum class input_error : uint8_t {
  wrong_input = 1
};
caf::error make_error(input_error x);
std::string to_string(input_error x);

} // battleship

#endif // _BATTLESHIP_ERROR_