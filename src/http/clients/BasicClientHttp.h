//
// Created by arseny on 04/02/2020.
//

#ifndef HTTP_SUBMODULE_CLIENTHTTP_H
#define HTTP_SUBMODULE_CLIENTHTTP_H

#include "base/BaseHttp.h"

namespace http::clients {
class BasicClientHttp : public base::BaseHttp {
 public:
  BasicClientHttp();
  ~BasicClientHttp() override;
  codes::HttpResultCodes Read(std::string_view url) override;
  codes::HttpResultCodes Read(std::string_view url, std::string_view app) override;
  [[nodiscard]] std::string_view GetProtocol() const noexcept override;
  [[nodiscard]] std::string_view GetProtocolVersion() const noexcept override;
  [[nodiscard]] std::string_view GetRequestType() const noexcept override;
};
}

#endif //HTTP_SUBMODULE_CLIENTHTTP_H
