//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/Clients/BasicClientHttps.h>

namespace tests::http {
class TestBaseHttpsClient : public ::testing::Test {
 protected:
  void SetUp() override {
	base_https_client_ = new Http::Clients::BasicClientHttps;
  }
  void TearDown() override {
	delete base_https_client_;
  }

  Http::Clients::BasicClientHttps *base_https_client_{};
};

TEST_F(TestBaseHttpsClient, null) {
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_https_client_->Read(""));
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_https_client_->Read("", ""));
}

TEST_F(TestBaseHttpsClient, google) {
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_https_client_->Read("google.com"));
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_https_client_->Read("google.com", ""));
}

}