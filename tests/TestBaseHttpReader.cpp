//
// Created by arseny on 01/02/2020.
//
#include "gtest/gtest.h"
#include "BaseHttp/Base/BaseHttp.h"
#include <iostream>
#include <BaseHttp/ClientHttp.h>

class TestHttpReader : public ::testing::Test {
protected:
	void SetUp() override
	{
		httpReader = new ClientHttp;
	}
	void TearDown() override
	{
		delete httpReader;
	}
	
	ClientHttp *httpReader;
};

TEST_F(TestHttpReader, null)
{
	EXPECT_EQ(HttpResultCodes::InvalidRequest_host, httpReader->Read(""));
	EXPECT_EQ(HttpResultCodes::InvalidRequest_host, httpReader->Read("", ""));
}

TEST_F(TestHttpReader, google)
{
	EXPECT_EQ(HttpResultCodes::Ok, httpReader->Read("google.com"));
	EXPECT_EQ(HttpResultCodes::Ok, httpReader->Read("google.com", ""));
}