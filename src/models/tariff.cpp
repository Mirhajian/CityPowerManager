#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../include/models/tariff.hpp"
#include "../../include/utils/file_io.hpp"

std::vector<std::pair<std::string, double>> Tariff::readTariffFromCSV(const std::string& type) const {
  std::vector<std::pair<std::string, double>> tariff;
  std::ifstream file("../data/tariffs.csv");
  std::string line;

  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string csvType, tier;
    double value;

    if (std::getline(iss, csvType, ',') &&
        std::getline(iss, tier, ',') &&
        iss >> value) {
      if (csvType == type) {
        tariff.emplace_back(tier, value);
      }
    }
  }

  return tariff;
}

std::map<std::string, double> Tariff::readIndustrialTariffFromCSV() const {
  std::map<std::string, double> tariff;
  std::ifstream file("../data/tariffs.csv");
  std::string line;

  // Skip header
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string csvType, tier;
    double value;

    if (std::getline(iss, csvType, ',') &&
        std::getline(iss, tier, ',') &&
        iss >> value) {
      if (csvType == "Industrial") {
        tariff[tier] = value;
      }
    }
  }

  return tariff;
}

double Tariff::getMultiplier(const int& period) const {
  switch (period) {
    case 0: return 1.0;  // 12 am to 6 am: medium
    case 1: return 0.5;  // 6 am to 12 pm: light
    case 2: return 2.0;  // 12 pm to 6 pm: peak
    case 3: return 1.0;  // 6 pm to 12 am: medium
    default: return 1.0;
  }
}

std::string ResidentialTariff::getTariffInfo() const {
  auto tariff = readTariffFromCSV("Residential");
  for (const auto& tier : tariff) {
    std::cout << tier.first << ": " << tier.second << std::endl;
  }
  return "Residential tariff info displayed";
}

std::string CommercialTariff::getTariffInfo() const {
  auto tariff = readTariffFromCSV("Commercial");
  for (const auto& tier : tariff) {
    std::cout << tier.first << ": " << tier.second << std::endl;
  }
  return "Commercial tariff info displayed";
}

std::string IndustrialTariff::getTariffInfo() const {
  auto tariff = readIndustrialTariffFromCSV();
  for (const auto& rate : tariff) {
    std::cout << rate.first << ": " << rate.second << std::endl;
  }
  return "Industrial tariff info displayed";
}
