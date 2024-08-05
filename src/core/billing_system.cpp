#include <ctime>
#include <iostream>

#include "../../include/core/billing_system.hpp"

BillingSystem::BillingSystem() : rng(std::random_device {}()), dist(0.0, 1.0) {}

double BillingSystem::generateRandomConsumption() {
  return dist(rng) * 6.0;  // *6.0 to convert to hours
}

double BillingSystem::getMultiplier(int period) const {
  switch (period) {
    case 0: return 1.0;  // 12 am to 6 am: medium
    case 1: return 0.5;  // 6 am to 12 pm: light
    case 2: return 2.0;  // 12 pm to 6 pm: peak
    case 3: return 1.0;  // 6 pm to 12 am: medium
    default: return 2.0;
  }
}

double BillingSystem::calculateBill(double consumption, const Tariff* tariff, const std::string& subscriberType) {
  double bill = 0.0;

  if (subscriberType == "Residential" || subscriberType == "Commercial") {
    auto tierTariff = tariff->readTariffFromCSV(subscriberType);
    for (const auto& tier : tierTariff) {
      size_t dashPos = tier.first.find('-');
      double lowerBound = std::stod(tier.first.substr(0, dashPos));
      double upperBound = (dashPos != std::string::npos) ? std::stod(tier.first.substr(dashPos + 1)) : std::numeric_limits<double>::max();

      if (consumption > lowerBound) {
        double tierConsumption = std::min(consumption - lowerBound, upperBound - lowerBound);
        bill += tierConsumption * tier.second;
      }

      if (consumption <= upperBound) break;
    }
  } else if (subscriberType == "Industrial") {
      auto industrialTariff = tariff->readIndustrialTariffFromCSV();
      bill = consumption * industrialTariff["medium_pressure"];  // Using medium_pressure as default
  }

  return bill;
}

void BillingSystem::issueBills(std::vector<ResidentialSubscriber>& residentialSubscribers,
                               std::vector<CommercialSubscriber>& commercialSubscribers,
                               std::vector<IndustrialSubscriber>& industrialSubscribers,
                               const std::vector<std::unique_ptr<Tariff>>& tariffs) {
  for (auto& subscriber : residentialSubscribers) {
    double totalConsumption = 0.0;
    for (int day = 0; day < 30; ++day) {
      for (int period = 0; period < 4; ++period) {
        double consumption = generateRandomConsumption() * getMultiplier(period);
        totalConsumption += consumption;
      }
    }
    double bill = calculateBill(totalConsumption, tariffs[0].get(), "Residential");
    subscriber.setDebt(subscriber.getDebt() + bill);
    std::cout << "Residential subscriber " << subscriber.getName() << " " << subscriber.getLastName() 
              << " (Meter: " << subscriber.getMeterNumber() << ") bill: $" << bill << std::endl;
  }

  for (auto& subscriber : commercialSubscribers) {
    double totalConsumption = 0.0;
    for (int day = 0; day < 30; ++day) {
      for (int period = 0; period < 4; ++period) {
        double consumption = generateRandomConsumption() * getMultiplier(period);
        totalConsumption += consumption;
      }
    }
    double bill = calculateBill(totalConsumption, tariffs[1].get(), "Commercial");
    subscriber.setDebt(subscriber.getDebt() + bill);
    std::cout << "Commercial subscriber " << subscriber.getName() << " " << subscriber.getLastName() 
              << " (Meter: " << subscriber.getMeterNumber() << ") bill: $" << bill << std::endl;
  }

  for (auto& subscriber : industrialSubscribers) {
    double totalConsumption = 0.0;
    for (int day = 0; day < 30; ++day) {
      for (int period = 0; period < 4; ++period) {
          double consumption = generateRandomConsumption() * getMultiplier(period);
          totalConsumption += consumption;
      }
    }
    double bill = calculateBill(totalConsumption, tariffs[2].get(), "Industrial");
    subscriber.setDebt(subscriber.getDebt() + bill);
    std::cout << "Industrial subscriber " << subscriber.getName() << " " << subscriber.getLastName() 
              << " (Meter: " << subscriber.getMeterNumber() << ") bill: $" << bill << std::endl;
  }
}
