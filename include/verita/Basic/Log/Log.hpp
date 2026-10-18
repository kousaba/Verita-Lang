#pragma once
#include <verita/Basic/Log/LogType.hpp>
#include <string>
#include <vector>

namespace verita{
struct Log{
  LogType type;
  std::vector<std::string> values;
  bool dumped = false;
};
}
