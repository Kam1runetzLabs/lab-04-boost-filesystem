//
// Created by w1ckedente on 14.12.2020.
//

#ifndef BFSYSTEM_THREAD_SAFE_QUEUE_HPP
#define BFSYSTEM_THREAD_SAFE_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class thread_safe_queue {
 public:
  thread_safe_queue();
  thread_safe_queue(const thread_safe_queue<T> &) = delete;
  thread_safe_queue &operator=(const thread_safe_queue<T> &) = delete;

  void enqueue(T &&value);

  template <typename... args_t>
  void emplace(args_t &&... args);

  T pop();

 private:
  std::mutex mutex;
  std::condition_variable empty;
  std::queue<T> container;
};

template <typename T>
thread_safe_queue<T>::thread_safe_queue() : mutex(), empty(), container() {}

template <typename T>
void thread_safe_queue<T>::enqueue(T &&value) {
  std::unique_lock<std::mutex> lock(mutex);
  container.push(std::forward<T>(value));
  empty.notify_all();
}

template <typename T>
T thread_safe_queue<T>::pop() {
  std::unique_lock<std::mutex> lock(mutex);
  while (container.empty()) {
    empty.wait(lock);
  }
  auto ret = std::move(container.front());
  container.pop();
  return ret;
}

template <typename T>
template <typename... args_t>
void thread_safe_queue<T>::emplace(args_t &&... args) {
  std::unique_lock<std::mutex> lock(mutex);
  container.emplace(std::forward<args_t...>(args)...);
  empty.notify_all();
}

#endif  // BFSYSTEM_THREAD_SAFE_QUEUE_HPP
