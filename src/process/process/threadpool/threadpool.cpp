#include "threadpool.hpp"
#include "threadpool_impl.hpp"

#include <thread>

namespace threadpool {
std::unique_ptr<IThreadpool> ThreadpoolFactory::create() {
  return std::make_unique<Threadpool_impl>(
      Threadpool_impl(std::thread::hardware_concurrency()));
}

std::unique_ptr<IThreadpool> ThreadpoolFactory::create(int nr_threads) {
  return std::make_unique<Threadpool_impl>(Threadpool_impl(nr_threads));
}
} // namespace threadpool
