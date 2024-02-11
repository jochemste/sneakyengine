#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "process.hpp"

#include "mock_process.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

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

TEST_F(TestProcessManager, TestProcessManagerSingleRunExec) {

  auto pmf     = process::PROC_get_processmanager_factory();
  auto pm      = pmf->create_processmanager();
  auto process = MockProcess(ProcessOwner::process_manager, "testProcess");

  ProcessState state = ProcessState::not_running;
  auto exec          = [&state](int id) { state = ProcessState::finished; };
  auto get_state     = [&state]() { return state; };

  EXPECT_CALL(process, get_state())
      .WillRepeatedly(Return(ProcessState::running));
  {
    testing::InSequence s;
    EXPECT_CALL(process, execute(_)).WillOnce(Invoke(exec));
    EXPECT_CALL(process, kill()).Times(1);
    EXPECT_CALL(process, get_state()).WillRepeatedly(Invoke(get_state));
  }

  ASSERT_NO_THROW({
    pm->start();
    pm->provide(process);

    // wait for procman to init process
    while (!pm->busy())
      ;
    // wait for process to finish
    while (state != ProcessState::finished)
      ;
    pm->stop();
  });
}

TEST_F(TestProcessManager, TestProcessManagerSingleEarlyStop) {

  auto pmf     = process::PROC_get_processmanager_factory();
  auto pm      = pmf->create_processmanager();
  auto process = MockProcess(ProcessOwner::process_manager, "testProcess");

  EXPECT_CALL(process, execute(_)).Times(1);
  EXPECT_CALL(process, kill()).Times(1);
  EXPECT_CALL(process, get_state())
      .WillRepeatedly(Return(ProcessState::not_running));

  ASSERT_NO_THROW({
    pm->start();
    pm->provide(process);
    // wait for procman to init process
    while (!pm->busy())
      ;
    pm->stop();
  });
}

// TEST_F(TestProcessManager, TestProcessManagerMultipleRun) {

//   auto pmf = process::PROC_get_processmanager_factory();
//   auto pm  = pmf->create_processmanager();

//   // index of the current process
//   int index                          = 0;
//   std::array<ProcessState, 3> states = {ProcessState::not_running,
//                                         ProcessState::not_running,
//                                         ProcessState::not_running};
//   auto exec                          = [&states, index](int id) {
//     states[index] = ProcessState::finished;
//   };
//   auto get_state = [&states, index]() { return states[index]; };

//   std::array<MockProcess, 3> processes = {
//       MockProcess(ProcessOwner::process_manager, "testProcess1"),
//       MockProcess(ProcessOwner::process_manager, "testProcess2"),
//       MockProcess(ProcessOwner::process_manager, "testProcess3"),
//   };

//   index = 0;
//   EXPECT_CALL(processes[index],
//   get_state()).WillRepeatedly(Invoke(get_state));
//   {
//     testing::InSequence s;
//     EXPECT_CALL(processes[index], execute(_)).WillOnce(Invoke(exec));
//     EXPECT_CALL(processes[index], kill()).Times(1);
//     EXPECT_CALL(processes[index], get_state()).WillOnce(Invoke(get_state));
//   }
//   // for (auto &process : processes) {
//   //   EXPECT_CALL(process, get_state())
//   //       .WillRepeatedly(Return(ProcessState::running));
//   //   EXPECT_CALL(process, kill());
//   //   EXPECT_CALL(process, execute(_));
//   // }

//   ASSERT_NO_THROW({
//     for (auto &process : processes) {
//       pm->start();
//       pm->provide(process);
//       // wait for procman to init first process
//       while (!pm->busy())
//         ;

//       // wait for processes to finish
//       // while (state != ProcessState::finished)
//       //   ;

//       pm->stop();
//     }
//   });
// }
