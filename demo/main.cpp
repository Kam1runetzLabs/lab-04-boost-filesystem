#include <brokers_analyse.hpp>
#include <chrono>
#include <iostream>

using namespace brokers_analyse;

std::string lastdate(const std::vector<financial_file> &files) {
  int res{0};
  for (const auto &file : files) {
    res = std::max(res, std::stoi(file.date()));
  }
  return std::to_string(res);
}

void broker_processing(const broker &brok) {
  if (brok.valid()) {
    for (const auto &af_pair : brok.files()) {
      std::cout << "broker:" << brok.name() << " account:" << af_pair.first
                << " files:" << af_pair.second.size()
                << " lastdate:" << lastdate(af_pair.second) << std::endl;
    }
  }
}

void printing_files(const broker &brok) {
  if (brok.valid()) {
    for (const auto &af_pair : brok.files()) {
      for (const auto &file : af_pair.second) {
        std::cout << brok.name() << " " << file.name() << std::endl;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  std::string directory = (argc < 2 ? "." : argv[1]);
  analyse_all(policy::parallel, directory, broker_processing);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  analyse_all(policy::serial, directory, printing_files);
  return 0;
}