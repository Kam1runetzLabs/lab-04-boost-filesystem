// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef INCLUDE_BROKERS_ANALYSE_ANALYSERS_HPP_
#define INCLUDE_BROKERS_ANALYSE_ANALYSERS_HPP_

#include <boost/filesystem.hpp>
#include <brokers_analyse/broker.hpp>
#include <string>
#include <tools/callback.hpp>
#include <tools/task.hpp>
#include <tools/thread_pool.hpp>
#include <vector>

using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

namespace brokers_analyse {

enum policy { parallel, serial };

broker analyse_one(const std::string &path);

template <typename callback_t, typename... args_t>
void analyse_all(policy pol, const std::string &path, callback_t &&callback,
                 args_t &&...args) {
  const d_path brokers_directory{path};
  if (pol == policy::parallel) {
    thread_pool pool;
    for (const auto &entry : d_iter{brokers_directory}) {
      pool.execute(TASK(analyse_one, entry.path().string()),
                   CALLBACK(std::forward<callback_t>(callback),
                            std::forward<args_t>(args)...));
    }
  } else if (pol == policy::serial) {
    auto cb = CALLBACK(std::forward<callback_t>(callback),
                       std::forward<args_t>(args)...);
    for (const auto &entry : d_iter{brokers_directory}) {
      cb(analyse_one(entry.path().string()));
    }
  } else {
    throw std::runtime_error("invalid execution policy was forward");
  }
}
}  // namespace brokers_analyse

#endif  // INCLUDE_BROKERS_ANALYSE_ANALYSERS_HPP_
