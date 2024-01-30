#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "process.hpp"
#include "threadpool_impl.hpp"

#include "mock_process.hpp"

#include <chrono>
#include <thread>

using ::testing::Invoke;

class TestThreadpool : public ::testing::Test {};

TEST_F(TestThreadpool, TestThreadpoolSingleThreadNoProcess) {
  threadpool::Threadpool_impl tp = threadpool::Threadpool_impl(1);

  EXPECT_NO_THROW({
    tp.start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    tp.stop();
  });
}

TEST_F(TestThreadpool, TestThreadpoolSysNrThreadNoProcess) {
  threadpool::Threadpool_impl tp = threadpool::Threadpool_impl();

  EXPECT_NO_THROW({
    tp.start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    tp.stop();
  });
}

TEST_F(TestThreadpool, TestThreadpoolSysNrThreadOneProcess) {
  int id = 1;
  std::shared_ptr<MockProcess> process(
      new MockProcess(ProcessOwner::process_manager, "testProcess1"));
  threadpool::Threadpool_impl tp = threadpool::Threadpool_impl();

  EXPECT_CALL(*process.get(), execute(id)).Times(1);

  EXPECT_NO_THROW({
    tp.start();
    tp.add_to_queue(id, process);
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    tp.stop();
  });
}

TEST_F(TestThreadpool, TestThreadpoolSysNrThreadMultiProcess) {
  std::shared_ptr<MockProcess> process(
      new MockProcess(ProcessOwner::process_manager, "testProcess1"));
  threadpool::Threadpool_impl tp = threadpool::Threadpool_impl();
  auto f                         = [](int id) {
    std::cout << "Testing " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  };

  {
    for (int id = 0; id < 100; id++) {
      EXPECT_CALL(*process.get(), execute(id))
          .Times(1)
          .WillRepeatedly(Invoke(f));
    }
  }

  EXPECT_NO_THROW({
    tp.start();
    for (int id = 0; id < 100; id++) {
      tp.add_to_queue(id, process);
    }

    while (tp.busy())
      ;
    tp.stop();
  });

  EXPECT_EQ(0, tp.get_nr_running());
  EXPECT_EQ(0, tp.get_nr_queued());
}
