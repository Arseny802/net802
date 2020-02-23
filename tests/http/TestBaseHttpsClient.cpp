//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/codes/HttpResultCodes.h>
#include <http/clients/BasicClientHttps.h>

namespace tests::http {
class TestBaseHttpsClient : public ::testing::Test {
 protected:
  void SetUp() override {
	base_https_client_ = new ::http::clients::BasicClientHttps;
  }
  void TearDown() override {
	delete base_https_client_;
  }

  ::http::clients::BasicClientHttps *base_https_client_{};
};

TEST_F(TestBaseHttpsClient, null) {
  EXPECT_EQ(::http::codes::HttpResultCodes::InvalidRequest_host, base_https_client_->Read(""));
  EXPECT_EQ(::http::codes::HttpResultCodes::InvalidRequest_host, base_https_client_->Read("", ""));
}

TEST_F(TestBaseHttpsClient, google) {
  EXPECT_EQ(::http::codes::HttpResultCodes::Ok, base_https_client_->Read("google.com"));
  EXPECT_EQ(::http::codes::HttpResultCodes::Ok, base_https_client_->Read("google.com", ""));
}

}