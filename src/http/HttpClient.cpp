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
    _reader = std::make_shared<http::clients::BasicClientHttps>();
  } else {
    _reader = std::make_shared<http::clients::BasicClientHttp>();
  }
}

bool HttpClient::UsingTls() const noexcept {
  return _tls;
}

bool HttpClient::Read(::std::string_view url, ::std::string_view app) {
  base::HttpResultCodes result = _reader->Read(url, app);
  if (result == base::HttpResultCodes::MovedWithNoLocation && !UsingTls()) {
	SetTls();
	return ParseAnswer(_reader->Read(url, app));
  } else if (result == base::HttpResultCodes::Ok) {
	return true;
  }
  return false;
}

bool HttpClient::ParseAnswer(base::HttpResultCodes code) const noexcept {
  switch (code) {
	case base::HttpResultCodes::Ok: return true;
	case base::HttpResultCodes::MovedWithNoLocation:
	case base::HttpResultCodes::InvalidRequest_host:
	case base::HttpResultCodes::ProcessingError:
	case base::HttpResultCodes::ProcessingException:
	case base::HttpResultCodes::ResponseError:
	case base::HttpResultCodes::InvalidResponse:
	default: return false;
  }
}

}