#include <sstream>
#include <vector>
#include "event.hpp"
#include "new_colony_event.hpp"
#include "../util/exception.hpp"

Event_ptr Event::from_string(std::string s)
{
  std::stringstream ss(s);
  std::string evname, args_raw;
  std::vector<std::string> args;

  getline(ss, evname, '(');
  getline(ss, args_raw, ',');

  ss.str(args_raw);

  for (std::string arg; getline(ss, arg, ',');){
    args.push_back(arg);
  }

  Event_ptr rv = nullptr;

  if (evname.compare("NewColonyEvent") == 0) {

    if (args.size() != 1) {
      throw ArgumentError(Formatter() << "Wrong number of arguments; expected 1, got " << args.size() << ".");
    }

    rv = NewColonyEvent::create(args[0]);

  }


  return rv;
}
