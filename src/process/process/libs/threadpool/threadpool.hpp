#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "process.hpp"

#include <memory>

namespace process {
  namespace threadpool {

    class IThreadpool {
      public:
        virtual ~IThreadpool() {}
        virtual void start()                                         = 0;
        virtual void stop()                                          = 0;
        virtual void add_to_queue(const int &id,
                                  std::shared_ptr<IProcess> process) = 0;
        virtual int get_nr_queued()                                  = 0;
        virtual int get_nr_running()                                 = 0;
        virtual bool busy()                                          = 0;

      protected:
        IThreadpool() {}
        IThreadpool(int /*nr_threads*/) {}
    };

    class ThreadpoolFactory {
      public:
        std::unique_ptr<IThreadpool> create();
        std::unique_ptr<IThreadpool> create(int nr_threads);

      private:
    };

  } // namespace threadpool
}

#endif // THREADPOOL_HPP
