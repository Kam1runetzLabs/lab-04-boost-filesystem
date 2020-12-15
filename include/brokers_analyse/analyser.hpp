//
// Created by w1ckedente on 15.12.2020.
//

#ifndef BFSYSTEM_ANALYSER_HPP
#define BFSYSTEM_ANALYSER_HPP

#include <boost/filesystem.hpp>
#include <brokers_analyse/broker.hpp>
#include <brokers_analyse/financial_file.hpp>

namespace brokers_analyse {
using d_iter = boost::filesystem::directory_iterator;
using d_path = boost::filesystem::path;

broker analyse_broker(const d_path &broker_dir_path);
broker analyse_broker(const std::string &broker_dir_path);
std::vector<broker> analyse_all_brokers(const std::string &brokers_dir_path);
}  // namespace brokers_analyse
#endif  // BFSYSTEM_ANALYSER_HPP
