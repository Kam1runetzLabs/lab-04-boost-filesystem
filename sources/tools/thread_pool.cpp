//
// Created by w1ckedente on 18.12.2020.
//
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <tools/thread_pool.hpp>
#include <vector>

thread_pool::thread_pool(std::size_t workers_count) : _is_stopped(false) {
  for (std::size_t i = 0; i < workers_count; ++i) {
    _worker_threads.emplace_back([=] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(_mutex);
          _available_to_job.wait(
              lock, [=] { return _is_stopped || !_tasks_queue.empty(); });
          if (_is_stopped && _tasks_queue.empty()) return;
          task = std::move(_tasks_queue.front());
          _tasks_queue.pop();
        }
        task();
      }
    });
  }
}

thread_pool::~thread_pool() {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    _is_stopped = true;
  }
  _available_to_job.notify_all();
  for (auto &worker : _worker_threads) worker.join();
}
