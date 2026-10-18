#include <map>
#include <string>
#include <verita/Basic/Log/Logger.hpp>

namespace verita {
std::string LogTypeManager::toString(LogType type) {
  return enumToString.contains(type) ? enumToString[type]
                                     : "__VERITA_NOT_FOUND_";
}

LogType LogTypeManager::fromString(const std::string &str) {
  return stringToEnum.contains(str) ? stringToEnum[str] : LogType::EMPTY;
}
} // namespace verita
