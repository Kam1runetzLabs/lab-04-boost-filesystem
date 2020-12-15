//
// Created by w1ckedente on 15.12.2020.
//

#ifndef BFSYSTEM_ANALYSER_HPP
#define BFSYSTEM_ANALYSER_HPP

#include <boost/filesystem.hpp>
#include <brokers_analyse/broker.hpp>
#include <brokers_analyse/financial_file.hpp>
#include <brokers_analyse/proxy_broker.hpp>
#include <tools/thread_pool.hpp>

namespace brokers_analyse {
using d_iter = boost::filesystem::directory_iterator;
using d_path = boost::filesystem::path;

class analyse_all_brokers {
 public:
  std::vector<_proxy_broker> operator()(const std::string &brokers_dir);

 private:
  thread_pool pool_;
};
}  // namespace brokers_analyse
#endif  // BFSYSTEM_ANALYSER_HPP
