//
// Created by arseny on 22/02/2020.
//

#include <diagnostic/Diagnostics.h>
#include "clients/BasicClientHttps.h"
#include "clients/BasicClientHttp.h"
#include "HttpClient.h"

namespace http {

HttpClient::HttpClient(bool tls) : _tls(tls) {
  diagnostics::Diagnostics::Initialize();
  spdlog::debug("HttpClient::HttpClient called, tls is '{}'.", tls);
  InitializeClient();
}

HttpClient::~HttpClient() = default;

void HttpClient::SetTls(bool tls) {
  spdlog::trace("HttpClient::SetTls called, value is '{}'.", _tls);
  spdlog::debug("HttpClient::SetTls called, new value is '{}'.", tls);
  if (_tls != tls) {
    spdlog::trace("HttpClient::SetTls there is a new value.");
    _tls = tls;
    InitializeClient();
  } else {
    spdlog::debug("HttpClient::SetTls - value was not changed, no action.");
  }
}

void HttpClient::InitializeClient() {
  spdlog::trace("HttpClient::InitializeClient called, tls is '{}'.", _tls);
  if (_tls) {
	spdlog::info("HttpClient::SetTls TLS set. Creating BasicClientHttps.");
	_reader = ::std::make_shared<http::clients::BasicClientHttps>();
  } else {
	spdlog::info("HttpClient::SetTls TLS unset. Creating BasicClientHttp.");
	_reader = ::std::make_shared<http::clients::BasicClientHttp>();
  }
}

bool HttpClient::UsingTls() const noexcept {
  spdlog::trace("HttpClient::UsingTls called, value is '{}'.", _tls);
  return _tls;
}

bool HttpClient::Read(::std::string_view url, ::std::string_view app) {
  spdlog::info("HttpClient::Read called with url='{}'; app='{}'.", url, app);

  codes::HttpResultCodes result = _reader->Read(url, app);
  spdlog::debug("HttpClient::Read got {} code.", result);

  if (result == codes::HttpResultCodes::MovedWithNoLocation && !UsingTls()) {
	spdlog::info("HttpClient::Read result is MovedWithNoLocation, TLS is not using.");
	SetTls();
	return ParseAnswer(_reader->Read(url, app));
  } else if (result == codes::HttpResultCodes::Ok) {
	spdlog::info("HttpClient::Read result is MovedWithNoLocation, TLS is not using.");
	return true;
  }
  return false;
}

bool HttpClient::ParseAnswer(codes::HttpResultCodes code) const noexcept {
  spdlog::debug("HttpClient::ParseAnswer got {} code.", code);
  switch (code) {
	case codes::HttpResultCodes::Ok: return true;
	case codes::HttpResultCodes::MovedWithNoLocation:
	case codes::HttpResultCodes::InvalidRequest_host:
	case codes::HttpResultCodes::ProcessingError:
	case codes::HttpResultCodes::ProcessingException:
	case codes::HttpResultCodes::ResponseError:
	case codes::HttpResultCodes::InvalidResponse:
	default: return false;
  }
}

}