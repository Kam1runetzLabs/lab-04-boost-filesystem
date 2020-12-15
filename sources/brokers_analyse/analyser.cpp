//
// Created by w1ckedente on 15.12.2020.
//

#include <boost/filesystem.hpp>
#include <brokers_analyse/analyser.hpp>
#include <brokers_analyse/broker.hpp>
#include <brokers_analyse/financial_file.hpp>
#include <iostream>
#include <string>
#include <tools/thread_pool.hpp>
#include <vector>

using namespace brokers_analyse;

inline bool is_separator(char c) { return c == '_'; }

inline bool is_not_separator(char c) { return !is_separator(c); }

std::vector<std::string> split_string(const std::string &text) {
  std::vector<std::string> ret;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = std::find_if(i, text.cend(), is_not_separator);
    auto j = std::find_if(i, text.cend(), is_separator);
    ret.emplace_back(i, j);
    i = j;
  }
  return ret;
}

financial_file parse_filename(const d_path &path) {
  if (path.extension().string() == ".txt") return financial_file();
  auto filename = path.stem().string();
  auto filename_tokens = split_string(filename);
  if (filename_tokens.size() != 3) return financial_file();
  if (filename_tokens[0] != file_type_string) return financial_file();
  if (filename_tokens[1].length() != account_string_length)  // account
    return financial_file();
  if (filename_tokens[2].length() != date_string_length)  // date
    return financial_file();

  return financial_file(filename_tokens[1], filename_tokens[2]);
}

broker analyse_broker(const d_path &broker_dir_path) {
  using dir_iter = boost::filesystem::directory_iterator;
  std::set<std::string> accounts;
  std::vector<financial_file> files;
  auto broker_name = broker_dir_path.filename().string();

  for (const auto &entry : dir_iter{broker_dir_path}) {
    if (!boost::filesystem::is_directory(entry)) {
      auto file = parse_filename(entry.path().filename());
      files.push_back(file);
      accounts.insert(file.account());
    }
  }
  return broker(broker_name, accounts, files);
}

std::vector<_proxy_broker> analyse_all_brokers::operator()(
    const std::string &brok_dir) {
  auto brokers_dir = d_path{brok_dir};
  std::vector<_proxy_broker> result;
  for (const auto &broker_entry : d_iter{brokers_dir}) {
    auto tmp = pool_.enqueue_task(analyse_broker, broker_entry);
    result.emplace_back(std::move(tmp));
  }
  return result;
}
