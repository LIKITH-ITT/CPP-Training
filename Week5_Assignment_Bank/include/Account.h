#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime>
#include "Transaction.h"

class Account 
{
private:
    long _accountNumber;
    double _balance;
    Transaction* _transactionHead;
    int _transactionCount;
    bool _isActive;
    std::time_t _createdAt;
    
public:
    Account(long accNum, double initialDeposit);
    ~Account();
    
    long getAccountNumber();
    double getBalance();
    Transaction* getTransactionHead();
    int getTransactionCount();
    bool getIsActive();
    std::time_t getCreatedAt();   
    void deactivate();    
    std::string getCreationDateTime();
    std::string getStatus();
    void addTransaction(Transaction* txn);
    bool deposit(double amount);
    bool withdraw(double amount);
    void printMiniStatement();
    void printFullStatement();
};

#endif
