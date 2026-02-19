#include "Admin.h"
#include "AccountHolder.h"
#include "Validator.h"
#include "UIStrings.h"
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
    std::cout << UIStrings::ADMIN_MENU_HEADER << "\n";
    std::cout << static_cast<int>(AdminMenu::CREATE_ACCOUNT) << ". " << UIStrings::MENU_CREATE_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::DELETE_ACCOUNT) << ". " << UIStrings::MENU_DELETE_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::SEARCH_ACCOUNT) << ". " << UIStrings::MENU_SEARCH_ACCOUNT << "\n";
    std::cout << static_cast<int>(AdminMenu::VIEW_ALL_ACCOUNTS) << ". " << UIStrings::MENU_VIEW_ALL_ACCOUNTS << "\n";
    std::cout << static_cast<int>(AdminMenu::EXIT) << ". " << UIStrings::MENU_LOGOUT << "\n";
    std::cout << UIStrings::SEPARATOR_DASHES << "\n";
    std::cout << UIStrings::PROMPT_ENTER_CHOICE;
}

void Admin::createAccount(AccountHolder*** accountHolders, int* totalAccounts, int* arrayCapacity, long* nextAccountNumber, long* nextTransactionNumber) 
{

    std::string name, email, password, confirmPassword;
    double initialDeposit;
    
    std::cout << UIStrings::CREATE_ACCOUNT_HEADER << "\n";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do 
    {
        std::cout << UIStrings::PROMPT_FULL_NAME;
        std::getline(std::cin, name);
        if (!Validator::isValidName(name)) {
            std::cout << UIStrings::ERROR_INVALID_NAME << "\n";
        }
    } while (!Validator::isValidName(name));
    
    do 
    {
        std::cout << UIStrings::PROMPT_EMAIL;
        std::cin >> email;
        if (!Validator::isValidEmail(email)) {
            std::cout << UIStrings::ERROR_INVALID_EMAIL << "\n";
        }
    } while (!Validator::isValidEmail(email));
    
    do 
    {
        std::cout << UIStrings::PROMPT_NEW_PASSWORD;
        std::cin >> password;
        if (!Validator::isValidPassword(password)) {
            std::cout << UIStrings::ERROR_INVALID_PASSWORD << "\n";
        }
    } while (!Validator::isValidPassword(password));
    
    int attempts = 0;
    bool matched = false;

    while (attempts < 3)
    {
        std::cout << UIStrings::PROMPT_CONFIRM_PASSWORD;
        std::cin >> confirmPassword;

        if (password == confirmPassword)
        {
            matched = true;
            break;
        }

        attempts++;
        std::cout << UIStrings::ERROR_PASSWORD_MISMATCH << "\n";

        if (attempts < 3)
        {
            std::cout << "Attempts remaining: " << (3 - attempts) << "\n";
        }
    }

    if (!matched)
    {
        std::cout << UIStrings::ERROR_CONFIRM_PASSWORD;
        return;
    }

    
    do {
        std::cout << UIStrings::PROMPT_INITIAL_DEPOSIT << Constants::MIN_DEPOSIT_AMOUNT << "): Rs. ";
        initialDeposit = getDepositAmount();
        if (initialDeposit < Constants::MIN_DEPOSIT_AMOUNT) {
            std::cout << UIStrings::ERROR_MIN_DEPOSIT << Constants::MIN_DEPOSIT_AMOUNT << "\n";
        }
    } while (initialDeposit < Constants::MIN_DEPOSIT_AMOUNT);
    
    long accNum = *nextAccountNumber;
    (*nextAccountNumber)++;
    
    AccountHolder* newHolder = new AccountHolder(accNum, name, email, password, initialDeposit);
    
    Transaction* openingTxn = new Transaction("Account Opening", initialDeposit, *nextTransactionNumber);
    (*nextTransactionNumber)++;
    newHolder->getAccount()->addTransaction(openingTxn);
    
    addAccountHolder(newHolder, accountHolders, totalAccounts, arrayCapacity);
    
    std::cout << UIStrings::SUCCESS_ACCOUNT_CREATED << "\n";
    std::cout << UIStrings::LABEL_ACCOUNT_NUMBER << accNum << "\n";
    std::cout << UIStrings::LABEL_ACCOUNT_HOLDER << name << "\n";
    std::cout << UIStrings::LABEL_EMAIL << email << "\n";
    std::cout << UIStrings::LABEL_INITIAL_BALANCE << std::fixed << std::setprecision(2) << initialDeposit << "\n";
    std::cout << UIStrings::LABEL_STATUS << "Active\n";
    std::cout << UIStrings::SEPARATOR_EQUALS << "\n";
}

void Admin::deleteAccount(AccountHolder*** accountHolders, int* totalAccounts) 
{
    std::cout << UIStrings::DELETE_ACCOUNT_HEADER << "\n";
    long accNum = getAccountNumberInput();
    
    AccountHolder* holder = findAccountByNumber(accountHolders, *totalAccounts, accNum);
    if (holder != nullptr) 
    {
        std::cout << UIStrings::INFO_ACCOUNT_DETAILS_BEFORE_DELETE;
        std::cout << UIStrings::LABEL_ACCOUNT_NUMBER << holder->getAccount()->getAccountNumber() << "\n";
        std::cout << UIStrings::LABEL_ACCOUNT_HOLDER << holder->getName() << "\n";
        std::cout << UIStrings::LABEL_BALANCE << std::fixed << std::setprecision(2) 
                  << holder->getAccount()->getBalance() << "\n";
        std::cout << UIStrings::LABEL_STATUS << holder->getAccount()->getStatus() << "\n\n";
        
        std::cout << UIStrings::PROMPT_CONFIRM_DELETE;
        std::string confirm;
        std::cin >> confirm;
        
        std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
        
        if (confirm == "yes" || confirm == "y") 
        {
            if (removeAccountHolder(accountHolders, totalAccounts, accNum)) 
            {
                std::cout << UIStrings::SUCCESS_ACCOUNT_DELETED << "\n";
                std::cout << UIStrings::INFO_DATA_REMOVED << "\n";
            } else 
            {
                std::cout << UIStrings::ERROR_DELETE_FAILED << "\n";
            }
        } else 
        {
            std::cout << UIStrings::INFO_DELETE_CANCELLED << "\n";
        }
    } 
    else 
    {
        std::cout << UIStrings::ERROR_ACCOUNT_NOT_FOUND << "\n";
    }
}

void Admin::searchAccount(AccountHolder*** accountHolders, int totalAccounts) 
{
    std::cout << UIStrings::SEARCH_ACCOUNT_HEADER << "\n";
    std::cout << "Search by:\n";
    std::cout << UIStrings::SEARCH_BY_NUMBER << "\n";
    std::cout << UIStrings::SEARCH_BY_NAME << "\n";
    std::cout << UIStrings::PROMPT_SEARCH_CHOICE;
    
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
        std::cout << UIStrings::PROMPT_ACCOUNT_HOLDER_NAME;
        std::getline(std::cin, name);
        holder = findAccountByName(accountHolders, totalAccounts, name);
    }
    
    if (holder != nullptr) 
    {
        std::cout << UIStrings::ACCOUNT_FOUND_HEADER << "\n";
        std::cout << UIStrings::LABEL_ACCOUNT_NUMBER << holder->getAccount()->getAccountNumber() << "\n";
        std::cout << UIStrings::LABEL_ACCOUNT_HOLDER << holder->getName() << "\n";
        std::cout << UIStrings::LABEL_EMAIL << holder->getEmail() << "\n";
        std::cout << UIStrings::LABEL_BALANCE << std::fixed << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
        std::cout << UIStrings::LABEL_STATUS << holder->getAccount()->getStatus() << "\n";
        std::cout << UIStrings::LABEL_CREATED_AT << holder->getAccount()->getCreationDateTime() << "\n";
        std::cout << UIStrings::LABEL_TOTAL_TRANSACTIONS << holder->getAccount()->getTransactionCount() << "\n";
        std::cout << "===================================\n";
    } 
    else 
    {
        std::cout << UIStrings::ERROR_ACCOUNT_NOT_FOUND << "\n";
    }
}

void Admin::viewAllAccounts(AccountHolder*** accountHolders, int totalAccounts) 
{
    std::cout << UIStrings::ALL_ACCOUNTS_HEADER << "\n";
    std::cout << UIStrings::INFO_TOTAL_ACCOUNTS << totalAccounts << "\n\n";
    
    if (totalAccounts == 0) 
    {
        std::cout << UIStrings::INFO_NO_ACCOUNTS << "\n";
        return;
    }
    
    std::cout << std::left << std::setw(12) << "Account No."
              << std::setw(22) << UIStrings::LABEL_NAME
              << std::setw(28) << "Email"
              << std::setw(15) << "Balance"
              << std::setw(13) << "Status"
              << std::setw(20) << "Created At" << std::endl;
    std::cout << std::string(108, '-') << std::endl;
    
    for (int account = 0; account < totalAccounts; account++) 
    {
        AccountHolder* holder = (*accountHolders)[account];
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
    std::cout << UIStrings::PROMPT_ACCOUNT_NUMBER;
    while (!(std::cin >> accNum)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a valid account number: ";
    }
    return accNum;
}

double Admin::getDepositAmount() 
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
        
        for (int account = 0; account < *totalAccounts; account++) 
        {
            newArray[account] = (*accountHolders)[account];
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
    for (int account = 0; account < totalAccounts; account++) {
        if ((*accountHolders)[account]->getAccount()->getAccountNumber() == accNum) 
        {
            return (*accountHolders)[account];
        }
    }
    return nullptr;
}

AccountHolder* Admin::findAccountByName(AccountHolder*** accountHolders, int totalAccounts,  std::string& name) 
{
    std::string searchName = name;
    std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
    
    for (int account = 0; account < totalAccounts; account++) 
    {
        std::string holderName = (*accountHolders)[account]->getName();
        std::transform(holderName.begin(), holderName.end(), holderName.begin(), ::tolower);
        
        if (holderName == searchName) 
        {
            return (*accountHolders)[account];
        }
    }
        
    return nullptr;
}

bool Admin::removeAccountHolder(AccountHolder*** accountHolders, int* totalAccounts, long accNum) 
{
    int index = -1;
    for (int account = 0; account < *totalAccounts; account++) 
    {
        if ((*accountHolders)[account]->getAccount()->getAccountNumber() == accNum) 
        {
            index = account;
            break;
        }
    }
    
    if (index == -1) 
    {
        return false;
    }
    
    delete (*accountHolders)[index];
    
    for (int account = index; account < *totalAccounts - 1; account++) 
    {
        (*accountHolders)[account] = (*accountHolders)[account + 1];
    }
    
    (*totalAccounts)--;
    return true;
}
