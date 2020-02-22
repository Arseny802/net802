//
// Created by arseny on 22/02/2020.
//

#include "clients/BasicClientHttps.h"
#include "clients/BasicClientHttp.h"
#include "HttpClient.h"

namespace http {

HttpClient::HttpClient(bool tls) : _tls(tls) {
  SetTls(tls);
}

HttpClient::~HttpClient() = default;

void HttpClient::SetTls(bool tls) {
  _tls = tls;
  if (_tls) {
	_reader = std::make_shared<Http::Clients::BasicClientHttps>();
  } else {
	_reader = std::make_shared<Http::Clients::BasicClientHttp>();
  }
}

bool HttpClient::UsingTls() const noexcept {
  return _tls;
}

bool HttpClient::Read(std::string_view url, std::string_view app) {
  Base::HttpResultCodes result = _reader->Read(url, app);
  if (result == Base::HttpResultCodes::MovedWithNoLocation && !UsingTls()) {
	SetTls();
	return ParseAnswer(_reader->Read(url, app));
  } else if (result == Base::HttpResultCodes::Ok) {
	return true;
  }
  return false;
}

bool HttpClient::ParseAnswer(Base::HttpResultCodes code) const noexcept {
  switch (code) {
	case Base::HttpResultCodes::Ok: return true;
	case Base::HttpResultCodes::MovedWithNoLocation:
	case Base::HttpResultCodes::InvalidRequest_host:
	case Base::HttpResultCodes::ProcessingError:
	case Base::HttpResultCodes::ProcessingException:
	case Base::HttpResultCodes::ResponseError:
	case Base::HttpResultCodes::InvalidResponse:
	default: return false;
  }
}

}