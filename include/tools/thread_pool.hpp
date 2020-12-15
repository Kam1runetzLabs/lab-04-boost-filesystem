//
// Created by w1ckedente on 14.12.2020.
//

#ifndef BFSYSTEM_THREAD_POOL_HPP
#define BFSYSTEM_THREAD_POOL_HPP

#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <tools/thread_safe_queue.hpp>
#include <vector>

class thread_pool {
 public:
  explicit thread_pool(
      std::size_t workers_count = std::thread::hardware_concurrency());
  thread_pool(const thread_pool &) = delete;
  template <typename task_t, typename... args_t>
  std::future<typename std::result_of<task_t(args_t...)>::type> enqueue_task(
      task_t &&task, args_t &&... args);
  ~thread_pool();

 private:
  std::vector<std::thread> workers_;
  thread_safe_queue<std::function<void(void)>> tasks_;
};

template <typename task_t, typename... args_t>
std::future<typename std::result_of<task_t(args_t...)>::type>
thread_pool::enqueue_task(task_t &&task, args_t &&... args) {
  using ret_t = typename std::result_of<task_t(args_t...)>::type;
  auto packaged_task = std::make_shared<std::packaged_task<ret_t()>>(
      std::bind(std::forward<task_t>(task), std::forward<args_t>(args)...));
  auto res = packaged_task->get_future();
  tasks_.emplace([packaged_task] { (*packaged_task)(); });
  return res;
}

#endif  // BFSYSTEM_THREAD_POOL_HPP
