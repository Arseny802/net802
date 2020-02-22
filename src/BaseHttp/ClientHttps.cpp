//
// Created by arseny on 04/02/2020.
//

#include "ClientHttps.h"

ClientHttps::ClientHttps() : BaseHttp() {

}

ClientHttps::~ClientHttps() = default;

void ClientHttps::Read(std::string_view url, std::string_view app) {
  StartReadingProcess(url, app);
}

std::string_view ClientHttps::GetProtocol() const {
  return "HTTPS";
}

std::string_view ClientHttps::GetProtocolVersion() const {
  return "1.0";
}

std::string_view ClientHttps::GetRequestType() const {
  return "GET";
}