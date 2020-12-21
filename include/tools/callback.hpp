// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef INCLUDE_TOOLS_CALLBACK_HPP_
#define INCLUDE_TOOLS_CALLBACK_HPP_

#include <functional>
#include <utility>

template <typename task_t, typename... args_t>
inline auto CALLBACK(task_t&& task, args_t&&... args) {
  return std::bind(std::forward<task_t>(task), std::placeholders::_1,
                   std::forward<args_t>(args)...);
}

#endif  // INCLUDE_TOOLS_CALLBACK_HPP_
