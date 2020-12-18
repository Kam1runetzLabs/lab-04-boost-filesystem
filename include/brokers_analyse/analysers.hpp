//
// Created by w1ckedente on 16.12.2020.
//

#ifndef BFSYSTEM_ANALYSERS_HPP
#define BFSYSTEM_ANALYSERS_HPP

#include <brokers_analyse/broker.hpp>
#include <string>
#include <tools/callback.hpp>
#include <tools/task.hpp>
#include <tools/thread_pool.hpp>
#include <vector>

namespace brokers_analyse {
using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

// todo thread safe vector
// todo default callback

enum policy { parallel, serial };
broker analyse_one(const d_entry &entry);
broker analyse_one(const std::string &path);

std::vector<broker> analyse_all(policy pol, const std::string &path);

}  // namespace brokers_analyse

#endif  // BFSYSTEM_ANALYSERS_HPP
