#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Transaction::Transaction(const std::string& txnType, double amt, long txnNumber) 
{
    std::ostringstream oss;
    oss << Constants::TRANSACTION_PREFIX << std::setw(9) << std::setfill('0') << txnNumber;
    _transactionID = oss.str();
    _type = txnType;
    _amount = amt;
    _timestamp = std::time(nullptr);
    _next = nullptr;
}

std::string Transaction::getTransactionID()  
{
    return _transactionID;
}

std::string Transaction::getType()  
{
    return _type;
}

double Transaction::getAmount()  
{
    return _amount;
}

std::time_t Transaction::getTimestamp()  
{
    return _timestamp;
}

Transaction* Transaction::getNext()  
{
    return _next;
}

void Transaction::setNext(Transaction* nextTxn)
{
    _next = nextTxn;
}

std::string Transaction::getDateTime()  
{   
    char timeBuffer[20];
    struct tm* timeinfo = std::localtime(&_timestamp);
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(timeBuffer);
}

void Transaction::print()  
{
    std::cout << std::left << std::setw(22) << getDateTime()
              << std::setw(18) << _transactionID
              << std::setw(20) << _type
              << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
              << _amount << std::endl;
}
