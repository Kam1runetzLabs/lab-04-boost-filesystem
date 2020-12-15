// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>
#include <brokers_analyse.hpp>
#include <chrono>
#include <iostream>
#include <thread>

// todo переделать парсинг строк

using namespace brokers_analyse;
TEST(Example, EmptyTest) {
  std::vector<_proxy_broker> res;
  analyse_all_brokers all;
  res = all("../misc/ftp");

  for (auto &rr : res) {
    std::cout << rr.get_broker_data().name();
  }

  //  std::this_thread::sleep_for(std::chrono::seconds(5));
  EXPECT_TRUE(true);
}
