#include <fstream>
#include <sstream>
#include <stdexcept>

#include "../../include/utils/file_io.hpp"

std::vector<std::string> FileIO::splitCSVLine(const std::string& line) {
  std::vector<std::string> result;
  std::stringstream ss(line);
  std::string item;
  while (std::getline(ss, item, ',')) {
    result.push_back(item);
  }
  return result;
}

std::vector<ResidentialSubscriber> FileIO::readResidentialSubscribers(const std::string& filename) {
  std::vector<ResidentialSubscriber> subscribers;
  std::ifstream file(filename);
  std::string line;

  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    auto parts = splitCSVLine(line);
    if (parts.size() == 6) {
      subscribers.emplace_back(parts[0], parts[1], parts[2], parts[3], parts[4]);
      subscribers.back().setDebt(std::stod(parts[5]));
    }
  }
  return subscribers;
}

std::vector<CommercialSubscriber> FileIO::readCommercialSubscribers(const std::string& filename) {
  std::vector<CommercialSubscriber> subscribers;
  std::ifstream file(filename);
  std::string line;

  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    auto parts = splitCSVLine(line);
    if (parts.size() == 8) {
      subscribers.emplace_back(parts[0], parts[1], parts[2], parts[3], parts[4], 
                               std::stod(parts[5]), parts[6]);
      subscribers.back().setDebt(std::stod(parts[7]));
    }
  }
  return subscribers;
}

std::vector<IndustrialSubscriber> FileIO::readIndustrialSubscribers(const std::string& filename) {
  std::vector<IndustrialSubscriber> subscribers;
  std::ifstream file(filename);
  std::string line;

  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    auto parts = splitCSVLine(line);
    if (parts.size() == 11) {
      subscribers.emplace_back(parts[0], parts[1], parts[2], parts[3], parts[4], 
                               parts[5], std::stod(parts[6]), parts[7], 
                               std::stod(parts[8]), std::stod(parts[9]));
      subscribers.back().setDebt(std::stod(parts[10]));
    }
  }
  return subscribers;
}

void FileIO::writeResidentialSubscribers(const std::string& filename, const std::vector<ResidentialSubscriber>& subscribers) {
  std::ofstream file(filename);
  file << "Name,LastName,NationalID,MeterNumber,InstallationDate,Debt\n";
  for (const auto& sub : subscribers) {
    file << sub.getName() << "," << sub.getLastName() << "," << sub.getNationalID() << ","
         << sub.getMeterNumber() << "," << sub.getInstallationDate() << "," << sub.getDebt() << "\n";
  }
}

void FileIO::writeCommercialSubscribers(const std::string& filename, const std::vector<CommercialSubscriber>& subscribers) {
  std::ofstream file(filename);
  file << "Name,LastName,NationalID,MeterNumber,InstallationDate,MeterCapacity,BusinessLicense,Debt\n";
  for (const auto& sub : subscribers) {
    file << sub.getName() << "," << sub.getLastName() << "," << sub.getNationalID() << ","
         << sub.getMeterNumber() << "," << sub.getInstallationDate() << ","
         << sub.getMeterCapacity() << "," << sub.getBusinessLicense() << "," << sub.getDebt() << "\n";
  }
}

void FileIO::writeIndustrialSubscribers(const std::string& filename, const std::vector<IndustrialSubscriber>& subscribers) {
  std::ofstream file(filename);
  file << "Name,LastName,NationalID,MeterNumber,InstallationDate,UnitName,SupplyVoltage,ConnectionType,MeterMultiplier,TransformerRatio,Debt\n";
  for (const auto& sub : subscribers) {
    file << sub.getName() << "," << sub.getLastName() << "," << sub.getNationalID() << ","
         << sub.getMeterNumber() << "," << sub.getInstallationDate() << ","
         << sub.getUnitName() << "," << sub.getSupplyVoltage() << ","
         << sub.getConnectionType() << "," << sub.getMeterMultiplier() << ","
         << sub.getTransformerRatio() << "," << sub.getDebt() << "\n";
  }
}

std::vector<std::vector<std::string>> FileIO::readTariffsFromCSV(const std::string& filename) {
  std::vector<std::vector<std::string>> tariffs;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {
      row.push_back(item);
    }

    tariffs.push_back(row);
  }

  return tariffs;
}

void FileIO::writeTariffsToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& tariffs) {
  std::ofstream file(filename);

  for (const auto& row : tariffs) {
    for (size_t i = 0; i < row.size(); ++i) {
      file << row[i];
      if (i < row.size() - 1) {
        file << ",";
      }
    }
    file << "\n";
  }
}
