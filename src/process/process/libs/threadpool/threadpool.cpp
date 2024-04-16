#include "threadpool.hpp"
#include "threadpool_impl.hpp"

#include <thread>

namespace process {
  namespace threadpool {
    std::unique_ptr<IThreadpool> ThreadpoolFactory::create() {
      return std::unique_ptr<Threadpool_impl>(
          new Threadpool_impl(std::thread::hardware_concurrency()));
    }

    std::unique_ptr<IThreadpool> ThreadpoolFactory::create(int nr_threads) {
      return std::unique_ptr<Threadpool_impl>(new Threadpool_impl(nr_threads));
    }
  } // namespace threadpool
}