#include <iostream>
#include <string>

#include "../../include/models/commercial_subscriber.hpp"

CommercialSubscriber::CommercialSubscriber(const std::string& name, const std::string& lastName,
                                           const std::string& nationalID, const std::string& meterNumber,
                                           const std::string& installationDate, double meterCapacity,
                                           const std::string& businessLicense)
    : Subscriber(name, lastName, nationalID, meterNumber, installationDate),
      meterCapacity(meterCapacity), businessLicense(businessLicense) {}

double CommercialSubscriber::getMeterCapacity() const {
  return meterCapacity;
}

const std::string& CommercialSubscriber::getBusinessLicense() const {
  return businessLicense;
}

void CommercialSubscriber::setMeterCapacity(double meterCapacity) {
  this->meterCapacity = meterCapacity;
}

void CommercialSubscriber::setBusinessLicense(const std::string& businessLicense) {
  this->businessLicense = businessLicense;
}

std::ostream& operator<<(std::ostream& os, const CommercialSubscriber& sub) {
    os << "Name: " << sub.getName()
       << ", Last Name: " << sub.getLastName()
       << ", National ID: " << sub.getNationalID()
       << ", Meter Number: " << sub.getMeterNumber()
       << ", Installation Date: " << sub.getInstallationDate()
       << ", Meter Capacity: " << sub.getMeterCapacity()
       << ", Business License: " << sub.getBusinessLicense()
       << ", Debt: " << sub.getDebt();
    return os;
}

