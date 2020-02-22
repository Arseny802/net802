//
// Created by arseny on 31/01/2020.
//
#include "BaseHttp.h"
#include "HttpResultCodes.h"
#include "HttpStatusCodes.h"

#include <fmt/format.h>
#include <boost/asio/connect.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <boost/asio/read.hpp>
#include <regex>

namespace http::base {

BaseHttp::BaseHttp() = default;

BaseHttp::~BaseHttp() = default;

HttpResultCodes BaseHttp::StartReadingProcess(std::string_view url, std::string_view app) {

  if (url.empty()) {
	return HttpResultCodes::InvalidRequest_host;
  }

  boost::system::error_code error;
  try {
	tcp::socket socket = Connect(url.data());

	// Send the request.
	buffer request;
	GenerateRequest(request, url.data(), app.data());
	boost::asio::write(socket, request);

	// Read the response status line. The response streambuf will
	// automatically grow to accommodate the entire line. The growth may be
	// limited by passing a maximum size to the streambuf constructor.
	buffer response;
	boost::asio::read_until(socket, response, kRequestDelimiter.data(), error);

	if (error != nullptr) {
	  std::cout << "Got " << error << " error on request." << std::endl;
	  LogBufferStream(response);
	  return HttpResultCodes::ProcessingError;
	}

	// Check that response is OK.
	std::istream response_stream(&response);

	std::string http_version;
	response_stream >> http_version;
	std::cout << "Response returned with http version: " << http_version << std::endl;

	unsigned int status_code;
	response_stream >> status_code;
	std::cout << "Response returned with status code: " << status_code << std::endl;

	std::string status_message;
	std::getline(response_stream, status_message);

	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
	  std::cout << "Invalid response" << std::endl;
	  LogBufferStream(response);
	  return HttpResultCodes::InvalidResponse;
	}

	if (status_code == HttpStatusCodes::Moved) {
	  std::string moving_location;
	  std::getline(response_stream, moving_location);

	  if (moving_location.size() < 20) {
		return HttpResultCodes::MovedWithNoLocation;
	  }

	  moving_location = std::move(moving_location.erase(0, 17));
	  moving_location = moving_location.substr(0, moving_location.size() - 2);

	  if (IsUrl(moving_location)) {
		std::cout << "New location is " << moving_location << std::endl;
		return Read(moving_location, app);
	  } else {
		return HttpResultCodes::MovedWithNoLocation;
	  }
	}

	if (status_code != HttpStatusCodes::Success) {
	  LogBufferStream(response);
	  return HttpResultCodes::ProcessingError;
	}

	// Read the response headers, which are terminated by a blank line.
	boost::asio::read_until(socket, response,
	                        fmt::format("{}{}", kRequestDelimiter, kRequestDelimiter));

	// Process the response headers.
	std::string header;
	while (std::getline(response_stream, header) && header != "\r") {
	  std::cout << header << std::endl;
	}
	std::cout << std::endl;

	// Write whatever content we already have to output.
	if (response.size() > 0) {
	  std::cout << &response;
	}

	// Read until EOF, writing data to output as we go.
	while (boost::asio::read(socket, response,
	                         boost::asio::transfer_at_least(1), error)) {
	  std::cout << &response;
	}
	if (error != nullptr) {
	  std::cout << "Got " << error << " error on request." << std::endl;
	  return HttpResultCodes::ProcessingError;
	}
	return HttpResultCodes::Ok;
  } catch (std::exception &e) {
	std::cout << "Exception: " << e.what() << std::endl;
	return HttpResultCodes::ProcessingException;
  }
}

void BaseHttp::LogBufferStream(buffer &buffer) {
  size_t nBufferSize = boost::asio::buffer_size(buffer.data());

  // get const buffer
  std::stringstream ssOut;
  boost::asio::streambuf::const_buffers_type constBuffer = buffer.data();

  // copy const buffer to stringstream, then output
  std::copy(
	  boost::asio::buffers_begin(constBuffer),
	  boost::asio::buffers_begin(constBuffer) + nBufferSize,
	  std::ostream_iterator<char>(ssOut)
  );

  std::cout << ssOut.str() << std::endl;
}

tcp::socket BaseHttp::Connect(std::string_view url) const {
  boost::asio::io_service io_service;

  // Get a list of endpoints corresponding to the server name.
  tcp::resolver resolver(io_service);
  std::string &&protocol(GetProtocol().data());
  std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);

  tcp::resolver::query query(url.data(), protocol);
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  // Try each endpoint until we successfully establish a connection.
  tcp::socket socket(io_service);
  boost::asio::connect(socket, endpoint_iterator);

  return socket;
}

void BaseHttp::GenerateRequest(buffer &request, std::string_view url, std::string_view app) const {
  std::ostream request_stream(&request);

  if (app.empty()) {
	request_stream << GetRequestType() << " / " << GetSpecificProtocol() << kRequestDelimiter;
  } else {
	request_stream << GetRequestType() << " " << app << " " << GetSpecificProtocol() << kRequestDelimiter;
  }

  request_stream << "Host: " << url << kRequestDelimiter;
  request_stream << "Accept: */*" << kRequestDelimiter;
  request_stream << "Connection: close" << fmt::format("{}{}", kRequestDelimiter, kRequestDelimiter);
}

std::string BaseHttp::GetSpecificProtocol() const noexcept {
  return fmt::format("{}/{}", GetProtocol(), GetProtocolVersion());
}

bool BaseHttp::IsUrl(std::string_view url) noexcept {
  //boost::network::uri uri(url);
  //return std::regex_match (url, std::regex("^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$"));
  return !url.empty();
}

}