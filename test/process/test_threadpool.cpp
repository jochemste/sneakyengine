#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "threadpool_impl.hpp"

#include "mock_process.hpp"

#include <chrono>
#include <thread>

class TestThreadpool : public ::testing::Test {};

TEST_F(TestThreadpool, TestThreadpoolSingleThread) {
  threadpool::Threadpool_impl tp = threadpool::Threadpool_impl(1);

  EXPECT_NO_THROW({
    tp.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    tp.stop();
  });
}
