#pragma once
#include <vector>
#include <verita/Basic/Log/Log.hpp>
#include <string>

namespace verita{
class Logger{
private:
  Logger(){

  }
  ~Logger(){

  }
  std::vector<Log> logs;
  bool debug = false;

  void dump_log(Log& log);

public:
  void report(LogType type, const std::vector<std::string>& values);
  void dump_all_logs();
  void dump_logs();

  void enable_debug_logs(){
    debug = true;
  }

  static Logger& getInstance(){
    static Logger instance;
    return instance;
  }
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;
};
}
