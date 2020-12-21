//
// Created by w1ckedente on 16.12.2020.
//

#ifndef BFSYSTEM_BROKER_HPP
#define BFSYSTEM_BROKER_HPP

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

#endif  // BFSYSTEM_BROKER_HPP
