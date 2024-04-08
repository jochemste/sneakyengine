#include <gtest/gtest.h>

#include "hash.hpp"

class TestHash : public ::testing::Test {};

/// Basic test to ensure no interface change and no unexpected failures
TEST_F(TestHash, TestGetHash) { EXPECT_NE(0, hash::get_hash("some string")); }
