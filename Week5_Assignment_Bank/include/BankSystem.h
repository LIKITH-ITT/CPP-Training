#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <string>
#include "Admin.h"
#include "AccountHolder.h"
#include "Validator.h"

class BankSystem
{
private:
    void displayMainMenu();
    void handleLogin();
    void handleRegistration();
    void handleAdminMenu();
    void handleCustomerMenu(AccountHolder* holder);
    void handleDeposit(AccountHolder* holder);
    void handleWithdraw(AccountHolder* holder);
    void handleChangePassword(AccountHolder* holder);
    void addAccountHolder(AccountHolder* holder);
    AccountHolder* findAccountHolderByUsernameOrEmail( std::string& usernameOrEmail);
    int getIntInput();
    double getDoubleInput();
    long getLongInput();
    
    Admin* _admin;
    AccountHolder*** _accountHolders;
    int* _totalAccounts;
    int* _arrayCapacity;
    long* _nextAccountNumber;
    long* _nextTransactionNumber;
    
public:
    BankSystem();
    ~BankSystem();
    void run();
};

#endif
