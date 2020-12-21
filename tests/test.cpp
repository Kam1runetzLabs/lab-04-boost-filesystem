// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <brokers_analyse.hpp>
#include <iostream>
#include <vector>

using namespace brokers_analyse;

void broker_processing(const broker &brok) {
  if (brok.valid()) std::cout << brok.name() << std::endl;
}

TEST(Example, EmptyTest) {
  analyse_all(policy::parallel, "../misc/ftp", broker_processing);
  EXPECT_TRUE(true);
}
