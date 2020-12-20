//
// Created by w1ckedente on 18.12.2020.
//

#ifndef BFSYSTEM_TASK_HPP
#define BFSYSTEM_TASK_HPP

#include <functional>
#include <utility>

template <typename task_t, typename... args_t>
inline auto TASK(task_t&& task, args_t&&... args) {
  return std::bind(std::forward<task_t>(task), std::forward<args_t>(args)...);
}

#endif  // BFSYSTEM_TASK_HPP
