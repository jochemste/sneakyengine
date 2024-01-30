#ifndef THREADPOOL_IMPL_HPP
#define THREADPOOL_IMPL_HPP

#include "threadpool.hpp"

namespace threadpool {
class Threadpool_impl : public IThreadpool {
public:
  Threadpool_impl(int nr_processes);
  virtual void start() override;
  virtual void stop() override;
  virtual void add_to_queue(std::shared_ptr<IProcess> process) override;
};
} // namespace threadpool

#endif // THREADPOOL_IMPL_HPP
