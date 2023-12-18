#include "scheduler_fifo.hpp"

template <typename T> T &FIFOScheduler<T>::get_next() { return m_queue.pop(); }

template <typename T>
int FIFOScheduler<T>::schedule(T &process, int /*priority*/) {
  m_queue.push(process);
  return 0;
}

template <typename T> unsigned int FIFOScheduler<T>::nr_processes() {
  return m_queue.size();
}
