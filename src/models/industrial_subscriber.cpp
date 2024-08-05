#include <iostream>
#include <string>

#include "../../include/models/industrial_subscriber.hpp"

IndustrialSubscriber::IndustrialSubscriber(const std::string& name, const std::string& lastName,
                                           const std::string& nationalID, const std::string& meterNumber,
                                           const std::string& installationDate, const std::string& unitName,
                                           double supplyVoltage, const std::string& connectionType,
                                           double meterMultiplier, double transformerRatio)
    : Subscriber(name, lastName, nationalID, meterNumber, installationDate),
      unitName(unitName), supplyVoltage(supplyVoltage), connectionType(connectionType),
      meterMultiplier(meterMultiplier), transformerRatio(transformerRatio) {}

const std::string& IndustrialSubscriber::getUnitName() const {
  return unitName;
}

double IndustrialSubscriber::getSupplyVoltage() const {
  return supplyVoltage;
}

const std::string& IndustrialSubscriber::getConnectionType() const {
  return connectionType;
}

double IndustrialSubscriber::getMeterMultiplier() const {
  return meterMultiplier;
}

double IndustrialSubscriber::getTransformerRatio() const {
  return transformerRatio;
}

void IndustrialSubscriber::setUnitName(const std::string& unitName) {
  this->unitName = unitName;
}

void IndustrialSubscriber::setSupplyVoltage(double supplyVoltage) {
  this->supplyVoltage = supplyVoltage;
}

void IndustrialSubscriber::setConnectionType(const std::string& connectionType) {
  this->connectionType = connectionType;
}

void IndustrialSubscriber::setMeterMultiplier(double meterMultiplier) {
  this->meterMultiplier = meterMultiplier;
}

void IndustrialSubscriber::setTransformerRatio(double transformerRatio) {
  this->transformerRatio = transformerRatio;
}

std::ostream& operator<<(std::ostream& os, const IndustrialSubscriber& sub) {
    os << "Name: " << sub.getName()
       << ", Last Name: " << sub.getLastName()
       << ", National ID: " << sub.getNationalID()
       << ", Meter Number: " << sub.getMeterNumber()
       << ", Installation Date: " << sub.getInstallationDate()
       << ", Unit Number: " << sub.getUnitName()
       << ", Voltage Level: " << sub.getSupplyVoltage()
       << ", Connection Type: " << sub.getConnectionType()
       << ", Transformer Capacity: " << sub.getTransformerRatio()
       << ", Meter meterMultiplier: " << sub.getMeterMultiplier()
       << ", Debt: " << sub.getDebt();
    return os;
}
