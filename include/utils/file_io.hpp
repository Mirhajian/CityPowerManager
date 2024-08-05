#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <map>
#include <string>
#include <vector>

#include "../models/commercial_subscriber.hpp"
#include "../models/industrial_subscriber.hpp"
#include "../models/residential_subscriber.hpp"
#include "../models/tariff.hpp"

class FileIO {
public:
  static std::vector<std::string> splitCSVLine(const std::string& line);
  static std::vector<ResidentialSubscriber> readResidentialSubscribers(const std::string& filename);
  static std::vector<CommercialSubscriber> readCommercialSubscribers(const std::string& filename);
  static std::vector<IndustrialSubscriber> readIndustrialSubscribers(const std::string& filename);

  static void writeResidentialSubscribers(const std::string& filename, const std::vector<ResidentialSubscriber>& subscribers);
  static void writeCommercialSubscribers(const std::string& filename, const std::vector<CommercialSubscriber>& subscribers);
  static void writeIndustrialSubscribers(const std::string& filename, const std::vector<IndustrialSubscriber>& subscribers);

  std::vector<std::vector<std::string>> readTariffsFromCSV(const std::string& filename);
  void writeTariffsToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& tariffs);
};

#endif  // FILE_IO_HPP
