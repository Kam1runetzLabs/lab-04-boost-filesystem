// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <brokers_analyse/broker.hpp>
#include <utility>

namespace brokers_analyse {
broker::broker(std::string name, acc_files_map files)
    : _name(std::move(name)), _files(std::move(files)) {}

std::string broker::name() const { return _name; }

void broker::set_name(const std::string &name) { _name = name; }

acc_files_map broker::files() const { return _files; }

void broker::insert_file(const std::string &account,
                         const financial_file &file) {
  _files[account].push_back(file);
}

bool broker::valid() const { return !(_name.empty() || _files.empty()); }

}  // namespace brokers_analyse
