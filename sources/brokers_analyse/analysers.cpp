//
// Created by w1ckedente on 17.12.2020.
//

#include <algorithm>
#include <boost/filesystem.hpp>
#include <brokers_analyse/analysers.hpp>
#include <brokers_analyse/broker.hpp>
#include <brokers_analyse/definitions.hpp>
#include <string>
#include <vector>

namespace brokers_analyse {

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

void _processing_filename(const std::string &filename, acc_files_map &files) {
  auto filename_tokens = _split_string(filename);
  if (filename_tokens.size() != filename_tokens_count) return;

  auto type = filename_tokens[0];
  auto account = filename_tokens[1];
  auto date = filename_tokens[2];

  if (type != file_type) return;
  if (account.length() != account_length) return;
  if (date.length() != date_length) return;

  files[account].emplace_back(filename, date);
}

broker analyse_one(const std::string &path) {
  std::string name;
  acc_files_map files;

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
    _processing_filename(entry.path().filename().stem().string(), files);
  }
  return broker(name, files);
}
}  // namespace brokers_analyse
