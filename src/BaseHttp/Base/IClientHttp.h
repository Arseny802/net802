//
// Created by arseny on 22/02/2020.
//

#ifndef NETWORK_MODULES_SRC_BASEHTTP_BASE_ICLIENTHTTP_H_
#define NETWORK_MODULES_SRC_BASEHTTP_BASE_ICLIENTHTTP_H_

#include <string_view>
#include "src/http/codes/HttpResultCodes.h"

/// Interface
class IClientHttp {
 public:
  /// Send simple HTTP request to specified host,
  /// gets answer and forwards it for parsing.
  /// \param url host to connect.
  /// \return result code, contains error code.
  virtual HttpResultCodes Read(std::string_view url) = 0;
  /// Send simple HTTP request to specified host,
  /// gets answer and forwards it for parsing.
  /// \param url host to connect.
  /// \param app command, like "/app/request"
  /// \return result code, contains error code.
  virtual HttpResultCodes Read(std::string_view url, std::string_view app) = 0;
  /// Virtual getter for short protocol name (HTTP, HTTPS).
  /// \return string with a protocol name.
  [[nodiscard]] virtual std::string_view GetProtocol() const noexcept = 0;
  /// Virtual getter protocol version (1.0, 2.0).
  /// \return string with protocol version.
  [[nodiscard]] virtual std::string_view GetProtocolVersion() const noexcept = 0;
  /// Virtual getter for request type (POST, GET).
  /// \return string with request type.
  [[nodiscard]] virtual std::string_view GetRequestType() const noexcept = 0;
  /// Virtual getter for long protocol name (HTTP/1.0).
  /// Combines GetProtocol() and GetProtocolVersion().
  /// \return string with a protocol name.
  [[nodiscard]] virtual std::string GetSpecificProtocol() const noexcept = 0;
};

#endif //NETWORK_MODULES_SRC_BASEHTTP_BASE_ICLIENTHTTP_H_
