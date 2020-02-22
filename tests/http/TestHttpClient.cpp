//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include <http/HttpClient.h>

namespace tests::http {
class TestHttpClient : public ::testing::Test {
 protected:
  void SetUp() override {
	http_reader_ = new Http::HttpClient;
  }
  void TearDown() override {
	delete http_reader_;
  }

  Http::HttpClient *http_reader_{};
};

TEST_F(TestHttpClient, null) {
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, http_reader_->Read(""));
  EXPECT_EQ(Http::Base::HttpResultCodes::InvalidRequest_host, http_reader_->Read("", ""));
}

TEST_F(TestHttpClient, google) {
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, http_reader_->Read("google.com"));
  EXPECT_EQ(Http::Base::HttpResultCodes::Ok, http_reader_->Read("google.com", ""));
}

}