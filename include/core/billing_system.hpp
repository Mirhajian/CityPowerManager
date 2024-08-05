#ifndef BILLING_SYSTEM_HPP
#define BILLING_SYSTEM_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <map>
#include <utility>
#include <memory>
#include "../models/tariff.hpp"
#include "../models/residential_subscriber.hpp"
#include "../models/commercial_subscriber.hpp"
#include "../models/industrial_subscriber.hpp"

class BillingSystem {
public:
  BillingSystem();
  void issueBills(std::vector<ResidentialSubscriber>& residentialSubscribers,
                  std::vector<CommercialSubscriber>& commercialSubscribers,
                  std::vector<IndustrialSubscriber>& industrialSubscribers,
                  const std::vector<std::unique_ptr<Tariff>>& tariffs);
  double calculateResidentialBill(const std::vector<std::pair<std::string, double>>& tariff);
  double calculateCommercialBill(const std::vector<std::pair<std::string, double>>& tariff);
  double calculateIndustrialBill(const std::map<std::string, double>& tariff);

  double getRandHours() const;
private:
  // double getMultiplier(int hour) const; // DEPRICATED

  // these are for the getRandHours(), they generate random results
  std::mt19937 rng;
  std::uniform_real_distribution<> dist;

  double generateRandomConsumption();
  double getMultiplier(int period) const;
  double calculateBill(double consumption, const Tariff* tariff, const std::string& subscriberType);
};

#endif  // BILLING_SYSTEM_HPP
