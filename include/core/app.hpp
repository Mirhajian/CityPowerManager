#ifndef APP_HPP
#define APP_HPP

#include "../utils/file_io.hpp"
#include "../models/tariff.hpp"
#include <memory>
#include <vector>

class App {
public:
  std::vector<ResidentialSubscriber> residentialSubscribers;
  std::vector<CommercialSubscriber> commercialSubscribers;
  std::vector<IndustrialSubscriber> industrialSubscribers;
  // std::vector<Tariff*> tariffs;  // DEPRICATED: replaced by unique_ptr

  void displayTariffs();  // Do not move this into private

  App();
  ~App();

  void run();

private:
  std::vector<std::unique_ptr<Tariff>> tariffs;  // Store tariffs as unique pointers
  FileIO fileIO;

  void showMainMenu();
  void clearScreen() const;
  void handleMenuOption(char option);
  void handleNewSubMenu();
  void handleDisSubMenu();
  void handleEdiSubMenu();
  void handleNewTarMenu();
  void handleDisTarMenu();
  void handleEdiTarMenu();
  void handleBillingIss();

  void addNewSubscriber(char type);
  void displaySubscribers(char type);
  void editSubscriber(char type);
  // void editTariffs(); NO NEED
  // void issueBill(); NO NEED

  // New helper methods, avoid warnings that nvim lsp gives
  template<typename T>
  void addSubscriber(std::vector<T>& subscribers, const std::string& type);

  template<typename T>
  void editSubscriberOfType(std::vector<T>& subscribers, const std::string& type);

  template<typename T>
  void displaySubscribers(const std::vector<T>& subscribers, const std::string& type);

  template<typename T>
  std::shared_ptr<T> findSubscriber(const std::vector<T>& subscribers, const std::string& meterNumber);

  void saveSubscribers();
};

#endif  // APP_HPP
