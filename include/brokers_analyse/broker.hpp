//
// Created by w1ckedente on 15.12.2020.
//

#ifndef BFSYSTEM_BROKER_HPP
#define BFSYSTEM_BROKER_HPP

#include <brokers_analyse/financial_file.hpp>
#include <set>
#include <string>
#include <vector>

namespace brokers_analyse {
class broker {
 public:
  broker();
  broker(std::string name, std::set<std::string> accounts,
         std::vector<financial_file> files);

  std::string name() const;
  std::set<std::string> accounts() const;
  std::vector<financial_file> files() const;
  bool is_valid() const;

 private:
  std::string name_;
  std::set<std::string> accounts_;
  std::vector<financial_file> files_;
};
}  // namespace brokers_analyse

#endif  // BFSYSTEM_BROKER_HPP
