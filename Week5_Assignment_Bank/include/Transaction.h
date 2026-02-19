#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include "Constants.h"

class Transaction 
{
private:
    std::string _transactionID;
    std::string _type;
    double _amount;
    std::time_t _timestamp;
    Transaction* _next;
    
public:
    Transaction(const std::string& txnType, double amt, long txnNum);
    
    std::string getTransactionID() ;
    std::string getType() ;
    double getAmount() ;
    std::time_t getTimestamp() ;
    Transaction* getNext() ;
    void setNext(Transaction* nextTxn);
    std::string getDateTime() ;
    std::string getTransaction() ;
};

#endif
