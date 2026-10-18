#include <iostream>
#include <vector>
#include <verita/Basic/Log/LogType.hpp>
#include <verita/Basic/Log/Logger.hpp>

namespace verita {
void Logger::report(LogType type, const std::vector<std::string> &formatter) {
  logs.push_back({type, formatter});
}

void Logger::dump_log(Log &log) {
  if (log.type == LogType::DEBUG && !debug)
    return;
  std::string text = LogTypeManager::getInstance().toString(log.type);
  std::vector<std::string> &args = log.values;

  size_t arg_idx = 0;
  size_t pos = 0;

  while (arg_idx < args.size() &&
         (pos = text.find("{}", pos)) != std::string::npos) {
    text.replace(pos, 2, args[arg_idx]);
    pos += args[arg_idx].length();
    arg_idx++;
  }
  log.dumped = true;
  std::cout << text << std::endl;
}
void Logger::dump_all_logs() {
  for (Log &log : logs) {
    dump_log(log);
  }
}
void Logger::dump_logs() {
  for (Log &log : logs) {
    if (!log.dumped) {
      dump_log(log);
    }
  }
}
} // namespace verita
