#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "process.hpp"

#include "mock_process.hpp"

class TestProcessManager : public testing::Test {};

/// Test initialisation of process manager and factory
TEST_F(TestProcessManager, TestProcessManagerInit) {
  auto pmf = process::PROC_get_processmanager_factory();
  ASSERT_NE(pmf, nullptr);

  auto pm = pmf->create_processmanager();

  ASSERT_NE(pm, nullptr);
}
