//
// Created by w1ckedente on 15.12.2020.
//

#include <tools/thread_pool.hpp>

thread_pool::thread_pool(std::size_t workers_count) {
  for (std::size_t i = 0; i < workers_count; ++i) {
    workers_.emplace_back([this] {
      for (;;) {
        auto work_item = tasks_.pop();
        if (!work_item) {
          tasks_.enqueue(nullptr);
          break;
        }
        work_item();
      }
    });
  }
}

thread_pool::~thread_pool() {
  tasks_.enqueue(nullptr);
  for (auto &worker : workers_) worker.join();
}
