//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/codes/HttpResultCodes.h>
#include <http/clients/BasicClientHttp.h>

namespace tests::http {
class TestBaseHttpClient : public ::testing::Test {
 protected:
  void SetUp() override {
	base_http_client_ = new ::http::clients::BasicClientHttp;
  }
  void TearDown() override {
	delete base_http_client_;
  }

  ::http::clients::BasicClientHttp *base_http_client_{};
};

TEST_F(TestBaseHttpClient, null) {
  EXPECT_EQ(::http::codes::HttpResultCodes::InvalidRequest_host, base_http_client_->Read(""));
  EXPECT_EQ(::http::codes::HttpResultCodes::InvalidRequest_host, base_http_client_->Read("", ""));
}

TEST_F(TestBaseHttpClient, google) {
  EXPECT_EQ(::http::codes::HttpResultCodes::Ok, base_http_client_->Read("google.com"));
  EXPECT_EQ(::http::codes::HttpResultCodes::Ok, base_http_client_->Read("google.com", ""));
}

}