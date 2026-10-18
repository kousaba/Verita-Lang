#pragma once
#include <map>
#include <string>

namespace verita{
#define LOG_TYPE_LIST(X) \
  X(EMPTY, "{}") \
  X(DEBUG, "{}") \
  X(TEST_LOG, "TEST_LOG_MESSAGE") \
  // ...

#define DEFINE_ENUM(code, string) code,

enum class LogType{
  LOG_TYPE_LIST(DEFINE_ENUM)
};

#undef DEFINE_ENUM

class LogTypeManager{
public:
  std::string toString(LogType type);
  LogType fromString(const std::string& str);
private:
  LogTypeManager(){
    #define REGISTER_MAP(code, string) \
      enumToString[LogType::code] = string; \
      stringToEnum[string] = LogType::code;
    LOG_TYPE_LIST(REGISTER_MAP)
  }
public:
  static LogTypeManager& getInstance(){
    static LogTypeManager instance;
    return instance;
  }

  std::map<LogType, std::string> enumToString;
  std::map<std::string, LogType> stringToEnum;
};
#undef REGISTER_MAP
}
