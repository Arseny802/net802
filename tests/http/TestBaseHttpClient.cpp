//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/Clients/BasicClientHttp.h>

namespace tests::http {
class TestBaseHttpClient : public ::testing::Test {
 protected:
  void SetUp() override {
	base_http_client_ = new Http::Clients::BasicClientHttp;
  }
  void TearDown() override {
	delete base_http_client_;
  }

  Http::Clients::BasicClientHttp *base_http_client_{};
};

TEST_F(TestBaseHttpClient, null) {
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_http_client_->Read(""));
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_http_client_->Read("", ""));
}

TEST_F(TestBaseHttpClient, google) {
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_http_client_->Read("google.com"));
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_http_client_->Read("google.com", ""));
}

}