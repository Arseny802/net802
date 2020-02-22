//
// Created by arseny on 31/01/2020.
//

#include <src/BaseHttp/Clients/BasicClientHttps.h>
#include <src/BaseHttp/Clients/BasicClientHttp.h>
#include "MoexReader.h"

MoexReader::MoexReader() = default;

MoexReader::~MoexReader() = default;

bool MoexReader::GetInfo() {
  return _reader.Read("www.boost.org", "/LICENSE_1_0.txt");
}
