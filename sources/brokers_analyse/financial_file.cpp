// Copyright 2020 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <brokers_analyse/definitions.hpp>
#include <brokers_analyse/financial_file.hpp>
#include <utility>

namespace brokers_analyse {
financial_file::financial_file(std::string name, std::string date)
    : _name(std::move(name)), _date(std::move(date)) {}

std::string financial_file::name() const { return _name + ".txt"; }

void financial_file::set_name(const std::string& name) { _name = name; }

std::string financial_file::date() const { return _date; }

void financial_file::set_date(const std::string& date) { _date = date; }

bool financial_file::valid() const {
  return !(_date.empty() || _name.empty()) && _date.length() == date_length;
}
}  // namespace brokers_analyse
