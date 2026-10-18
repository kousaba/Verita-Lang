#include <gtest/gtest.h>
#include <verita/Basic/Log/LogType.hpp>
#include <verita/Basic/Log/Logger.hpp>

TEST(LoggerTest, DumpLogsOutputsTestMsg) {
  auto &logger = verita::Logger::getInstance();

  testing::internal::CaptureStdout();

  logger.enable_debug_logs();
  logger.report(verita::LogType::DEBUG, {"TEST_MSG"});
  logger.dump_logs();

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("TEST_MSG"), std::string::npos)
      << "Expected 'TEST_MSG' in output, but got:\n"
      << output;
}
