#include "display_proc_impl.hpp"

#include "display.hpp"
#include "process.hpp"

#include <memory>

class DisplayProcessImpl : public IProcess {
public:
  DisplayProcessImpl() = delete;
  DisplayProcessImpl(const ProcessOwner &owner, const std::string &name);
  ~DisplayProcessImpl();

  virtual void execute(int id) override;
  virtual void kill() override;
  virtual ProcessState get_state() override;
  virtual ProcessOwner get_owner() override;

private:
  ProcessOwner m_owner;
  int m_process_id;
  std::string m_name;
  ProcessState m_state;
};

std::unique_ptr<IProcess>
DisplayProcessFactory::createProcess(const ProcessOwner &owner,
                                     const std::string &name) {
  return std::make_unique<DisplayProcessImpl>(owner, name);
}

DisplayProcessImpl::DisplayProcessImpl(const ProcessOwner &owner,
                                       const std::string &name)
    : m_owner(owner), m_process_id(-1), m_name(name),
      m_state(ProcessState::not_running) {}
DisplayProcessImpl::~DisplayProcessImpl() {}
void DisplayProcessImpl::execute(int id) { m_process_id = id; }
void DisplayProcessImpl::kill() { m_process_id = -1; }
ProcessState DisplayProcessImpl::get_state() { return m_state; }
ProcessOwner DisplayProcessImpl::get_owner() { return m_owner; }
