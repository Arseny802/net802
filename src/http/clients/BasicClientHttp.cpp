//
// Created by arseny on 04/02/2020.
//

#include <base/BaseHttp.h>
#include <codes/HttpResultCodes.h>
#include <string_view>
#include <diagnostic/Diagnostics.h>
#include "BasicClientHttp.h"

namespace http::clients {

BasicClientHttp::BasicClientHttp() : BaseHttp() {
  diagnostics::Diagnostics::Initialize();
  spdlog::trace("BasicClientHttp::BasicClientHttp() called.");
}

BasicClientHttp::~BasicClientHttp() = default;

codes::HttpResultCodes BasicClientHttp::Read(std::string_view url) {
  spdlog::debug("BasicClientHttp::Read called. Url is '{}'.", url);
  return StartReadingProcess(url, std::string_view());
}

codes::HttpResultCodes BasicClientHttp::Read(std::string_view url, std::string_view app) {
  spdlog::debug("BasicClientHttp::Read called. Url is '{}'; app is '{}'.", url, app);
  return StartReadingProcess(url, app);
}

std::string_view BasicClientHttp::GetProtocol() const noexcept {
  return "HTTP";
}

std::string_view BasicClientHttp::GetProtocolVersion() const noexcept {
  return "1.0";
}

std::string_view BasicClientHttp::GetRequestType() const noexcept {
  return "GET";
}

}