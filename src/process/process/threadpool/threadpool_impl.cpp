#include "threadpool_impl.hpp"

namespace threadpool {
Threadpool_impl::Threadpool_impl(int nr_processes) {}
void Threadpool_impl::start() {}
void Threadpool_impl::stop() {}
void Threadpool_impl::add_to_queue(std::shared_ptr<IProcess> process) {}
} // namespace threadpool
