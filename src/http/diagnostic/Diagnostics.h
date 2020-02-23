//
// Created by arseny on 23/02/2020.
//

#ifndef NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
#define NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_

#include <optional>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/spdlog.h"

namespace http::diagnostics {
///
class Diagnostics {
 public:
  ///
  static void Initialize();
  ///
  /// \return
  static spdlog::level::level_enum GetCurrentLogLevel() noexcept;
  ///
  /// \param new_level
  static void SetCurrentLogLevel(spdlog::level::level_enum new_level);
  ///
  /// \return
  static ::std::string_view GetCurrentLogPattern() noexcept;
  ///
  /// \param new_pattern
  static void SetCurrentLogPattern(::std::string new_pattern);
  /// Was Initialize() function called or not.
  static bool initialized;
 protected:
  ///
  const static ::std::string logger_name;
  ///
  const static ::std::string log_file_name;
  ///
  const static ::std::optional<std::string> date_format;
 private:
  static spdlog::level::level_enum current_level_;
  static ::std::string log_format_;
};
}

#endif //NETWORK_MODULES_SRC_HTTP_DIAGNOSTIC_DIAGNOSTICS_H_
