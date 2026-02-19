#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Transaction::Transaction(const std::string& txnType, double amt, long txnNumber)
{
    std::string numberString = std::to_string(txnNumber);

    while (numberString.length() < 9)
    {
        numberString = "0" + numberString;
    }

    _transactionID = Constants::TRANSACTION_PREFIX + numberString;
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

std::string Transaction::getTransaction()
{
    std::ostringstream oss;

    oss << std::left << std::setw(22) << getDateTime()
        << std::setw(18) << _transactionID
        << std::setw(20) << _type
        << std::right << std::setw(12)
        << std::fixed << std::setprecision(2)
        << _amount;

    return oss.str();
}
