// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <brokers_analyse.hpp>
#include <iostream>
#include <vector>

using namespace brokers_analyse;
TEST(Example, EmptyTest) {
  auto brokers = analyse_all(policy::parallel, "../misc/ftp");
  std::cout << "TOTAL BROKERS: " << brokers.size() << std::endl;
  for (const auto &broker : brokers) {
    std::cout << broker.name << " files: " << broker.files.size() << " files"
              << std::endl;
  }
  EXPECT_TRUE(true);
}
