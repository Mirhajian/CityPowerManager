#ifndef TARIFF_HPP
#define TARIFF_HPP

#include <map>
#include <string>
#include <utility>
#include <vector>

class Tariff {
public:
  std::string type;
  std::string tier;
  double price;

  virtual ~Tariff() = default;

  std::vector<std::pair<std::string, double>> readTariffFromCSV(const std::string& type) const;
  std::map<std::string, double> readIndustrialTariffFromCSV() const;
  double getMultiplier(const int& period) const;

  virtual std::string getTariffInfo() const = 0;
};

class ResidentialTariff : public Tariff {
public:
  std::string getTariffInfo() const override;
};

class CommercialTariff : public Tariff {
public:
  std::string getTariffInfo() const override;
};

class IndustrialTariff : public Tariff {
public:
  std::string getTariffInfo() const override;
};

std::vector<Tariff> readTariffs(const std::string& filename);
void writeTariffs(const std::string& filename, const std::vector<Tariff>& tariffs);

#endif  // TARIFF_HPP
