#include "AccountHolder.h"
#include "Logger.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>
#include <sstream>

AccountHolder::AccountHolder(long accNum, std::string& holderName, std::string& holderEmail, std::string& pwd, double initialDeposit) : User(accNum, pwd) 
{
    _account = new Account(accNum, initialDeposit);
    _name = holderName;
    _email = holderEmail;
}

AccountHolder::~AccountHolder() 
{
    delete _account;
}

Account* AccountHolder::getAccount()  
{
    return _account;
}

std::string AccountHolder::getName()  
{
    return _name;
}

std::string AccountHolder::getEmail() 
{
    return _email;
}

void AccountHolder::displayMenu() {

    std::cout << "\n========== CUSTOMER MENU ==========\n";
    std::cout << static_cast<int>(CustomerMenu::DEPOSIT) << ". Deposit Money\n";
    std::cout << static_cast<int>(CustomerMenu::WITHDRAW) << ". Withdraw Money\n";
    std::cout << static_cast<int>(CustomerMenu::VIEW_BALANCE) << ". View Balance\n";
    std::cout << static_cast<int>(CustomerMenu::MINI_STATEMENT) << ". Mini Statement\n";
    std::cout << static_cast<int>(CustomerMenu::FULL_STATEMENT) << ". Full Statement\n";
    std::cout << static_cast<int>(CustomerMenu::CHANGE_PASSWORD) << ". Change Password\n";
    std::cout << static_cast<int>(CustomerMenu::EXIT) << ". Logout\n";
    std::cout << "===================================\n";
    std::cout << Logger::PROMPT_ENTER_CHOICE;
}

bool AccountHolder::performWithdraw(double amount) 
{
    return _account->withdraw(amount);
}

bool AccountHolder::performDeposit(double amount) 
{
    return _account->deposit(amount);
}

void AccountHolder::viewBalance()  
{
    std::cout << "\n========== ACCOUNT BALANCE ==========\n";
    std::cout << Logger::LABEL_ACCOUNT_NUMBER << _account->getAccountNumber() << "\n";
    std::cout << Logger::LABEL_ACCOUNT_HOLDER << _name << "\n";
    std::cout << Logger::LABEL_CURRENT_BALANCE << std::fixed << std::setprecision(2) << _account->getBalance() << "\n";
    std::cout << "=====================================\n";
}

void AccountHolder::printMiniStatement()  
{
    _account->printMiniStatement();
}

void AccountHolder::printBankStatement()  
{
    _account->printFullStatement();
}

void AccountHolder::printAccountDetails()  
{
    std::cout << "\n========== ACCOUNT DETAILS ==========\n";
    std::cout << Logger::LABEL_ACCOUNT_NUMBER << _account->getAccountNumber() << "\n";
    std::cout << Logger::LABEL_ACCOUNT_HOLDER << _name << "\n";
    std::cout << Logger::LABEL_EMAIL << _email << "\n";
    std::cout << Logger::LABEL_BALANCE << std::fixed << std::setprecision(2) << _account->getBalance() << "\n";
    std::cout << Logger::LABEL_STATUS << _account->getStatus() << "\n";
    std::cout << Logger::LABEL_CREATED_AT << _account->getCreationDateTime() << "\n";
    std::cout << Logger::LABEL_TOTAL_TRANSACTIONS << _account->getTransactionCount() << "\n";
    std::cout << "=====================================\n";
}
