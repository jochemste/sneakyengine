#include <gtest/gtest.h>

#include "scheduler.hpp"

#include <vector>

class TestScheduler : public testing::Test {};

TEST_F(TestScheduler, TestConstructorFIFO) {
  EXPECT_NO_THROW({ scheduler::FIFOScheduler<int> s; });
  EXPECT_NO_THROW({ scheduler::FIFOScheduler<int *> s; });
  EXPECT_NO_THROW({ scheduler::FIFOScheduler<std::vector<int>> s; });
}

TEST_F(TestScheduler, TestFIFOLengthMatchesSource) {
  std::vector<int> v{4, 2, 0, 42};
  scheduler::FIFOScheduler<int> s;

  for (auto &el : v) {
    s.schedule(el);
  }

  ASSERT_EQ(v.size(), s.nr_processes());
}

TEST_F(TestScheduler, TestFIFOQueueCorrectOrder) {
  std::vector<int> v{4, 2, 0, 42};
  scheduler::FIFOScheduler<int> s;

  for (auto &el : v) {
    s.schedule(el);
  }

  ASSERT_EQ(v.size(), s.nr_processes());

  for (unsigned int i = 0; i < v.size(); i++) {
    auto el = s.get_next();
    EXPECT_EQ(*el, v.at(i));
  }

  ASSERT_EQ(0, s.nr_processes());
}
