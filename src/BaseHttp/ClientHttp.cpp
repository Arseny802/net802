//
// Created by arseny on 04/02/2020.
//

#include "ClientHttp.h"

ClientHttp::ClientHttp() : BaseHttp() {

}

ClientHttp::~ClientHttp() = default;

HttpResultCodes ClientHttp::Read(std::string_view url, std::string_view app) {
  return StartReadingProcess(url, app);
}

std::string_view ClientHttp::GetProtocol() const noexcept {
  return "HTTP";
}

std::string_view ClientHttp::GetProtocolVersion() const noexcept {
  return "1.0";
}

std::string_view ClientHttp::GetRequestType() const noexcept {
  return "GET";
}