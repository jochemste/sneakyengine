#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "process.hpp"

#include "mock_process.hpp"

#include <array>
#include <sstream>
#include <string>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class TestProcessManager : public testing::Test {
protected:
  std::string get_procname(std::string basename, int index) {
    std::stringstream ss;
    ss << basename << index;
    return ss.str();
  }
};

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

/// Test a single process run
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

  pm->start();
  pm->provide(process);

  // wait for procman to init process
  while (!pm->busy())
    ;
  // wait for process to finish
  while (state != ProcessState::finished)
    ;

  pm->stop();
}

/// Test early stopping of procman
TEST_F(TestProcessManager, TestProcessManagerSingleEarlyStop) {

  auto pmf     = process::PROC_get_processmanager_factory();
  auto pm      = pmf->create_processmanager();
  auto process = MockProcess(ProcessOwner::process_manager, "testProcess");

  EXPECT_CALL(process, execute(_)).Times(1);
  EXPECT_CALL(process, kill()).Times(1);
  EXPECT_CALL(process, get_state())
      .WillRepeatedly(Return(ProcessState::not_running));

  pm->start();
  pm->provide(process);

  // wait for procman to init process
  while (!pm->busy())
    ;

  // Do not wait for process to finish

  pm->stop();
}

/// Test with large amount of processes
TEST_F(TestProcessManager, TestProcessManagerMultipleRun) {
  const int nr_procs = 1000;
  auto pmf           = process::PROC_get_processmanager_factory();
  auto pm            = pmf->create_processmanager();

  int index             = 0; // index of the current process
  std::string name_base = "testProcess"; // basename of the processes
  std::array<ProcessState, nr_procs> states; // states of the processes
  std::array<MockProcess *, nr_procs> processes; // the process objects

  // initialise test
  for (int i = 0; i < nr_procs; i++) {
    states[i]    = ProcessState::not_running;
    processes[i] = new MockProcess(ProcessOwner::process_manager,
                                   get_procname(name_base, index));
  }

  index = 0;
  for (auto &process : processes) {
    //   testing::InSequence s;
    EXPECT_CALL(*process, get_state())
        .WillRepeatedly(Invoke([&states, index]() { return states[index]; }));
    EXPECT_CALL(*process, kill()).WillOnce(Invoke([&states, index]() {
      states[index] = ProcessState::finished;
    }));
    EXPECT_CALL(*process, execute(_)).WillOnce(Invoke([&states, index](int id) {
      states[index] = ProcessState::running;
    }));
    index++;
  }

  pm->start();

  for (auto &process : processes) {
    pm->provide(*process);
  }

  // wait for procman to init first process
  while (!pm->busy())
    ;

  // wait for processes to finish
  for (index = 0; index < nr_procs; index++) {
    while (states[index] != ProcessState::running)
      ;
  }

  // stop procman
  pm->stop();

  // cleanup
  for (int i = 0; i < nr_procs; i++)
    delete processes[i];
}

/// Test a number of processes that finish before stop is called
TEST_F(TestProcessManager, TestProcessManagerMultipleRunProcFinished) {
  const int nr_procs = 100;
  auto pmf           = process::PROC_get_processmanager_factory();
  auto pm            = pmf->create_processmanager();

  int index             = 0; // index of the current process
  std::string name_base = "testProcess"; // basename of the processes
  std::array<ProcessState, nr_procs> states; // states of the processes
  std::array<MockProcess *, nr_procs> processes; // the process objects

  // initialise test
  for (int i = 0; i < nr_procs; i++) {
    states[i]    = ProcessState::not_running;
    processes[i] = new MockProcess(ProcessOwner::process_manager,
                                   get_procname(name_base, index));
  }

  index = 0;
  for (auto &process : processes) {
    //   testing::InSequence s;
    EXPECT_CALL(*process, get_state())
        .WillRepeatedly(Invoke([&states, index]() { return states[index]; }));
    EXPECT_CALL(*process, execute(_)).WillOnce(Invoke([&states, index](int id) {
      states[index] = ProcessState::finished;
    }));
    index++;
  }

  pm->start();

  for (auto &process : processes) {
    pm->provide(*process);
  }

  // wait for procman to init first process
  while (!pm->busy())
    ;

  // wait for processes to finish
  for (index = 0; index < nr_procs; index++) {
    while (states[index] != ProcessState::finished)
      ;
  }

  // stop procman
  pm->stop();

#ifdef _WIN32
  // cleanup when windows, there seems to be a difference
  // in smart pointer implementation in std::map erase usage
  for (int i = 0; i < nr_procs; i++)
    delete processes[i];
#endif //_WIN32
}
