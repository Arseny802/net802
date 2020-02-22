//
// Created by arseny on 04/02/2020.
//

#include "ClientHttps.h"

ClientHttps::ClientHttps() : BaseHttp() {

}

ClientHttps::~ClientHttps() = default;

HttpResultCodes ClientHttps::Read(std::string_view url, std::string_view app) {
  return StartReadingProcess(url, app);
}

std::string_view ClientHttps::GetProtocol() const noexcept {
  return "HTTPS";
}

std::string_view ClientHttps::GetProtocolVersion() const noexcept {
  return "1.0";
}

std::string_view ClientHttps::GetRequestType() const noexcept {
  return "GET";
}