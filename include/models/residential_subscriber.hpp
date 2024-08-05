#ifndef RESIDENTIAL_SUBSCRIBER_HPP
#define RESIDENTIAL_SUBSCRIBER_HPP

#include "subscriber.hpp"

class ResidentialSubscriber : public Subscriber {
public:
  ResidentialSubscriber(const std::string& name, const std::string& lastName,
                        const std::string& nationalID, const std::string& meterNumber,
                        const std::string& installationDate);

  friend std::ostream& operator<<(std::ostream& os, const ResidentialSubscriber& sub);
};

#endif  // RESIDENTIAL_SUBSCRIBER_HPP
