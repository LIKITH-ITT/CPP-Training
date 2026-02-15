#include "Admin.h"
#include "AccountHolder.h"
#include "Validator.h"
#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

Admin::Admin() : User(Constants::ADMIN_ID, Constants::ADMIN_PASSWORD) 
{
    _adminName = "Administrator";
}

Admin::~Admin() {}

std::string Admin::getAdminName()  
{
    return _adminName;
}

void Admin::displayMenu() 
{
    std::cout << Logger::ADMIN_MENU_HEADER << "\n";
    std::cout << static_cast<int>(AdminMenu::CREATE_ACCOUNT) << ". " << Logger::MENU_CREATE_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::DELETE_ACCOUNT) << ". " << Logger::MENU_DELETE_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::SEARCH_ACCOUNT) << ". " << Logger::MENU_SEARCH_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::VIEW_ALL_ACCOUNTS) << ". " << Logger::MENU_VIEW_ALL_ACCOUNTS << "\n";
    std::cout << static_cast<int>(AdminMenu::EXIT) << ". " << Logger::MENU_LOGOUT << "\n";
    std::cout << Logger::SEPARATOR_DASHES << "\n";
    std::cout << Logger::PROMPT_ENTER_CHOICE;
}

void Admin::createAccount(AccountHolder*** accountHolders, int* totalAccounts, int* arrayCapacity, long* nextAccountNumber, long* nextTransactionNumber) 
{

    std::string name, email, password, confirmPassword;
    double initialDeposit;
    
    std::cout << Logger::CREATE_ACCOUNT_HEADER << "\n";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do 
    {
        std::cout << Logger::PROMPT_FULL_NAME;
        std::getline(std::cin, name);
        if (!Validator::isValidName(name)) {
            std::cout << Logger::ERROR_INVALID_NAME << "\n";
        }
    } while (!Validator::isValidName(name));
    
    do 
    {
        std::cout << Logger::PROMPT_EMAIL;
        std::cin >> email;
        if (!Validator::isValidEmail(email)) {
            std::cout << Logger::ERROR_INVALID_EMAIL << "\n";
        }
    } while (!Validator::isValidEmail(email));
    
    do 
    {
        std::cout << Logger::PROMPT_NEW_PASSWORD;
        std::cin >> password;
        if (!Validator::isValidPassword(password)) {
            std::cout << Logger::ERROR_INVALID_PASSWORD << "\n";
        }
    } while (!Validator::isValidPassword(password));
    
    std::cout << Logger::PROMPT_CONFIRM_PASSWORD;
    std::cin >> confirmPassword;
    
    if (password != confirmPassword) 
    {
        std::cout << Logger::ERROR_PASSWORD_MISMATCH << "\n";
        return;
    }
    
    do {
        std::cout << Logger::PROMPT_INITIAL_DEPOSIT << Constants::MIN_DEPOSIT_AMOUNT << "): Rs. ";
        initialDeposit = getDoubleInput();
        if (initialDeposit < Constants::MIN_DEPOSIT_AMOUNT) {
            std::cout << Logger::ERROR_MIN_DEPOSIT << Constants::MIN_DEPOSIT_AMOUNT << "\n";
        }
    } while (initialDeposit < Constants::MIN_DEPOSIT_AMOUNT);
    
    long accNum = *nextAccountNumber;
    (*nextAccountNumber)++;
    
    AccountHolder* newHolder = new AccountHolder(accNum, name, email, password, initialDeposit);
    
    Transaction* openingTxn = new Transaction("Account Opening", initialDeposit, *nextTransactionNumber);
    (*nextTransactionNumber)++;
    newHolder->getAccount()->addTransaction(openingTxn);
    
    addAccountHolder(newHolder, accountHolders, totalAccounts, arrayCapacity);
    
    std::cout << Logger::SUCCESS_ACCOUNT_CREATED << "\n";
    std::cout << Logger::LABEL_ACCOUNT_NUMBER << accNum << "\n";
    std::cout << Logger::LABEL_ACCOUNT_HOLDER << name << "\n";
    std::cout << Logger::LABEL_EMAIL << email << "\n";
    std::cout << Logger::LABEL_INITIAL_BALANCE << std::fixed << std::setprecision(2) << initialDeposit << "\n";
    std::cout << Logger::LABEL_STATUS << "Active\n";
    std::cout << Logger::SEPARATOR_EQUALS << "\n";
}

void Admin::deleteAccount(AccountHolder*** accountHolders, int* totalAccounts) 
{
    std::cout << Logger::DELETE_ACCOUNT_HEADER << "\n";
    long accNum = getAccountNumberInput();
    
    AccountHolder* holder = findAccountByNumber(accountHolders, *totalAccounts, accNum);
    if (holder != nullptr) 
    {
        std::cout << Logger::INFO_ACCOUNT_DETAILS_BEFORE_DELETE;
        std::cout << Logger::LABEL_ACCOUNT_NUMBER << holder->getAccount()->getAccountNumber() << "\n";
        std::cout << Logger::LABEL_ACCOUNT_HOLDER << holder->getName() << "\n";
        std::cout << Logger::LABEL_BALANCE << std::fixed << std::setprecision(2) 
                  << holder->getAccount()->getBalance() << "\n";
        std::cout << Logger::LABEL_STATUS << holder->getAccount()->getStatus() << "\n\n";
        
        std::cout << Logger::PROMPT_CONFIRM_DELETE;
        std::string confirm;
        std::cin >> confirm;
        
        std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
        
        if (confirm == "yes" || confirm == "y") 
        {
            if (removeAccountHolder(accountHolders, totalAccounts, accNum)) 
            {
                std::cout << Logger::SUCCESS_ACCOUNT_DELETED << "\n";
                std::cout << Logger::INFO_DATA_REMOVED << "\n";
            } else 
            {
                std::cout << Logger::ERROR_DELETE_FAILED << "\n";
            }
        } else 
        {
            std::cout << Logger::INFO_DELETE_CANCELLED << "\n";
        }
    } 
    else 
    {
        std::cout << Logger::ERROR_ACCOUNT_NOT_FOUND << "\n";
    }
}

void Admin::searchAccount(AccountHolder*** accountHolders, int totalAccounts) 
{
    std::cout << Logger::SEARCH_ACCOUNT_HEADER << "\n";
    std::cout << "Search by:\n";
    std::cout << Logger::SEARCH_BY_NUMBER << "\n";
    std::cout << Logger::SEARCH_BY_NAME << "\n";
    std::cout << Logger::PROMPT_SEARCH_CHOICE;
    
    int choice;
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice! Enter 1 or 2: ";
    }
    
    AccountHolder* holder = nullptr;
    
    if (choice == 1) 
    {
        long accNum = getAccountNumberInput();
        holder = findAccountByNumber(accountHolders, totalAccounts, accNum);
    } 
    else 
    {
        std::cin.ignore();
        std::string name;
        std::cout << Logger::PROMPT_ACCOUNT_HOLDER_NAME;
        std::getline(std::cin, name);
        holder = findAccountByName(accountHolders, totalAccounts, name);
    }
    
    if (holder != nullptr) 
    {
        std::cout << Logger::ACCOUNT_FOUND_HEADER << "\n";
        std::cout << Logger::LABEL_ACCOUNT_NUMBER << holder->getAccount()->getAccountNumber() << "\n";
        std::cout << Logger::LABEL_ACCOUNT_HOLDER << holder->getName() << "\n";
        std::cout << Logger::LABEL_EMAIL << holder->getEmail() << "\n";
        std::cout << Logger::LABEL_BALANCE << std::fixed << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
        std::cout << Logger::LABEL_STATUS << holder->getAccount()->getStatus() << "\n";
        std::cout << Logger::LABEL_CREATED_AT << holder->getAccount()->getCreationDateTime() << "\n";
        std::cout << Logger::LABEL_TOTAL_TRANSACTIONS << holder->getAccount()->getTransactionCount() << "\n";
        std::cout << "===================================\n";
    } 
    else 
    {
        std::cout << Logger::ERROR_ACCOUNT_NOT_FOUND << "\n";
    }
}

void Admin::viewAllAccounts(AccountHolder*** accountHolders, int totalAccounts) 
{
    std::cout << Logger::ALL_ACCOUNTS_HEADER << "\n";
    std::cout << Logger::INFO_TOTAL_ACCOUNTS << totalAccounts << "\n\n";
    
    if (totalAccounts == 0) 
    {
        std::cout << Logger::INFO_NO_ACCOUNTS << "\n";
        return;
    }
    
    std::cout << std::left << std::setw(12) << "Account No."
              << std::setw(22) << Logger::LABEL_NAME
              << std::setw(28) << "Email"
              << std::setw(15) << "Balance"
              << std::setw(13) << "Status"
              << std::setw(20) << "Created At" << std::endl;
    std::cout << std::string(108, '-') << std::endl;
    
    for (int i = 0; i < totalAccounts; i++) 
    {
        AccountHolder* holder = (*accountHolders)[i];
        std::cout << std::left << std::setw(12) << holder->getAccount()->getAccountNumber()
                  << std::setw(22) << holder->getName()
                  << std::setw(28) << holder->getEmail()
                  << std::right << std::setw(13) << std::fixed << std::setprecision(2)
                  << holder->getAccount()->getBalance()
                  << std::left << std::setw(13) << "  " + holder->getAccount()->getStatus()
                  << std::setw(20) << holder->getAccount()->getCreationDateTime() << std::endl;
    }
    std::cout << std::string(108, '=') << "\n";
}

long Admin::getAccountNumberInput() 
{
    long accNum;
    std::cout << Logger::PROMPT_ACCOUNT_NUMBER;
    while (!(std::cin >> accNum)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a valid account number: ";
    }
    return accNum;
}

double Admin::getDoubleInput() 
{
    double value;
    while (!(std::cin >> value)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a valid number: ";
    }
    return value;
}

std::string Admin::getStringInput() 
{
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void Admin::addAccountHolder(AccountHolder* holder, AccountHolder*** accountHolders, int* totalAccounts, int* arrayCapacity) 
{
    if (*totalAccounts >= *arrayCapacity)
    {
        int newCapacity = (*arrayCapacity == 0) ? 2 : (*arrayCapacity * 2);
        
        AccountHolder** newArray = new AccountHolder*[newCapacity];
        
        for (int i = 0; i < *totalAccounts; i++) 
        {
            newArray[i] = (*accountHolders)[i];
        }
        
        if (*accountHolders != nullptr) 
        {
            delete[] (*accountHolders);
        }
        
        *accountHolders = newArray;
        *arrayCapacity = newCapacity;
    }
    
    (*accountHolders)[*totalAccounts] = holder;
    (*totalAccounts)++;
}

AccountHolder* Admin::findAccountByNumber(AccountHolder*** accountHolders, int totalAccounts, long accNum) 
{
    for (int i = 0; i < totalAccounts; i++) {
        if ((*accountHolders)[i]->getAccount()->getAccountNumber() == accNum) 
        {
            return (*accountHolders)[i];
        }
    }
    return nullptr;
}

AccountHolder* Admin::findAccountByName(AccountHolder*** accountHolders, int totalAccounts,  std::string& name) 
{
    std::string searchName = name;
    std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
    
    for (int i = 0; i < totalAccounts; i++) 
    {
        std::string holderName = (*accountHolders)[i]->getName();
        std::transform(holderName.begin(), holderName.end(), holderName.begin(), ::tolower);
        
        if (holderName == searchName) 
        {
            return (*accountHolders)[i];
        }
    }
    
    for (int i = 0; i < totalAccounts; i++) 
    {
        std::string holderName = (*accountHolders)[i]->getName();
        std::transform(holderName.begin(), holderName.end(), holderName.begin(), ::tolower);
        
        if (holderName.find(searchName) != std::string::npos) 
        {
            return (*accountHolders)[i];
        }
    }
    
    return nullptr;
}

bool Admin::removeAccountHolder(AccountHolder*** accountHolders, int* totalAccounts, long accNum) 
{
    int index = -1;
    for (int i = 0; i < *totalAccounts; i++) 
    {
        if ((*accountHolders)[i]->getAccount()->getAccountNumber() == accNum) 
        {
            index = i;
            break;
        }
    }
    
    if (index == -1) 
    {
        return false;
    }
    
    delete (*accountHolders)[index];
    
    for (int i = index; i < *totalAccounts - 1; i++) 
    {
        (*accountHolders)[i] = (*accountHolders)[i + 1];
    }
    
    (*totalAccounts)--;
    return true;
}
