//
// Created by arseny on 31/01/2020.
//

#include <ClientHttps.h>
#include <ClientHttp.h>
#include "MoexReader.h"

MoexReader::MoexReader(bool tls) : _tls(tls)
{
	if (tls) _reader = std::make_shared<ClientHttps>();
	else  _reader = std::make_shared<ClientHttp>();
}

MoexReader::~MoexReader() = default;

void  MoexReader::SetTls(bool tls)
{
	if (_tls)_reader = std::make_shared<ClientHttp>();
	else  _reader = std::make_shared<ClientHttps>();
	_tls = tls;
}

bool MoexReader::UsingTls() const
{
	return _tls;
}

bool MoexReader::ReadSome() {
	_reader->Read("www.boost.org", "/LICENSE_1_0.txt");
	
	auto result = _reader->Read("www.moex.com");
	if (result == HttpResultCodes::MovedWithNoLocation) {
		SetTls();
		result = _reader->Read("www.moex.com");
	}
    return true;
}
