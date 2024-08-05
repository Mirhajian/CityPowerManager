#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <string>

class Subscriber {
public:
  Subscriber(const std::string& name, const std::string& lastName,
             const std::string& nationalID, const std::string& meterNumber,
             const std::string& installationDate);

  virtual ~Subscriber() = default;

  const std::string& getName() const;
  const std::string& getLastName() const;
  const std::string& getNationalID() const;
  const std::string& getMeterNumber() const;
  const std::string& getInstallationDate() const;
  const double getDebt() const;

  void setName(const std::string& name);
  void setLastName(const std::string& lastName);
  void setNationalID(const std::string& nationalID);
  void setMeterNumber(const std::string& meterNumber);
  void setInstallationDate(const std::string& installationDate);
  void setDebt(double debt);

private:
  std::string name;
  std::string lastName;
  std::string nationalID;
  std::string meterNumber;
  std::string installationDate;
  double debt;
};

#endif  // SUBSCRIBER_HPP
