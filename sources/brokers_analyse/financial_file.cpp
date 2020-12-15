//
// Created by w1ckedente on 15.12.2020.
//

#include <brokers_analyse/financial_file.hpp>
#include <string>
#include <utility>

using namespace brokers_analyse;

financial_file::financial_file() : account_(), date_() {}

financial_file::financial_file(std::string account, std::string date)
    : account_(std::move(account)), date_(std::move(date)) {}

std::string financial_file::file_name() const {
  std::string ret;
  ret += "balance_" + account_ + "_" + date_ + ".txt";
  return ret;
}

std::string financial_file::account() const { return account_; }

std::string financial_file::date() const { return date_; }

bool financial_file::is_valid() const {
  return date_.length() == 8 && account_.length() == 8;
}
