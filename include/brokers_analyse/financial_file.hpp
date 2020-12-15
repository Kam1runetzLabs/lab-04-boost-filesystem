//
// Created by w1ckedente on 15.12.2020.
//

#ifndef BFSYSTEM_FINANCIAL_FILE_HPP
#define BFSYSTEM_FINANCIAL_FILE_HPP

#include <string>

const std::size_t date_string_length = 8;
const std::size_t account_string_length = 8;
const std::string file_type_string = "balance";

namespace brokers_analyse {
class financial_file {
 public:
  financial_file();
  financial_file(std::string account, std::string date);
  std::string file_name() const;

  std::string account() const;
  std::string date() const;

  bool is_valid() const;

 private:
  std::string account_;
  std::string date_;
};
}  // namespace brokers_analyse

#endif  // BFSYSTEM_FINANCIAL_FILE_HPP
