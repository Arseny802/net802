//
// Created by arseny on 04/02/2020.
//

#include "ClientHttp.h"

ClientHttp::ClientHttp() : BaseHttp() {

}

ClientHttp::~ClientHttp() = default;

void ClientHttp::Read(std::string_view url, std::string_view app) {
  StartReadingProcess(url, app);
}

std::string_view ClientHttp::GetProtocol() const {
  return "HTTP";
}

std::string_view ClientHttp::GetProtocolVersion() const {
  return "1.0";
}

std::string_view ClientHttp::GetRequestType() const {
  return "GET";
}