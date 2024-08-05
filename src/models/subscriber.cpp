#include "../../include/models/subscriber.hpp"

Subscriber::Subscriber(const std::string& name, const std::string& lastName,
                       const std::string& nationalID, const std::string& meterNumber,
                       const std::string& installationDate)
    : name(name), lastName(lastName), nationalID(nationalID), meterNumber(meterNumber),
      installationDate(installationDate) {}

const std::string& Subscriber::getName() const {
  return name;
}

const std::string& Subscriber::getLastName() const {
  return lastName;
}

const std::string& Subscriber::getNationalID() const {
  return nationalID;
}

const std::string& Subscriber::getMeterNumber() const {
  return meterNumber;
}

const std::string& Subscriber::getInstallationDate() const {
  return installationDate;
}

void Subscriber::setName(const std::string& name) {
  this->name = name;
}

void Subscriber::setLastName(const std::string& lastName) {
  this->lastName = lastName;
}

void Subscriber::setNationalID(const std::string& nationalID) {
  this->nationalID = nationalID;
}

void Subscriber::setMeterNumber(const std::string& meterNumber) {
  this->meterNumber = meterNumber;
}

void Subscriber::setInstallationDate(const std::string& installationDate) {
  this->installationDate = installationDate;
}

void Subscriber::setDebt(double debt) {
  this->debt = debt;
}

double const Subscriber::getDebt() const {
  return debt;
}
