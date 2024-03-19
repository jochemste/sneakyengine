#include "display_proc_impl.hpp"

#include "display.hpp"
#include "logging.hpp"
#include "process.hpp"

#include <memory>
#include <mutex>
namespace display {
  namespace display_process {
    class DisplayProcessImpl : public process::IProcess {
    public:
      DisplayProcessImpl() = delete;
      DisplayProcessImpl(const process::ProcessOwner &owner, const std::string &name);
      ~DisplayProcessImpl();

      virtual void execute(int id) override;
      virtual void kill() override;
      virtual process::ProcessState get_state() override;
      virtual process::ProcessOwner get_owner() override;
      virtual void get_name(std::string &name) override;

    private:
      void update_state(const process::ProcessState &state);

      process::ProcessOwner m_owner;
      int m_process_id;
      std::string m_name;
      process::ProcessState m_state;
      std::unique_ptr<display::IDisplay> m_display;
      std::mutex m_state_mutex;
    };

    std::unique_ptr<process::IProcess>
    DisplayProcessFactory::createProcess(const process::ProcessOwner &owner,
                                        const std::string &name) {
      return std::make_unique<DisplayProcessImpl>(owner, name);
    }

    DisplayProcessImpl::DisplayProcessImpl(const process::ProcessOwner &owner,
                                          const std::string &name)
        : m_owner(owner), m_process_id(-1), m_name(name),
          m_state(process::ProcessState::not_running),
          m_display(DIS_get_display_instance()) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    DisplayProcessImpl::~DisplayProcessImpl() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      kill();
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    void DisplayProcessImpl::execute(int id) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::info) << logging::LOG_HEADER << "Executing process " << id << ": "
                          << m_name;
      m_process_id = id;
      update_state(process::ProcessState::running);

      try {
        m_display->start();

        while (get_state() == process::ProcessState::running) {
          m_display->refresh();
        }

      } catch (display::DisplayException &e) {
        update_state(process::ProcessState::failed);
        std::string err_msg("Display process has failed");
        logging::Log(logging::LogLevel::critical) << logging::LOG_HEADER << err_msg << ": " << e.what();
        throw process::ProcessException(err_msg);
      }
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    void DisplayProcessImpl::kill() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      if (get_state() == process::ProcessState::running) {
        update_state(process::ProcessState::stopping);

        try {
          m_display->stop();
        } catch (display::DisplayException &e) {
          update_state(process::ProcessState::failed);
          logging::Log(logging::LogLevel::error) << logging::LOG_HEADER << "Killing display has failed"
                              << ": " << e.what();
        }
      }

      if (get_state() != process::ProcessState::failed) {
        update_state(process::ProcessState::finished);
      }
      m_process_id = -1;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    process::ProcessState DisplayProcessImpl::get_state() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
      return m_state;
    }

    process::ProcessOwner DisplayProcessImpl::get_owner() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
      return m_owner;
    }

    void DisplayProcessImpl::get_name(std::string &name) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      name = m_name;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    void DisplayProcessImpl::update_state(const process::ProcessState &state) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      m_state = state;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }
  }
}