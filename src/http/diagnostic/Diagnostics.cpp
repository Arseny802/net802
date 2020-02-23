//
// Created by arseny on 23/02/2020.
//

#include "Diagnostics.h"

#include <utility>

namespace http::diagnostics {

bool Diagnostics::initialized = false;

spdlog::level::level_enum Diagnostics::current_level_ = spdlog::level::debug;
::std::string Diagnostics::log_format_ = "{} [%n] [%^---%L---%$] [thread %t] %v";

const ::std::string Diagnostics::logger_name = "http_logger";
const ::std::string Diagnostics::log_file_name = "logs/http";
const ::std::optional<std::string> Diagnostics::date_format = "[%H:%M:%S %z]";

void Diagnostics::Initialize() {
  if (initialized) {
    return;
  }

  ::std::vector<spdlog::sink_ptr> sinks;

  sinks.push_back(::std::make_shared<spdlog::sinks::stdout_sink_st>());
  sinks.push_back(::std::make_shared<spdlog::sinks::daily_file_sink_st>
      (log_file_name.data(), 0, 0, true, 14));

  auto combined_logger = std::make_shared<spdlog::logger>
      (logger_name.data(), begin(sinks), end(sinks));
  spdlog::register_logger(combined_logger);

  spdlog::set_level(current_level_);
  // change log pattern
  spdlog::set_pattern(fmt::format(log_format_.data(), date_format.value_or("")));
  spdlog::info("Initialized logger.");
  initialized = true;
}

spdlog::level::level_enum Diagnostics::GetCurrentLogLevel() noexcept {
  return current_level_;
}

void Diagnostics::SetCurrentLogLevel(spdlog::level::level_enum new_level) {
  current_level_ = new_level;
}

::std::string_view Diagnostics::GetCurrentLogPattern() noexcept {
  return log_format_;
}

void Diagnostics::SetCurrentLogPattern(::std::string new_pattern) {
  log_format_ = std::move(new_pattern);
}

void Example() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);
  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");
  spdlog::debug("This message should be displayed..");

  // define SPDLOG_ACTIVE_LEVEL to desired level
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");
}

}
