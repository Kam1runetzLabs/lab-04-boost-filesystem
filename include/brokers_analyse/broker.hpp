//
// Created by w1ckedente on 16.12.2020.
//

#ifndef BFSYSTEM_BROKER_HPP
#define BFSYSTEM_BROKER_HPP

#include <algorithm>
#include <brokers_analyse/financial_file.hpp>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace brokers_analyse {
struct broker {
  std::string name;
  std::set<std::string> accounts;
  std::vector<financial_file> files;
  bool valid() const;
};
}  // namespace brokers_analyse

#endif  // BFSYSTEM_BROKER_HPP
