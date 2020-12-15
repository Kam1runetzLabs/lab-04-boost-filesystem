//
// Created by w1ckedente on 15.12.2020.
//
#include <algorithm>
#include <brokers_analyse/broker.hpp>
#include <utility>

using namespace brokers_analyse;

broker::broker() : name_(), accounts_(), files_() {}

broker::broker(std::string name, std::set<std::string> accounts,
               std::vector<financial_file> files)
    : name_(std::move(name)),
      accounts_(std::move(accounts)),
      files_(std::move(files)) {}

std::string broker::name() const { return name_; }

std::set<std::string> broker::accounts() const { return accounts_; }

std::vector<financial_file> broker::files() const { return files_; }

bool broker::is_valid() const {
  return !(accounts_.empty() || files_.empty() || name_.empty()) &&
         std::all_of(
             accounts_.cbegin(), accounts_.cend(),
             [](const std::string &acc) { return acc.length() == 8; }) &&
         std::all_of(
             files_.cbegin(), files_.cend(),
             [](const financial_file &file) { return file.is_valid(); });
}
