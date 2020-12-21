// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef INCLUDE_BROKERS_ANALYSE_BROKER_HPP_
#define INCLUDE_BROKERS_ANALYSE_BROKER_HPP_

#include <brokers_analyse/financial_file.hpp>
#include <map>
#include <string>
#include <vector>

namespace brokers_analyse {
using acc_files_map = std::map<std::string, std::vector<financial_file>>;
class broker {
 public:
  broker() = default;
  broker(std::string name, acc_files_map files);
  std::string name() const;
  void set_name(const std::string &name);

  acc_files_map files() const;
  void insert_file(const std::string &account, const financial_file &file);

  bool valid() const;

 private:
  std::string _name;
  acc_files_map _files;
};
}  // namespace brokers_analyse

#endif  // INCLUDE_BROKERS_ANALYSE_BROKER_HPP_
