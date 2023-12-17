#include "scheduler.hpp"

#include <queue>

template <typename T> class FIFOScheduler {
public:
  virtual T &get_next() override;
  virtual int schedule(T &process, int /*priority*/) override;
  virtual unsigned int nr_processes() override;

protected:
private:
  std::queue<T &> m_queue;
};
