//
// Created by w1ckedente on 15.12.2020.
//

#ifndef BFSYSTEM_PROXY_BROKER_HPP
#define BFSYSTEM_PROXY_BROKER_HPP

#include <brokers_analyse/broker.hpp>
#include <future>

namespace brokers_analyse {
class _proxy_broker {
 public:
  explicit _proxy_broker(std::future<broker> &&f_broker);
  _proxy_broker(const _proxy_broker &) = delete;
  _proxy_broker(_proxy_broker &&other) noexcept;

  broker get_broker_data();

 private:
  std::future<broker> f_broker_;
};
}  // namespace brokers_analyse
#endif  // BFSYSTEM_PROXY_BROKER_HPP
