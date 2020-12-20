//
// Created by w1ckedente on 20.12.2020.
//

#include <algorithm>
#include <brokers_analyse/broker.hpp>

bool brokers_analyse::broker::valid() const {
  return !(name.empty() || accounts.empty() || files.empty()) &&
         std::all_of(accounts.cbegin(), accounts.cend(),
                     [](const std::string &acc) -> bool {
                       return acc.length() == 8;
                     }) &&
         std::all_of(files.cbegin(), files.cend(),
                     [](const financial_file &file) -> bool {
                       return file.date.length() == 8;
                     });
}