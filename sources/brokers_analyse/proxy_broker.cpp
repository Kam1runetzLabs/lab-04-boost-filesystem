//
// Created by w1ckedente on 15.12.2020.
//

#include <brokers_analyse/proxy_broker.hpp>
#include <future>

using namespace brokers_analyse;

_proxy_broker::_proxy_broker(std::future<broker> &&f_broker)
    : f_broker_(std::move(f_broker)) {}

_proxy_broker::_proxy_broker(_proxy_broker &&other) noexcept {
  f_broker_ = std::move(other.f_broker_);
}

broker _proxy_broker::get_broker_data() { return f_broker_.get(); }
