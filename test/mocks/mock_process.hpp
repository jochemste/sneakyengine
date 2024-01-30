#include <gmock/gmock.h>

#include <string>

#include "process.hpp"

class MockProcess : public IProcess {
public:
  MockProcess()                         = delete;
  MockProcess(const MockProcess &other) = delete;
  MockProcess(MockProcess &&other)      = default;

  MockProcess(const ProcessOwner &owner, const std::string &name)
      : m_name(name), m_owner(owner), m_id(-1) {}
  MOCK_METHOD(void, execute, (int id), (override));
  MOCK_METHOD(void, kill, (), (override));
  MOCK_METHOD(ProcessState, get_state, (), (override));
  MOCK_METHOD(ProcessOwner, get_owner, (), (override));

protected:
private:
  const std::string m_name;
  ProcessOwner m_owner;
  int m_id;
};
