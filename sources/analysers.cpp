//
// Created by w1ckedente on 17.12.2020.
//

#include <algorithm>
#include <boost/filesystem.hpp>
#include <brokers_analyse/analysers.hpp>
#include <brokers_analyse/broker.hpp>
#include <brokers_analyse/financial_file.hpp>
#include <mutex>
#include <set>
#include <string>
#include <tools/callback.hpp>
#include <tools/task.hpp>
#include <tools/thread_pool.hpp>
#include <vector>

// debug
#include <iostream>

using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

namespace brokers_analyse {

static void _default_callback(const broker &brok,
                              std::vector<broker> &brokers) {
  // todo thread safe push to vector
  if (brok.valid()) {
    brokers.push_back(brok);
    std::cout << "DEBUG" << std::endl;
  }
}

static inline bool _is_separator(char c) { return c == '_'; }

static inline bool _not_separator(char c) { return !_is_separator(c); }

static std::vector<std::string> _split_string(const std::string &text) {
  std::vector<std::string> ret;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = std::find_if(i, text.end(), _not_separator);
    auto j = std::find_if(i, text.end(), _is_separator);
    ret.emplace_back(i, j);
    i = j;
  }
  return ret;
}
static void _processing_filename(const std::string &filename,
                                 std::vector<financial_file> &files,
                                 std::set<std::string> &accounts) {
  auto string_tokens = _split_string(filename);
  if (string_tokens.size() != 3) return;
  if (string_tokens[0] != "balance") return;
  if (string_tokens[1].length() != 8) return;
  if (string_tokens[2].length() != 8) return;

  files.push_back(financial_file{string_tokens[1], string_tokens[2]});
  accounts.insert(string_tokens[1]);
}

broker analyse_one(const std::string &path) {
  std::string name;
  std::set<std::string> accounts;
  std::vector<financial_file> files;
  const d_path broker_directory{path};
  if (!boost::filesystem::is_directory(broker_directory))
    throw std::runtime_error(
        "argument must be path to broker directory, not file");
  name = broker_directory.filename().stem().string();
  for (const auto &entry : d_iter{broker_directory}) {
    if (boost::filesystem::is_directory(entry) ||
        !entry.path().filename().stem().extension().string().empty() ||
        entry.path().extension().string() != ".txt")
      continue;
    // todo symlinks processing
    _processing_filename(entry.path().filename().stem().string(), files,
                         accounts);
  }

  return broker{name, accounts, files};
}

std::vector<broker> analyse_all(policy pol, const std::string &path) {
  std::vector<broker> result;
  const d_path brokers_directory{path};
  if (pol == policy::parallel) {
    thread_pool pool;
    for (const auto &entry : d_iter{brokers_directory}) {
      pool.execute(TASK(analyse_one, entry.path().string()),
                   CALLBACK(_default_callback, result));
    }
  } else if (pol == policy::serial) {
    for (const auto &entry : d_iter{brokers_directory}) {
      auto brok = analyse_one(entry.path().string());
      if (brok.valid()) result.push_back(brok);
    }
  } else {
    throw std::runtime_error("invalid execution policy was forward");
  }
  return result;
}
}  // namespace brokers_analyse
