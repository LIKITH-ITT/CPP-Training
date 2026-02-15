#include "BankSystem.h"
#include "Constants.h"
#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <limits>

BankSystem::BankSystem()
{
    _admin = new Admin();
    
    _accountHolders = new AccountHolder**;
    *_accountHolders = nullptr;
    
    _totalAccounts = new int;
    *_totalAccounts = 0;
    
    _arrayCapacity = new int;
    *_arrayCapacity = 0;
    
    _nextAccountNumber = new long;
    *_nextAccountNumber = Constants::INITIAL_ACCOUNT_NUMBER;
    
    _nextTransactionNumber = new long;
    *_nextTransactionNumber = Constants::INITIAL_TRANSACTION_ID;
}

BankSystem::~BankSystem()
{
    if (*_accountHolders != nullptr)
    {
        for (int i = 0; i < *_totalAccounts; i++)
        {
            delete (*_accountHolders)[i];
        }
        delete[] (*_accountHolders);
    }
    
    delete _accountHolders;
    delete _totalAccounts;
    delete _arrayCapacity;
    delete _nextAccountNumber;
    delete _nextTransactionNumber;
    delete _admin;
}

void BankSystem::run()
{
    std::cout << Logger::WELCOME_MESSAGE << "\n";
    
    bool running = true;
    while (running)
    {
        displayMainMenu();
        int choice = getIntInput();
        
        switch (static_cast<MainMenu>(choice))
        {
            case MainMenu::LOGIN:
                handleLogin();
                break;
            case MainMenu::EXIT:
                running = false;
                std::cout << Logger::GOODBYE_MESSAGE << "\n";
                break;
            default:
                std::cout << Logger::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::displayMainMenu()
{
    std::cout << Logger::MAIN_MENU_HEADER << "\n";
    std::cout << static_cast<int>(MainMenu::LOGIN) << ". " << Logger::MENU_LOGIN << "\n";
    std::cout << static_cast<int>(MainMenu::EXIT) << ". " << Logger::MENU_EXIT << "\n";
    std::cout << Logger::SEPARATOR_DASHES << "\n";
    std::cout << Logger::PROMPT_ENTER_CHOICE;
}

void BankSystem::handleLogin()
{
    std::string username, password;
    
    std::cout << Logger::LOGIN_HEADER << "\n";
    std::cout << Logger::PROMPT_USERNAME;
    std::cin >> username;
    std::cout << Logger::PROMPT_PASSWORD;
    std::cin >> password;
    
    if (username == Constants::ADMIN_USERNAME && _admin->authenticate(password))
    {
        std::cout << Logger::INFO_WELCOME_ADMIN << _admin->getAdminName() << "!\n";
        handleAdminMenu();
    }
    else
    {
        AccountHolder* holder = findAccountHolderByUsernameOrEmail(username);
        if (holder != nullptr)
        {
            if (!holder->getAccount()->getIsActive())
            {
                std::cout << Logger::ERROR_ACCOUNT_DEACTIVATED << "\n";
                return;
            }
            
            if (holder->authenticate(password))
            {
                std::cout << Logger::INFO_WELCOME_USER << holder->getName() << "!\n";
                handleCustomerMenu(holder);
            }
            else
            {
                std::cout << Logger::ERROR_INVALID_CREDENTIALS << "\n";
            }
        }
        else
        {
            std::cout << Logger::ERROR_INVALID_CREDENTIALS << "\n";
        }
    }
}

void BankSystem::handleAdminMenu()
{
    bool running = true;
    while (running)
    {
        _admin->displayMenu();
        int choice = getIntInput();
        
        switch (static_cast<AdminMenu>(choice))
        {
            case AdminMenu::CREATE_ACCOUNT:
                _admin->createAccount(_accountHolders, _totalAccounts, _arrayCapacity, 
                                   _nextAccountNumber, _nextTransactionNumber);
                break;
            case AdminMenu::DELETE_ACCOUNT:
                _admin->deleteAccount(_accountHolders, _totalAccounts);
                break;
            case AdminMenu::SEARCH_ACCOUNT:
                _admin->searchAccount(_accountHolders, *_totalAccounts);
                break;
            case AdminMenu::VIEW_ALL_ACCOUNTS:
                _admin->viewAllAccounts(_accountHolders, *_totalAccounts);
                break;
            case AdminMenu::EXIT:
                running = false;
                std::cout << Logger::SUCCESS_LOGOUT << "\n";
                break;
            default:
                std::cout << Logger::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::handleCustomerMenu(AccountHolder* holder)
{
    bool running = true;
    while (running)
    {
        holder->displayMenu();
        int choice = getIntInput();
        
        switch (static_cast<CustomerMenu>(choice))
        {
            case CustomerMenu::DEPOSIT:
                handleDeposit(holder);
                break;
            case CustomerMenu::WITHDRAW:
                handleWithdraw(holder);
                break;
            case CustomerMenu::VIEW_BALANCE:
                holder->viewBalance();
                break;
            case CustomerMenu::MINI_STATEMENT:
                holder->printMiniStatement();
                break;
            case CustomerMenu::FULL_STATEMENT:
                holder->printBankStatement();
                break;
            case CustomerMenu::CHANGE_PASSWORD:
                handleChangePassword(holder);
                break;
            case CustomerMenu::EXIT:
                running = false;
                std::cout << Logger::SUCCESS_LOGOUT << "\n";
                break;
            default:
                std::cout << Logger::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::handleDeposit(AccountHolder* holder)
{
    double amount;
    std::cout << Logger::PROMPT_AMOUNT_DEPOSIT;
    amount = getDoubleInput();
    
    if (!Validator::isValidAmount(amount))
    {
        std::cout << Logger::ERROR_INVALID_AMOUNT << "\n";
        return;
    }
    
    if (holder->performDeposit(amount))
    {
        Transaction* txn = new Transaction("Deposit", amount, *_nextTransactionNumber);
        (*_nextTransactionNumber)++;
        holder->getAccount()->addTransaction(txn);
        std::cout << Logger::SUCCESS_DEPOSIT << std::fixed 
                  << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << Logger::ERROR_DEPOSIT_FAILED << "\n";
    }
}

void BankSystem::handleWithdraw(AccountHolder* holder)
{
    double amount;
    std::cout << Logger::INFO_CURRENT_BALANCE << std::fixed << std::setprecision(2) 
              << holder->getAccount()->getBalance() << "\n";
    std::cout << Logger::PROMPT_AMOUNT_WITHDRAW;
    amount = getDoubleInput();
    
    if (!Validator::isValidAmount(amount))
    {
        std::cout << Logger::ERROR_INVALID_AMOUNT << "\n";
        return;
    }
    
    if (holder->performWithdraw(amount))
    {
        Transaction* txn = new Transaction("Withdrawal", amount, *_nextTransactionNumber);
        (*_nextTransactionNumber)++;
        holder->getAccount()->addTransaction(txn);
        std::cout << Logger::SUCCESS_WITHDRAWAL << std::fixed 
                  << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << Logger::ERROR_INSUFFICIENT_BALANCE << "\n";
    }
}

void BankSystem::handleChangePassword(AccountHolder* holder)
{
    std::string oldPassword, newPassword, confirmPassword;
    
    std::cout << Logger::PROMPT_CURRENT_PASSWORD;
    std::cin >> oldPassword;
    
    if (!holder->authenticate(oldPassword))
    {
        std::cout << Logger::ERROR_INCORRECT_PASSWORD << "\n";
        return;
    }
    
    do
    {
        std::cout << Logger::PROMPT_NEW_PASSWORD;
        std::cin >> newPassword;
        if (!Validator::isValidPassword(newPassword))
        {
            std::cout << Logger::ERROR_INVALID_PASSWORD << "\n";
        }
    }
    while (!Validator::isValidPassword(newPassword));
    
    std::cout << Logger::PROMPT_CONFIRM_NEW_PASSWORD;
    std::cin >> confirmPassword;
    
    if (newPassword != confirmPassword)
    {
        std::cout << "Passwords do not match! Password change failed.\n";
        return;
    }
    
    holder->setPassword(newPassword);
    std::cout << Logger::SUCCESS_PASSWORD_CHANGED << "\n";
}

void BankSystem::addAccountHolder(AccountHolder* holder)
{
    if (*_totalAccounts >= *_arrayCapacity)
    {
        int newCapacity = (*_arrayCapacity == 0) ? 2 : (*_arrayCapacity * 2);
        
        AccountHolder** newArray = new AccountHolder*[newCapacity];
        
        for (int i = 0; i < *_totalAccounts; i++)
        {
            newArray[i] = (*_accountHolders)[i];
        }
        
        if (*_accountHolders != nullptr)
        {
            delete[] (*_accountHolders);
        }
        
        *_accountHolders = newArray;
        *_arrayCapacity = newCapacity;
    }
    
    (*_accountHolders)[*_totalAccounts] = holder;
    (*_totalAccounts)++;
}

AccountHolder* BankSystem::findAccountHolderByUsernameOrEmail(std::string& usernameOrEmail)
{
    for (int i = 0; i < *_totalAccounts; i++)
    {
        AccountHolder* holder = (*_accountHolders)[i];
        std::string accNumStr = std::to_string(holder->getAccount()->getAccountNumber());
        if (accNumStr == usernameOrEmail)
        {
            return holder;
        }
        if (holder->getEmail() == usernameOrEmail)
        {
            return holder;
        }
    }
    return nullptr;
}

int BankSystem::getIntInput()
{
    int value;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << Logger::INVALID_INPUT << "\n";
        std::cout << "Please enter a number: ";
    }
    return value;
}

double BankSystem::getDoubleInput()
{
    double value;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << Logger::INVALID_INPUT << "\n";
        std::cout << "Please enter a number: ";
    }
    return value;
}

long BankSystem::getLongInput()
{
    long value;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << Logger::INVALID_INPUT << "\n";
        std::cout << "Please enter a number: ";
    }
    return value;
}
