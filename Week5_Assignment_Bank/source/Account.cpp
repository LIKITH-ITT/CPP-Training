#include "Account.h"
#include "Constants.h"
#include <iostream>
#include "Logger.h"
#include <iomanip>

Account::Account(long accNum, double initialDeposit) 
{
    _accountNumber = accNum;
    _balance = initialDeposit;
    _transactionHead = nullptr;
    _transactionCount = 0;
    _isActive = true;
    _createdAt = std::time(nullptr);
}

Account::~Account() 
{
    Transaction* current = _transactionHead;
    while (current != nullptr) 
    {
        Transaction* temp = current;
        current = current->getNext();
        delete temp;
    }
}

long Account::getAccountNumber()  
{
    return _accountNumber;
}

double Account::getBalance()  
{
    return _balance;
}

Transaction* Account::getTransactionHead()  
{
    return _transactionHead;
}

int Account::getTransactionCount()  
{
    return _transactionCount;
}

bool Account::getIsActive()  
{
    return _isActive;
}

std::time_t Account::getCreatedAt()  
{
    return _createdAt;
}

void Account::deactivate() 
{
    _isActive = false;
}

std::string Account::getCreationDateTime()  
{
    char buffer[30];
    struct tm* timeinfo = std::localtime(&_createdAt);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

std::string Account::getStatus()  
{
    return _isActive ? "Active" : "Deactivated";
}

void Account::addTransaction(Transaction* txn) 
{
    if (_transactionHead == nullptr) {
        _transactionHead = txn;
    } else {
        txn->setNext(_transactionHead);
        _transactionHead = txn;
    }
    _transactionCount++;
}

bool Account::deposit(double amount) 
{
    if (amount <= 0) {
        return false;
    }
    _balance += amount;
    return true;
}

bool Account::withdraw(double amount) 
{
    if (amount <= 0 || amount > _balance) 
    {
        return false;
    }
    _balance -= amount;
    return true;
}

void Account::printMiniStatement()  {
    std::cout << "\n========== MINI STATEMENT ==========\n";
    std::cout << Logger::LABEL_ACCOUNT_NUMBER << _accountNumber << "\n";
    std::cout << Logger::LABEL_CURRENT_BALANCE << std::fixed << std::setprecision(2) << _balance << "\n\n";
    
    if (_transactionHead == nullptr) 
    {
        std::cout << "No transactions found.\n";
        return;
    }
    
    std::cout << std::left << std::setw(22) << Logger::LABEL_DATE_TIME
              << std::setw(18) << Logger::LABEL_TRANSACTION_ID
              << std::setw(20) << Logger::LABEL_TYPE
              << std::right << std::setw(12) << Logger::LABEL_AMOUNT << std::endl;
    std::cout << std::string(72, '-') << std::endl;
    
    Transaction* current = _transactionHead;
    int count = 0;
    while (current != nullptr && count < Constants::STATEMENT_DISPLAY_LIMIT) 
    {
        current->print();
        current = current->getNext();
        count++;
    }
    std::cout << std::string(72, '=') << "\n";
}

void Account::printFullStatement()  
{
    std::cout << "\n========== FULL STATEMENT ==========\n";
    std::cout << Logger::LABEL_ACCOUNT_NUMBER << _accountNumber << "\n";
    std::cout << Logger::LABEL_CURRENT_BALANCE << std::fixed << std::setprecision(2) << _balance << "\n\n";
    
    if (_transactionHead == nullptr) 
    {
        std::cout << "No transactions found.\n";
        return;
    }
    
    std::cout << std::left << std::setw(22) << Logger::LABEL_DATE_TIME
              << std::setw(18) << Logger::LABEL_TRANSACTION_ID
              << std::setw(20) << Logger::LABEL_TYPE
              << std::right << std::setw(12) << Logger::LABEL_AMOUNT << std::endl;
    std::cout << std::string(72, '-') << std::endl;
    
    Transaction* current = _transactionHead;
    while (current != nullptr) 
    {
        current->print();
        current = current->getNext();
    }
    std::cout << std::string(72, '=') << "\n";
}
