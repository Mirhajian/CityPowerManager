#ifndef INDUSTRIAL_SUBSCRIBER_HPP
#define INDUSTRIAL_SUBSCRIBER_HPP

#include <string>

#include "subscriber.hpp"

class IndustrialSubscriber : public Subscriber {
public:
  IndustrialSubscriber(const std::string& name, const std::string& lastName,
                       const std::string& nationalID, const std::string& meterNumber,
                       const std::string& installationDate, const std::string& unitName,
                       double supplyVoltage, const std::string& connectionType,
                       double meterMultiplier, double transformerRatio);

  const std::string& getUnitName() const;
  double getSupplyVoltage() const;
  const std::string& getConnectionType() const;
  double getMeterMultiplier() const;
  double getTransformerRatio() const;

  void setUnitName(const std::string& unitName);
  void setSupplyVoltage(double supplyVoltage);
  void setConnectionType(const std::string& connectionType);
  void setMeterMultiplier(double meterMultiplier);
  void setTransformerRatio(double transformerRatio);
  friend std::ostream& operator<<(std::ostream& os, const IndustrialSubscriber& sub);

private:
  std::string unitName;
  double supplyVoltage;
  std::string connectionType;
  double meterMultiplier;
  double transformerRatio;
};

#endif  // INDUSTRIAL_SUBSCRIBER_HPP
