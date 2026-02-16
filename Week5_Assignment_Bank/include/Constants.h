#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants 
{

    constexpr long INITIAL_ACCOUNT_NUMBER = 10000000;
    constexpr long INITIAL_TRANSACTION_ID = 100000000;
    const std::string TRANSACTION_PREFIX = "TXN";

    constexpr int ACCOUNT_NUMBER_LENGTH = 8;

    const std::string ADMIN_USERNAME = "admin";
    const std::string ADMIN_PASSWORD = "Admin123";
    const long ADMIN_ID = 99999999;


    constexpr int MIN_PASSWORD_LENGTH = 6;
    constexpr int MAX_PASSWORD_LENGTH = 20;
    constexpr int MIN_NAME_LENGTH = 2;
    constexpr int MAX_NAME_LENGTH = 50;

    constexpr double MIN_DEPOSIT_AMOUNT = 100.0;
    constexpr double MIN_BALANCE = 0.0;

    constexpr int STATEMENT_DISPLAY_LIMIT = 5;
}

enum class MainMenu {
        EXIT,
        LOGIN
    };

    enum class AdminMenu {
        EXIT,
        CREATE_ACCOUNT,
        DELETE_ACCOUNT,
        SEARCH_ACCOUNT,
        VIEW_ALL_ACCOUNTS
    };

    enum class CustomerMenu {
        EXIT,
        DEPOSIT,
        WITHDRAW,
        VIEW_BALANCE,
        MINI_STATEMENT,
        FULL_STATEMENT,
        CHANGE_PASSWORD
    };

    enum class TransactionType {
        DEPOSIT,
        WITHDRAWAL,
        ACCOUNT_OPENING
    };

#endif
