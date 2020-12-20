//
// Created by w1ckedente on 16.12.2020.
//

#ifndef BFSYSTEM_ANALYSERS_HPP
#define BFSYSTEM_ANALYSERS_HPP

#include <brokers_analyse/broker.hpp>
#include <deque>
#include <string>
#include <vector>

namespace brokers_analyse {

enum policy { parallel, serial };
broker analyse_one(const std::string &path);
std::vector<broker> analyse_all(policy pol, const std::string &path);
}  // namespace brokers_analyse

#endif  // BFSYSTEM_ANALYSERS_HPP
