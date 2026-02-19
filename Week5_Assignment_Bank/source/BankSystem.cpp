#include "BankSystem.h"
#include "Constants.h"
#include "UIStrings.h"
#include <iostream>
#include <iomanip>
#include<InputHandler.h>
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
        for (int account = 0; account < *_totalAccounts; account++)
        {
            delete (*_accountHolders)[account];
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
    std::cout << UIStrings::WELCOME_MESSAGE << "\n";
    
    bool running = true;
    while (running)
    {
        displayMainMenu();
        int choice = InputHandler::getIntInput();
        
        switch (static_cast<MainMenu>(choice))
        {
            case MainMenu::LOGIN:
                handleLogin();
                break;
            case MainMenu::EXIT:
                running = false;
                std::cout << UIStrings::GOODBYE_MESSAGE << "\n";
                break;
            default:
                std::cout << UIStrings::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::displayMainMenu()
{
    std::cout << UIStrings::MAIN_MENU_HEADER << "\n";
    std::cout << static_cast<int>(MainMenu::LOGIN) << ". " << UIStrings::MENU_LOGIN << "\n";
    std::cout << static_cast<int>(MainMenu::EXIT) << ". " << UIStrings::MENU_EXIT << "\n";
    std::cout << UIStrings::SEPARATOR_DASHES << "\n";
    std::cout << UIStrings::PROMPT_ENTER_CHOICE;
}

void BankSystem::handleLogin()
{
    std::string username, password;
    
    std::cout << UIStrings::LOGIN_HEADER << "\n";
    std::cout << UIStrings::PROMPT_USERNAME;
    std::cin >> username;
    std::cout << UIStrings::PROMPT_PASSWORD;
    std::cin >> password;
    
    if (username == Constants::ADMIN_USERNAME && _admin->authenticate(password))
    {
        std::cout << UIStrings::INFO_WELCOME_ADMIN << _admin->getAdminName() << "!\n";
        handleAdminMenu();
    }
    else
    {
        AccountHolder* holder = findAccountHolderByUsernameOrEmail(username);
        if (holder != nullptr)
        {
            if (!holder->getAccount()->getIsActive())
            {
                std::cout << UIStrings::ERROR_ACCOUNT_DEACTIVATED << "\n";
                return;
            }
            
            if (holder->authenticate(password))
            {
                std::cout << UIStrings::INFO_WELCOME_USER << holder->getName() << "!\n";
                handleCustomerMenu(holder);
            }
            else
            {
                std::cout << UIStrings::ERROR_INVALID_CREDENTIALS << "\n";
            }
        }
        else
        {
            std::cout << UIStrings::ERROR_INVALID_CREDENTIALS << "\n";
        }
    }
}

void BankSystem::handleAdminMenu()
{
    bool running = true;
    while (running)
    {
        _admin->displayMenu();
        int choice = InputHandler::getIntInput();
        
        switch (static_cast<AdminMenu>(choice))
        {
            case AdminMenu::CREATE_ACCOUNT:
                _admin->createAccount(_accountHolders, _totalAccounts, _arrayCapacity, _nextAccountNumber, _nextTransactionNumber);
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
                std::cout << UIStrings::SUCCESS_LOGOUT << "\n";
                break;
            default:
                std::cout << UIStrings::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::handleCustomerMenu(AccountHolder* holder)
{
    bool running = true;
    while (running)
    {
        holder->displayMenu();
        int choice = InputHandler::getIntInput();
        
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
                std::cout << UIStrings::SUCCESS_LOGOUT << "\n";
                break;
            default:
                std::cout << UIStrings::INVALID_CHOICE << "\n";
        }
    }
}

void BankSystem::handleDeposit(AccountHolder* holder)
{
    double amount;
    std::cout << UIStrings::PROMPT_AMOUNT_DEPOSIT;
    amount = InputHandler::getDoubleInput();
    
    if (!Validator::isValidAmount(amount))
    {
        std::cout << UIStrings::ERROR_INVALID_AMOUNT << "\n";
        return;
    }
    
    if (holder->performDeposit(amount))
    {
        Transaction* txn = new Transaction("Deposit", amount, *_nextTransactionNumber);
        (*_nextTransactionNumber)++;
        holder->getAccount()->addTransaction(txn);
        std::cout << UIStrings::SUCCESS_DEPOSIT << std::fixed << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << UIStrings::ERROR_DEPOSIT_FAILED << "\n";
    }
}

void BankSystem::handleWithdraw(AccountHolder* holder)
{
    double amount;
    std::cout << UIStrings::INFO_CURRENT_BALANCE << std::fixed << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
    std::cout << UIStrings::PROMPT_AMOUNT_WITHDRAW;
    amount = InputHandler::getDoubleInput();
    
    if (!Validator::isValidAmount(amount))
    {
        std::cout << UIStrings::ERROR_INVALID_AMOUNT << "\n";
        return;
    }
    
    if (holder->performWithdraw(amount))
    {
        Transaction* txn = new Transaction("Withdrawal", amount, *_nextTransactionNumber);
        (*_nextTransactionNumber)++;
        holder->getAccount()->addTransaction(txn);
        std::cout << UIStrings::SUCCESS_WITHDRAWAL << std::fixed << std::setprecision(2) << holder->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << UIStrings::ERROR_INSUFFICIENT_BALANCE << "\n";
    }
}

void BankSystem::handleChangePassword(AccountHolder* holder)
{
    std::string oldPassword, newPassword, confirmPassword;
    
    std::cout << UIStrings::PROMPT_CURRENT_PASSWORD;
    std::cin >> oldPassword;
    
    if (!holder->authenticate(oldPassword))
    {
        std::cout << UIStrings::ERROR_INCORRECT_PASSWORD << "\n";
        return;
    }
    
    do
    {
        std::cout << UIStrings::PROMPT_NEW_PASSWORD;
        std::cin >> newPassword;
        if (!Validator::isValidPassword(newPassword))
        {
            std::cout << UIStrings::ERROR_INVALID_PASSWORD << "\n";
        }
    }
    while (!Validator::isValidPassword(newPassword));
    
    std::cout << UIStrings::PROMPT_CONFIRM_NEW_PASSWORD;
    std::cin >> confirmPassword;
    
    if (newPassword != confirmPassword)
    {
        std::cout << "Passwords do not match! Password change failed.\n";
        return;
    }
    
    holder->setPassword(newPassword);
    std::cout << UIStrings::SUCCESS_PASSWORD_CHANGED << "\n";
}

void BankSystem::addAccountHolder(AccountHolder* holder)
{
    if (*_totalAccounts >= *_arrayCapacity)
    {
        int newCapacity = (*_arrayCapacity == 0) ? 2 : (*_arrayCapacity * 2);
        
        AccountHolder** newArray = new AccountHolder*[newCapacity];
        
        for (int account = 0; account < *_totalAccounts; account++)
        {
            newArray[account] = (*_accountHolders)[account];
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
    for (int account = 0; account < *_totalAccounts; account++)
    {
        AccountHolder* holder = (*_accountHolders)[account];
        std::string accountNumber = std::to_string(holder->getAccount()->getAccountNumber());
        if (accountNumber == usernameOrEmail)
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
