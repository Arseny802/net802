//
// Created by arseny on 04/02/2020.
//

#include <diagnostic/Diagnostics.h>
#include "codes/HttpResultCodes.h"
#include "BasicClientHttps.h"

namespace http::clients {

BasicClientHttps::BasicClientHttps() : BaseHttp() {
  diagnostics::Diagnostics::Initialize();
  spdlog::trace("BasicClientHttps::BasicClientHttps() called.");
}

BasicClientHttps::~BasicClientHttps() = default;

codes::HttpResultCodes BasicClientHttps::Read(std::string_view url) {
  spdlog::debug("BasicClientHttps::Read called. Url is '{}'.", url);
  return StartReadingProcess(url, std::string_view());
}

codes::HttpResultCodes BasicClientHttps::Read(std::string_view url, std::string_view app) {
  spdlog::debug("BasicClientHttps::Read called. Url is '{}'; app is '{}'.", url, app);
  return StartReadingProcess(url, app);
}

std::string_view BasicClientHttps::GetProtocol() const noexcept {
  return "HTTPS";
}

std::string_view BasicClientHttps::GetProtocolVersion() const noexcept {
  return "1.0";
}

std::string_view BasicClientHttps::GetRequestType() const noexcept {
  return "GET";
}

}