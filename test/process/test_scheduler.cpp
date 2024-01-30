#include <gtest/gtest.h>

#include "scheduler.hpp"

#include "mock_process.hpp"

#include <vector>

using ::testing::_;

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

/// @brief Test scheduler with mock processes
TEST_F(TestScheduler, TestFIFOQueueProcess) {
  scheduler::FIFOScheduler<MockProcess> s;
  std::array<MockProcess, 3> processes = {
      MockProcess(ProcessOwner::process_manager, "testProcess1"),
      MockProcess(ProcessOwner::client_application, "testProcess2"),
      MockProcess(ProcessOwner::none, "testProcess3"),
  };

  for (unsigned int i = 0; i < processes.size(); i++) {
    // Call member function expected to be able to determine identity of process
    EXPECT_CALL(processes.at(i), get_owner()).Times(2);

    // Ensure scheduler never calls member functions
    EXPECT_CALL(processes.at(i), execute(_)).Times(0);
    EXPECT_CALL(processes.at(i), get_state()).Times(0);
    EXPECT_CALL(processes.at(i), kill()).Times(0);
  }

  for (auto &proc : processes) {
    EXPECT_NO_THROW({ s.schedule(proc); });
  }

  ASSERT_EQ(s.nr_processes(), processes.size());

  for (unsigned int i = 0; i < processes.size(); i++) {
    auto el = s.get_next();
    EXPECT_EQ(el->get_owner(), processes.at(i).get_owner());
  }

  ASSERT_EQ(0, s.nr_processes());
}
