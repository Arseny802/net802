//
// Created by arseny on 22/02/2020.
//

#ifndef NETWORK_MODULES_SRC_BASEHTTP_HTTPCLIENT_H_
#define NETWORK_MODULES_SRC_BASEHTTP_HTTPCLIENT_H_

#include "base/IClientHttp.h"
#include <memory>

namespace http {
/// Real client
class HttpClient {
 public:
  ///
  /// \param tls
  explicit HttpClient(bool tls = false);
  ~HttpClient();
  ///
  /// \param url
  /// \param app
  /// \return
  bool Read(std::string_view url, std::string_view app = std::string_view());
  /// Change connection to secure / unsecured
  /// \param tls TLS over HTTP
  void SetTls(bool tls = true);
  /// Getter, using TLS over HTTP or not
  /// \return HTTPS / HTTP
  [[nodiscard]] bool UsingTls() const noexcept;
 protected:
  [[nodiscard]] bool ParseAnswer(codes::HttpResultCodes code) const noexcept;
 private:
  void InitializeClient();
  std::shared_ptr<base::IClientHttp> _reader;
  bool _tls;
};
}

#endif //NETWORK_MODULES_SRC_BASEHTTP_HTTPCLIENT_H_
