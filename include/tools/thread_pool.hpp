//
// Created by w1ckedente on 17.12.2020.
//

#ifndef BFSYSTEM_THREAD_POOL_HPP
#define BFSYSTEM_THREAD_POOL_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class thread_pool {
 public:
  explicit thread_pool(
      std::size_t workers_count = std::thread::hardware_concurrency());
  ~thread_pool();

  template <typename task_t, typename callback_t>
  void execute(task_t&& task, callback_t&& callback) {
    auto workers_task = std::make_shared<std::packaged_task<void()>>(std::bind(
        std::forward<callback_t>(callback), std::forward<task_t>(task)));
    {
      std::unique_lock<std::mutex> lock(_mutex);
      _tasks_queue.emplace([workers_task] { (*workers_task)(); });
    }
    _available_to_job.notify_one();
  }

 private:
  std::vector<std::thread> _worker_threads;
  std::queue<std::function<void()>> _tasks_queue;
  std::mutex _mutex;
  std::condition_variable _available_to_job;
  bool _is_stopped;
};

#endif  // BFSYSTEM_THREAD_POOL_HPP
