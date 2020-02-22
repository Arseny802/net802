//
// Created by arseny on 04/02/2020.
//

#include <base/BaseHttp.h>
#include <base/HttpResultCodes.h>
#include <string_view>
#include "BasicClientHttp.h"

namespace http::clients {

BasicClientHttp::BasicClientHttp() : BaseHttp() {

}

BasicClientHttp::~BasicClientHttp() = default;

base::HttpResultCodes BasicClientHttp::Read(std::string_view url) {
  return StartReadingProcess(url, std::string_view());
}

base::HttpResultCodes BasicClientHttp::Read(std::string_view url, std::string_view app) {
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