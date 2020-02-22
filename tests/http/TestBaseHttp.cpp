//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/base/HttpResultCodes.h>
#include <http/base/BaseHttp.h>

namespace tests::http {
class TestBaseHttp : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }

  ::http::base::BaseHttp *base_http_{};
};

TEST_F(TestBaseHttp, null) {
  EXPECT_EQ(::http::base::HttpResultCodes::InvalidRequest_host, base_http_->Read(""));
  EXPECT_EQ(::http::base::HttpResultCodes::InvalidRequest_host, base_http_->Read("", ""));
}

TEST_F(TestBaseHttp, google) {
  EXPECT_EQ(::http::base::HttpResultCodes::Ok, base_http_->Read("google.com"));
  EXPECT_EQ(::http::base::HttpResultCodes::Ok, base_http_->Read("google.com", ""));
}

}