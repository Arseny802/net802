//
// Created by arseny on 31/01/2020.
//

#ifndef HTTP_READER_HTTPREADER_H
#define HTTP_READER_HTTPREADER_H

#include <string>
#include <string_view>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include "HttpResultCodes.h"
#include "ErrorCode.h"
#include "IClientHttp.h"

using boost::asio::ip::tcp;

/// Abstract class for HTTP(S) requests.
/// Based on BOOST::ASIO system.
class BaseHttp : public IClientHttp {
public:
  /// Checks if passed string is valid URL.
  /// Doesn't grant that's a working URL!
  /// \param url - string to check
  /// \return valid or not
  static bool IsUrl(std::string_view url) noexcept;
  /// Base implementation of reading procedure.
  /// Just calls similar function with 'app' arg.
  /// \param url host to connect.
  /// \return result code, contains error code.
  HttpResultCodes Read(std::string_view url) override;
  /// Virtual getter for long protocol name (HTTP/1.0).
  /// Combines GetProtocol() and GetProtocolVersion().
  /// \return string with a protocol name.
  [[nodiscard]] std::string GetSpecificProtocol() const noexcept override;
protected:
  BaseHttp();
  virtual ~BaseHttp();
  /// Sends HTTP request by url with argument,
  /// prints server's output.
  /// \param url url to read
  /// \param app command, like "/app/request"
  /// \return Custom status code
  HttpResultCodes StartReadingProcess(std::string_view url, std::string_view app);
  /// Form the request. We specify the "Connection: close" header so that
  /// the server will close the socket after transmitting the response.
  /// This will allow us to treat all data up until the EOF as the content.
  /// \param url Url to connect, like "www.google.com"
  /// \param app Command, like "/app/request"
  /// \return Pointer to HTTP request in stream
  [[nodiscard]] virtual std::unique_ptr<boost::asio::streambuf>
  GenerateRequest(std::string_view url, std::string_view app) const;
  /// constant delimiter for requests and responses.
  constexpr static std::string_view kRequestDelimiter = "\r\n";
private:
  [[nodiscard]] tcp::socket Connect(std::string_view url) const;
};

#endif //HTTP_READER_HTTPREADER_H
