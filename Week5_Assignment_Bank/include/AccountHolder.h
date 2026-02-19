#ifndef ACCOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include "User.h"
#include "Account.h"
#include <string>

class AccountHolder : public User 
{
private:
    static std::string generateUserID(long accNum);
    
    Account* _account;
    std::string _name;
    std::string _email;
    
public:
    AccountHolder(long accNum,  std::string& holderName,  std::string& holderEmail,  std::string& pwd, double initialDeposit);
    ~AccountHolder();
    
    Account* getAccount() ;
    std::string getName() ;
    std::string getEmail() ;
    
    void displayMenu() override;
    bool performWithdraw(double amount);   
    bool performDeposit(double amount);
    void viewBalance() ;
    void printMiniStatement() ;
    void printBankStatement() ;
    void printAccountDetails() ;
};

#endif
