#ifndef THREADPOOL_IMPL_HPP
#define THREADPOOL_IMPL_HPP

#include "threadpool.hpp"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace threadpool {
class Threadpool_impl : public IThreadpool {
public:
  Threadpool_impl();
  Threadpool_impl(int nr_threads);
  Threadpool_impl(const Threadpool_impl &other) = delete;
  Threadpool_impl(Threadpool_impl &&other)      = default;

  ~Threadpool_impl() {}
  virtual void start() override;
  virtual void stop() override;
  virtual void add_to_queue(const int &id,
                            std::shared_ptr<IProcess> process) override;
  virtual int get_nr_queued() override;
  virtual int get_nr_running() override;
  virtual bool busy() override;

private:
  void thread_run();

  const int m_nr_threads;
  std::atomic<int> m_nr_running;
  bool m_should_stop;
  std::mutex m_queue_mutex;
  std::vector<std::thread> m_threads;
  std::condition_variable m_mutex_condition;
  std::queue<std::pair<int, std::shared_ptr<IProcess>>> m_queue;
};
} // namespace threadpool

#endif // THREADPOOL_IMPL_HPP
