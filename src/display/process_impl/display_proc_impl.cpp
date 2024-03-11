#include "display_proc_impl.hpp"

#include "display.hpp"
#include "logging.hpp"
#include "process.hpp"

#include <memory>
#include <mutex>
namespace {
  namespace displayProcess {
    class DisplayProcessImpl : public IProcess {
    public:
      DisplayProcessImpl() = delete;
      DisplayProcessImpl(const ProcessOwner &owner, const std::string &name);
      ~DisplayProcessImpl();

      virtual void execute(int id) override;
      virtual void kill() override;
      virtual ProcessState get_state() override;
      virtual ProcessOwner get_owner() override;
      virtual void get_name(std::string &name) override;

    private:
      void update_state(const ProcessState &state);

      ProcessOwner m_owner;
      int m_process_id;
      std::string m_name;
      ProcessState m_state;
      std::unique_ptr<IDisplay> m_display;
      std::mutex m_state_mutex;
    };

    std::unique_ptr<IProcess>
    DisplayProcessFactory::createProcess(const ProcessOwner &owner,
                                        const std::string &name) {
      return std::make_unique<DisplayProcessImpl>(owner, name);
    }

    DisplayProcessImpl::DisplayProcessImpl(const ProcessOwner &owner,
                                          const std::string &name)
        : m_owner(owner), m_process_id(-1), m_name(name),
          m_state(ProcessState::not_running),
          m_display(DIS_get_display_instance()) {
      Log(LogLevel::debug) << LOG_START;
      Log(LogLevel::debug) << LOG_END;
    }

    DisplayProcessImpl::~DisplayProcessImpl() {
      Log(LogLevel::debug) << LOG_START;
      kill();
      Log(LogLevel::debug) << LOG_END;
    }

    void DisplayProcessImpl::execute(int id) {
      Log(LogLevel::debug) << LOG_START;
      Log(LogLevel::info) << LOG_HEADER << "Executing process " << id << ": "
                          << m_name;
      m_process_id = id;
      update_state(ProcessState::running);

      try {
        m_display->start();

        while (get_state() == ProcessState::running) {
          m_display->refresh();
        }

      } catch (DisplayException &e) {
        update_state(ProcessState::failed);
        std::string err_msg("Display process has failed");
        Log(LogLevel::critical) << LOG_HEADER << err_msg << ": " << e.what();
        throw ProcessException(err_msg);
      }
      Log(LogLevel::debug) << LOG_END;
    }

    void DisplayProcessImpl::kill() {
      Log(LogLevel::debug) << LOG_START;
      if (get_state() == ProcessState::running) {
        update_state(ProcessState::stopping);

        try {
          m_display->stop();
        } catch (DisplayException &e) {
          update_state(ProcessState::failed);
          Log(LogLevel::error) << LOG_HEADER << "Killing display has failed"
                              << ": " << e.what();
        }
      }

      if (get_state() != ProcessState::failed) {
        update_state(ProcessState::finished);
      }
      m_process_id = -1;
      Log(LogLevel::debug) << LOG_END;
    }

    ProcessState DisplayProcessImpl::get_state() {
      Log(LogLevel::debug) << LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      Log(LogLevel::debug) << LOG_END;
      return m_state;
    }

    ProcessOwner DisplayProcessImpl::get_owner() {
      Log(LogLevel::debug) << LOG_START;
      Log(LogLevel::debug) << LOG_END;
      return m_owner;
    }

    void DisplayProcessImpl::get_name(std::string &name) {
      Log(LogLevel::debug) << LOG_START;
      name = m_name;
      Log(LogLevel::debug) << LOG_END;
    }

    void DisplayProcessImpl::update_state(const ProcessState &state) {
      Log(LogLevel::debug) << LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      m_state = state;
      Log(LogLevel::debug) << LOG_END;
    }
  }
}