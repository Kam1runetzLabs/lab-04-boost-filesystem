//
// Created by w1ckedente on 18.12.2020.
//

#ifndef BFSYSTEM_CALLBACK_HPP
#define BFSYSTEM_CALLBACK_HPP

#include <functional>
#include <utility>

template <typename task_t, typename... args_t>
inline auto CALLBACK(task_t&& task, args_t&&... args) {
  return std::bind(std::forward<task_t>(task), std::placeholders::_1,
                   std::forward<args_t>(args)...);
}

#endif  // BFSYSTEM_CALLBACK_HPP
