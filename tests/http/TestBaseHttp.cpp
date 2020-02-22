//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/Base/BaseHttp.h>

namespace tests::http {
class TestBaseHttp : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }

  Http::Base::BaseHttp *base_http_{};
};

TEST_F(TestBaseHttp, null) {
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_http_->Read(""));
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, base_http_->Read("", ""));
}

TEST_F(TestBaseHttp, google) {
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_http_->Read("google.com"));
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, base_http_->Read("google.com", ""));
}

}