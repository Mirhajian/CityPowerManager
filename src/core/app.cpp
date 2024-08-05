#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

#include "../../include/utils/ascii_art.hpp"
#include "../../include/core/app.hpp"
#include "../../include/core/billing_system.hpp"

App::App() {
  try {
    // comment the clearScreen(); method in the App::run() method to ...
    // show the database info to debug databases in /data

    residentialSubscribers = fileIO.readResidentialSubscribers("../data/residential_subscribers.csv");
    commercialSubscribers = fileIO.readCommercialSubscribers("../data/commercial_subscribers.csv");
    industrialSubscribers = fileIO.readIndustrialSubscribers("../data/industrial_subscribers.csv");

    tariffs.emplace_back(std::make_unique<ResidentialTariff>());
    tariffs.emplace_back(std::make_unique<CommercialTariff>());
    tariffs.emplace_back(std::make_unique<IndustrialTariff>());
    // tariffs = fileIO.readTariffs("../data/tariffs.csv");  // DEPRICATED: replaced by above approach with unique_ptr

    std::cout << "Loaded " << residentialSubscribers.size() << " residential subscribers.\n";
    std::cout << "Loaded " << commercialSubscribers.size() << " commercial subscribers.\n";
    std::cout << "Loaded " << industrialSubscribers.size() << " industrial subscribers.\n";
    std::cout << "Loaded " << tariffs.size() << " tariffs.\n";
  } catch (const std::exception& e) {
      std::cerr << "Error loading data: " << e.what() << '\n';
  }
}

App::~App() {
  // DEPRICATED, unique_ptrs handle their own memory, no need to ...
  // delete their memory
  // for (auto tariff : tariffs) {
  //     delete tariff;
  // }
}

void App::showMainMenu() {
  std::cout << CityPowerManager::Art::WELCOME_BANNER << std::endl;
  std::cout << "Menu:\n";
  std::cout << "1. Submit New Subscriber\n";
  std::cout << "2. Display Subscribers\n";
  std::cout << "3. Edit Subscriber\n";
  std::cout << "4. Submit New Tariffs\n";
  std::cout << "5. Display Tariffs\n";
  std::cout << "6. Edit Tariffs\n";
  std::cout << "7. Billing Issuance\n";
  std::cout << "8. Exit\n";
  std::cout << "Enter your choice: ";
}

void App::handleMenuOption(char option) {
  switch (option) {
    case '1':
      handleNewSubMenu();
      break;
    case '2':
      handleDisSubMenu();
      break;
    case '3':
      handleEdiSubMenu();
      break;
    case '4':
      handleNewTarMenu();
      break;
    case '5':
      handleDisTarMenu();
      break;
    case '6':
      handleEdiTarMenu();
      break;
    case '7':
      handleBillingIss();
      break;
    case '8':
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid option. Please try again.\n";
      std::cin.ignore(256, '\n');
      break;
  }
}

void App::handleNewSubMenu() {
  char choice;
  do {
    clearScreen();
    std::cout << CityPowerManager::Art::ADD_NEW_SUBSCRIBER;
    std::cout << "New Subscriber:\n";
    std::cout << "1. Add Residential Subscriber\n";
    std::cout << "2. Add Commercial Subscriber\n";
    std::cout << "3. Add Industrial Subscriber\n";
    std::cout << "4. Back To Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice >= '1' && choice <= '3') {
      addNewSubscriber(choice);
    } else if (choice != '4') {
      std::cout << "Invalid option. Please try again.\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
    }
  } while (choice != '4');
}

void App::handleDisSubMenu() {
  char choice;
  do {
    clearScreen();
    std::cout << CityPowerManager::Art::DISPLAY_SUBS << std::endl;
    std::cout << "Display Subscribers:\n";
    std::cout << "1. Display Residential Subscribers\n";
    std::cout << "2. Display Commercial Subscribers\n";
    std::cout << "3. Display Industrial Subscribers\n";
    std::cout << "4. Back To Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice >= '1' && choice <= '3') {
        displaySubscribers(choice);
    } else if (choice != '4') {
      std::cout << "Invalid option. Please try again.\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
    }
  } while (choice != '4');
}

void App::handleNewTarMenu() {
  clearScreen();
  std::cout << CityPowerManager::Art::ADD_NEW_TARIFFS << std::endl;
  std::cout << "Creating new tariffs\n";
  std::cout << "WARNING: This action will overwrite existing tariffs.\n";
  std::cout << "Proceed? (y/n): ";
  char proceed;
  std::cin >> proceed;
  // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (proceed == 'y') {
    std::vector<std::vector<std::string>> newTariffs;
    newTariffs.push_back({"Type", "Tier", "Price"});  // Header

    std::string types[] = {"Residential", "Commercial", "Industrial"};
    for (const auto& type : types) {
      std::string input;
      do {
        std::vector<std::string> row;
        row.push_back(type);
        std::cout << "Enter tier for " << type << " (or 'done' to finish this type): ";
        std::cin >> input;
        if (input != "done") {
          row.push_back(input);
          std::cout << "Enter price for this tier: ";
          std::cin >> input;
          row.push_back(input);

          newTariffs.push_back(row);
        }
      } while (input != "done");
    }

  fileIO.writeTariffsToCSV("../data/tariffs.csv", newTariffs);
  std::cout << "New tariffs have been saved.\n";
  std::cout << "Press return to get back.";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // std::cin.get();
  } else if (proceed == 'n') {
    std::cout << "Press return to get back.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } else {
    std::cout << "Invalid input, Press return to get back.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void App::handleEdiTarMenu() {
  clearScreen();
  std::cout << CityPowerManager::Art::EDIT_TARIFFS << std::endl;
  std::cout << "Editing existing tariffs\n";
  auto currentTariffs = fileIO.readTariffsFromCSV("../data/tariffs.csv");

  for (size_t i = 1; i < currentTariffs.size(); ++i) {
    std::cout << i << ". " << currentTariffs[i][0] << " - " << currentTariffs[i][1] << ": " << currentTariffs[i][2] << "\n";
  }

  std::cout << "Enter the number of the tariff you want to edit (0 to finish): ";
  int choice;
  std::cin >> choice;

  while (choice != 0) {
    if (choice > 0 && choice < static_cast<int>(currentTariffs.size())) {
      std::cout << "Editing: " << currentTariffs[choice][0] << " - " << currentTariffs[choice][1] << "\n";
      std::cout << "Enter new price: ";
      std::cin >> currentTariffs[choice][2];
    } else {
      std::cout << "Invalid choice.\n";
    }

    std::cout << "Enter the number of the tariff you want to edit (0 to finish): ";
    std::cin >> choice;
  }

  fileIO.writeTariffsToCSV("../data/tariffs.csv", currentTariffs);
  std::cout << "Updated tariffs have been saved.\n";
  std::cout << "Press return to get back.";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // std::cin.get();
}

void App::handleEdiSubMenu() {
  char choice;
  do {
    clearScreen();
    std::cout << CityPowerManager::Art::EDIT_SUBS << std::endl;
    std::cout << "Edit Subscriber:\n";
    std::cout << "1. Edit Residential Subscriber\n";
    std::cout << "2. Edit Commercial Subscriber\n";
    std::cout << "3. Edit Industrial Subscriber\n";
    std::cout << "4. Back To Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice >= '1' && choice <= '3') {
      editSubscriber(choice);
    } else if (choice != '4') {
      std::cout << "Invalid option. Please try again.\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
    }
  } while (choice != '4');
}

void App::handleDisTarMenu() {
  clearScreen();
  std::cout << CityPowerManager::Art::EDIT_TARIFFS << std::endl;
  displayTariffs();
  std::cout << "Press return to get back.";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // std::cin.get();
}

void App::handleBillingIss() {
  clearScreen();
  std::cout << CityPowerManager::Art::BILLING_ISSUANCE << std::endl;
  BillingSystem billingSystem;
  billingSystem.issueBills(residentialSubscribers, commercialSubscribers, industrialSubscribers, tariffs);
  std::cout << "Bills have been issued and added to subscribers' debts.\n";
  std::cout << "Press return to get back.";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // std::cin.get();
}

void App::addNewSubscriber(char type) {
  std::string name, lastName, nationalID, meterNumber, installationDate;

  std::cout << "Enter name: ";
  std::cin >> name;
  std::cout << "Enter last name: ";
  std::cin >> lastName;
  std::cout << "Enter national ID: ";
  std::cin >> nationalID;
  std::cout << "Enter meter number: ";
  std::cin >> meterNumber;
  std::cout << "Enter installation date: ";
  std::cin >> installationDate;

  switch (type) {
    case '1': {
      ResidentialSubscriber sub(name, lastName, nationalID, meterNumber, installationDate);
      residentialSubscribers.push_back(sub);
      break;
    }
    case '2': {
      double meterCapacity;
      std::string businessLicense;
      std::cout << "Enter meter capacity: ";
      std::cin >> meterCapacity;
      std::cout << "Enter business license: ";
      std::cin >> businessLicense;
      CommercialSubscriber sub(name, lastName, nationalID, meterNumber, installationDate, meterCapacity, businessLicense);
      commercialSubscribers.push_back(sub);
      break;
    }
    case '3': {
      std::string unitName, connectionType;
      double supplyVoltage, meterMultiplier, transformerRatio;
      std::cout << "Enter unit name: ";
      std::cin >> unitName;
      std::cout << "Enter supply voltage: ";
      std::cin >> supplyVoltage;
      std::cout << "Enter connection type: ";
      std::cin >> connectionType;
      std::cout << "Enter meter multiplier: ";
      std::cin >> meterMultiplier;
      std::cout << "Enter transformer ratio: ";
      std::cin >> transformerRatio;
      IndustrialSubscriber sub(name, lastName, nationalID, meterNumber, installationDate, unitName, supplyVoltage, connectionType, meterMultiplier, transformerRatio);
      industrialSubscribers.push_back(sub);
      break;
    }
  }

  std::cout << "Subscriber added successfully.\n";
  // Save changes to file
  fileIO.writeResidentialSubscribers("../data/residential_subscribers.csv", residentialSubscribers);
  fileIO.writeCommercialSubscribers("../data/commercial_subscribers.csv", commercialSubscribers);
  fileIO.writeIndustrialSubscribers("../data/industrial_subscribers.csv", industrialSubscribers);
}

void App::editSubscriber(char type) {
  std::string meterNumber;
  std::cout << "Enter meter number of the subscriber to edit: ";
  std::cin >> meterNumber;

  switch (type) {
    case '1': {
      auto it = std::find_if(residentialSubscribers.begin(), residentialSubscribers.end(),
        [&meterNumber](const ResidentialSubscriber& sub) { return sub.getMeterNumber() == meterNumber; });
      if (it != residentialSubscribers.end()) {
        std::cout << "Enter new name (or '.' to keep current): ";
        std::string name;
        std::cin >> name;
        if (name != ".") it->setName(name);

        std::cout << "Enter new last name (or '.' to keep current): ";
        std::string lastName;
        std::cin >> lastName;
        if (lastName != ".") it->setLastName(lastName);

        std::cout << "Enter new national ID (or '.' to keep current): ";
        std::string nationalID;
        std::cin >> nationalID;
        if (nationalID != ".") it->setNationalID(nationalID);

        std::cout << "Enter new installation date (or '.' to keep current): ";
        std::string installationDate;
        std::cin >> installationDate;
        if (installationDate != ".") it->setInstallationDate(installationDate);

        std::cout << "Subscriber updated successfully.\n";
        fileIO.writeResidentialSubscribers("../data/residential_subscribers.csv", residentialSubscribers);
      } else {
        std::cout << "Subscriber not found.\n";
      }
      break;
    }
    case '2': {
      auto it = std::find_if(commercialSubscribers.begin(), commercialSubscribers.end(),
        [&meterNumber](const CommercialSubscriber& sub) { return sub.getMeterNumber() == meterNumber; });
      if (it != commercialSubscribers.end()) {
        std::cout << "Enter new name (or '.' to keep current): ";
        std::string name;
        std::cin >> name;
        if (name != ".") it->setName(name);

        std::cout << "Enter new last name (or '.' to keep current): ";
        std::string lastName;
        std::cin >> lastName;
        if (lastName != ".") it->setLastName(lastName);

        std::cout << "Enter new national ID (or '.' to keep current): ";
        std::string nationalID;
        std::cin >> nationalID;
        if (nationalID != ".") it->setNationalID(nationalID);

        std::cout << "Enter new installation date (or '.' to keep current): ";
        std::string installationDate;
        std::cin >> installationDate;
        if (installationDate != ".") it->setInstallationDate(installationDate);

        std::cout << "Enter new meter capacity (or -1 to keep current): ";
        double meterCapacity;
        std::cin >> meterCapacity;
        if (meterCapacity != -1) it->setMeterCapacity(meterCapacity);

        std::cout << "Enter new business license (or '.' to keep current): ";
        std::string businessLicense;
        std::cin >> businessLicense;
        if (businessLicense != ".") it->setBusinessLicense(businessLicense);

        std::cout << "Subscriber updated successfully.\n";
        fileIO.writeCommercialSubscribers("../data/commercial_subscribers.csv", commercialSubscribers);
      } else {
        std::cout << "Subscriber not found.\n";
      }
      break;
    }
    case '3': {
      auto it = std::find_if(industrialSubscribers.begin(), industrialSubscribers.end(),
        [&meterNumber](const IndustrialSubscriber& sub) { return sub.getMeterNumber() == meterNumber; });
      if (it != industrialSubscribers.end()) {
        std::cout << "Enter new name (or '.' to keep current): ";
        std::string name;
        std::cin >> name;
        if (name != ".") it->setName(name);

        std::cout << "Enter new last name (or '.' to keep current): ";
        std::string lastName;
        std::cin >> lastName;
        if (lastName != ".") it->setLastName(lastName);

        std::cout << "Enter new national ID (or '.' to keep current): ";
        std::string nationalID;
        std::cin >> nationalID;
        if (nationalID != ".") it->setNationalID(nationalID);

        std::cout << "Enter new installation date (or '.' to keep current): ";
        std::string installationDate;
        std::cin >> installationDate;
        if (installationDate != ".") it->setInstallationDate(installationDate);

        std::cout << "Enter new unit name (or '.' to keep current): ";
        std::string unitName;
        std::cin >> unitName;
        if (unitName != ".") it->setUnitName(unitName);

        std::cout << "Enter new supply voltage (or -1 to keep current): ";
        double supplyVoltage;
        std::cin >> supplyVoltage;
        if (supplyVoltage != -1) it->setSupplyVoltage(supplyVoltage);

        std::cout << "Enter new connection type (or '.' to keep current): ";
        std::string connectionType;
        std::cin >> connectionType;
        if (connectionType != ".") it->setConnectionType(connectionType);

        std::cout << "Enter new meter multiplier (or -1 to keep current): ";
        double meterMultiplier;
        std::cin >> meterMultiplier;
        if (meterMultiplier != -1) it->setMeterMultiplier(meterMultiplier);

        std::cout << "Enter new transformer ratio (or -1 to keep current): ";
        double transformerRatio;
        std::cin >> transformerRatio;
        if (transformerRatio != -1) it->setTransformerRatio(transformerRatio);

        std::cout << "Subscriber updated successfully.\n";
        fileIO.writeIndustrialSubscribers("../data/industrial_subscribers.csv", industrialSubscribers);
      } else {
          std::cout << "Subscriber not found.\n";
      }
      break;
    }
  }
}

void App::displayTariffs() {
  clearScreen();
  std::cout << CityPowerManager::Art::DISPLAY_TARIFFS << std::endl;
  std::cout << "Displaying Tariffs:\n";
  for (const auto& tariff : tariffs) {
      std::cout << tariff->getTariffInfo() << "\n";
      std::cout << "-------------------\n";
  }

  // std::cout << "Press return to get back.";
  // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // std::cin.get();
}

void App::displaySubscribers(char option) {
  switch (option){
    case '1':
      clearScreen();
      std::cout << "Residential Subscribers:\n";
      for (const auto& sub : residentialSubscribers) {
        std::cout << sub << "\n";
      }
      std::cout << "Press return to get back.";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      break;

    case '2':
      clearScreen();
      std::cout << "Commercial Subscribers:\n";
        for (const auto& sub : commercialSubscribers) {
          std::cout << sub << "\n";
        }
      std::cout << "Press return to get back.";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      break;

    case '3':
      clearScreen();
      std::cout << "Industrial Subscribers:\n";
        for (const auto& sub : industrialSubscribers) {
          std::cout << sub << "\n";
        }
      std::cout << "Press return to get back.";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      break;

    case '4':
      // do nothing
      break;

    default:
      break;
  }
}

void App::clearScreen() const {
#ifdef WIN_32
  system("cls");
#else
  system("clear");
#endif
}

void App::run() {
  char choice;
  do {
    clearScreen();  // Comment here if you want to debug databases
    showMainMenu();
    std::cin >> choice;
    handleMenuOption(choice);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (choice != '8');
}
