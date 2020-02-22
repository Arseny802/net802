//
// Created by arseny on 04/02/2020.
//

#ifndef HTTP_SUBMODULE_CLIENTHTTPS_H
#define HTTP_SUBMODULE_CLIENTHTTPS_H

#include "Base/BaseHttp.h"

class ClientHttps : public BaseHttp {
 public:
  ClientHttps();
  void Read(std::string_view url, std::string_view app) override;
  [[nodiscard]] std::string_view GetProtocol() const override;
  [[nodiscard]] std::string_view GetProtocolVersion() const override;
  [[nodiscard]] std::string_view GetRequestType() const override;
 protected:
  ~ClientHttps() override;
};

#endif //HTTP_SUBMODULE_CLIENTHTTPS_H
