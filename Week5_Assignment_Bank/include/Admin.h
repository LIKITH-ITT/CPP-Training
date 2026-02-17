#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Constants.h"

class AccountHolder;

class Admin : public User 
{
private:
    long  getAccountNumberInput();
    double getDepositAmount();
    std::string getStringInput();
    void addAccountHolder(AccountHolder* holder, AccountHolder*** accountHolders, int* totalAccounts, int* arrayCapacity);
    AccountHolder* findAccountByNumber(AccountHolder*** accountHolders, int totalAccounts, long accNum);
    AccountHolder* findAccountByName(AccountHolder*** accountHolders, int totalAccounts, std::string& name);
    bool removeAccountHolder(AccountHolder*** accountHolders, int* totalAccounts, long accNum);
    
    std::string _adminName;
    
public:
    Admin();
    ~Admin();
    
    std::string getAdminName();
    void displayMenu() override;
    
    void createAccount(AccountHolder*** accountHolders, int* totalAccounts, int* arrayCapacity, long* nextAccountNumber, long* nextTransactionNumber);
    void deleteAccount(AccountHolder*** accountHolders, int* totalAccounts);
    void searchAccount(AccountHolder*** accountHolders, int totalAccounts);
    void viewAllAccounts(AccountHolder*** accountHolders, int totalAccounts);
};

#endif
