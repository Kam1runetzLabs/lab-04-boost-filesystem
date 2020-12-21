// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef BFSYSTEM_FINANCIAL_FILE_HPP
#define BFSYSTEM_FINANCIAL_FILE_HPP

#include <string>

namespace brokers_analyse {
class financial_file {
 public:
  financial_file() = default;
  financial_file(std::string name, std::string date);
  std::string name() const;
  void set_name(const std::string &name);

  std::string date() const;
  void set_date(const std::string &date);

  bool valid() const;

 private:
  std::string _name;
  std::string _date;
};
}  // namespace brokers_analyse

#endif  // BFSYSTEM_FINANCIAL_FILE_HPP
