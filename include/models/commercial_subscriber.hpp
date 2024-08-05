#ifndef COMMERCIAL_SUBSCRIBER_HPP
#define COMMERCIAL_SUBSCRIBER_HPP

#include <string>

#include "subscriber.hpp"

class CommercialSubscriber : public Subscriber {
public:
  CommercialSubscriber(const std::string& name, const std::string& lastName,
                       const std::string& nationalID, const std::string& meterNumber,
                       const std::string& installationDate, double meterCapacity,
                       const std::string& businessLicense);

  double getMeterCapacity() const;
  const std::string& getBusinessLicense() const;

  void setMeterCapacity(double meterCapacity);
  void setBusinessLicense(const std::string& businessLicense);

  friend std::ostream& operator<<(std::ostream& os, const CommercialSubscriber& sub);

private:
  double meterCapacity;
  std::string businessLicense;
};

#endif  // COMMERCIAL_SUBSCRIBER_HPP
