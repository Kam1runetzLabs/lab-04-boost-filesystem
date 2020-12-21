// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef INCLUDE_BROKERS_ANALYSE_FINANCIAL_FILE_HPP_
#define INCLUDE_BROKERS_ANALYSE_FINANCIAL_FILE_HPP_

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

#endif  // INCLUDE_BROKERS_ANALYSE_FINANCIAL_FILE_HPP_
