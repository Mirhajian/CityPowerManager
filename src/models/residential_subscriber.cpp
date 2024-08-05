#include <iostream>
#include <string>

#include "../../include/models/residential_subscriber.hpp"

ResidentialSubscriber::ResidentialSubscriber(const std::string& name, const std::string& lastName,
                                             const std::string& nationalID, const std::string& meterNumber,
                                             const std::string& installationDate)
    : Subscriber(name, lastName, nationalID, meterNumber, installationDate) {
}

std::ostream& operator<<(std::ostream& os, const ResidentialSubscriber& sub) {
  os << "Name: " << sub.getName()
     << ", Last Name: " << sub.getLastName()
     << ", National ID: " << sub.getNationalID()
     << ", Meter Number: " << sub.getMeterNumber()
     << ", Installation Date: " << sub.getInstallationDate()
     << ", Debt: " << sub.getDebt();

  return os;
}
