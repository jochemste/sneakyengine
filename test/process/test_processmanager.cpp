#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "process.hpp"

#include "mock_process.hpp"

using testing::_;
using testing::Return;

class TestProcessManager : public testing::Test {};

/// Test initialisation of process manager and factory
TEST_F(TestProcessManager, TestProcessManagerInit) {
  auto pmf = process::PROC_get_processmanager_factory();
  ASSERT_NE(pmf, nullptr);

  auto pm = pmf->create_processmanager();

  ASSERT_NE(pm, nullptr);
}

TEST_F(TestProcessManager, TestProcessManagerEmptyRun) {

  auto pmf = process::PROC_get_processmanager_factory();
  auto pm  = pmf->create_processmanager();

  ASSERT_NO_THROW({
    pm->start();
    pm->stop();
  });
}

TEST_F(TestProcessManager, TestProcessManagerSingleRun) {

  auto pmf     = process::PROC_get_processmanager_factory();
  auto pm      = pmf->create_processmanager();
  auto process = MockProcess(ProcessOwner::process_manager, "testProcess");

  EXPECT_CALL(process, get_state())
      .WillRepeatedly(Return(ProcessState::running));
  EXPECT_CALL(process, kill());
  EXPECT_CALL(process, execute(_));

  ASSERT_NO_THROW({
    pm->start();
    pm->provide(process);
    pm->stop();
  });
}
