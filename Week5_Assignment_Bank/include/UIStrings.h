#ifndef UISTRINGS_H
#define UISTRINGS_H

namespace UIStrings 
{

    constexpr const char* WELCOME_MESSAGE = "========== BANKING SYSTEM ==========";
    constexpr const char* GOODBYE_MESSAGE = "Thank you for using our Banking System!";
    constexpr const char* INVALID_CHOICE = "***Invalid choice! Please try again.***";
    constexpr const char* INVALID_INPUT = "***Invalid input! Please enter a valid input.***";

    constexpr const char* MAIN_MENU_HEADER = "\n========== MAIN MENU ==========";
    constexpr const char* ADMIN_MENU_HEADER = "\n========== ADMIN MENU ==========";
    constexpr const char* CUSTOMER_MENU_HEADER = "\n========== CUSTOMER MENU ==========";
    constexpr const char* LOGIN_HEADER = "\n========== LOGIN ==========";
    constexpr const char* CREATE_ACCOUNT_HEADER = "\n========== CREATE ACCOUNT ==========";
    constexpr const char* DELETE_ACCOUNT_HEADER = "\n========== DELETE ACCOUNT ==========";
    constexpr const char* SEARCH_ACCOUNT_HEADER = "\n========== SEARCH ACCOUNT ==========";
    constexpr const char* ALL_ACCOUNTS_HEADER = "\n========== ALL ACCOUNTS ==========";
    constexpr const char* ACCOUNT_FOUND_HEADER = "\n========== ACCOUNT FOUND ==========";
    constexpr const char* ACCOUNT_BALANCE_HEADER = "\n========== ACCOUNT BALANCE ==========";
    constexpr const char* ACCOUNT_DETAILS_HEADER = "\n========== ACCOUNT DETAILS ==========";
    constexpr const char* MINI_STATEMENT_HEADER = "\n========== MINI STATEMENT ==========";
    constexpr const char* FULL_STATEMENT_HEADER = "\n========== FULL STATEMENT ==========";

    constexpr const char* MENU_LOGIN = "Login";
    constexpr const char* MENU_EXIT = "Exit";
    constexpr const char* MENU_LOGOUT = "Logout";
    constexpr const char* MENU_CREATE_ACCOUNT = "Create Account";
    constexpr const char* MENU_DELETE_ACCOUNT = "Delete Account";
    constexpr const char* MENU_SEARCH_ACCOUNT = "Search Account";
    constexpr const char* MENU_VIEW_ALL_ACCOUNTS = "View All Accounts";
    constexpr const char* MENU_DEPOSIT = "Deposit Money";
    constexpr const char* MENU_WITHDRAW = "Withdraw Money";
    constexpr const char* MENU_VIEW_BALANCE = "View Balance";
    constexpr const char* MENU_MINI_STATEMENT = "Mini Statement";
    constexpr const char* MENU_FULL_STATEMENT = "Full Statement";
    constexpr const char* MENU_CHANGE_PASSWORD = "Change Password";

    constexpr const char* PROMPT_USERNAME = "Username (Account Number or Email): ";
    constexpr const char* PROMPT_PASSWORD = "Password: ";
    constexpr const char* PROMPT_FULL_NAME = "Enter Full Name: ";
    constexpr const char* PROMPT_EMAIL = "Enter Email: ";
    constexpr const char* PROMPT_CONFIRM_PASSWORD = "Confirm Password: ";
    constexpr const char* PROMPT_INITIAL_DEPOSIT = "Enter Initial Deposit (Minimum Rs. ";
    constexpr const char* PROMPT_ACCOUNT_NUMBER = "\nEnter Account Number: ";
    constexpr const char* PROMPT_AMOUNT_DEPOSIT = "\nEnter amount to deposit: Rs. ";
    constexpr const char* PROMPT_AMOUNT_WITHDRAW = "Enter amount to withdraw: Rs. ";
    constexpr const char* PROMPT_CURRENT_PASSWORD = "\nEnter current password: ";
    constexpr const char* PROMPT_NEW_PASSWORD = "Enter new password (6-20 chars, must contain uppercase, lowercase, and digit): ";
    constexpr const char* PROMPT_CONFIRM_NEW_PASSWORD = "Confirm new password: ";
    constexpr const char* PROMPT_SEARCH_CHOICE = "Enter choice: ";
    constexpr const char* PROMPT_ACCOUNT_HOLDER_NAME = "Enter Account Holder Name: ";
    constexpr const char* PROMPT_CONFIRM_DELETE = "Are you sure you want to DELETE this account? (yes/no): ";
    constexpr const char* PROMPT_ENTER_CHOICE = "Enter your choice: ";
    constexpr const char* PROMPT_AGAIN = "Please enter again: ";

    constexpr const char* SUCCESS_ACCOUNT_CREATED = "\n========== ACCOUNT CREATED SUCCESSFULLY ==========";
    constexpr const char* SUCCESS_ACCOUNT_DELETED = "\nAccount deleted successfully!";
    constexpr const char* SUCCESS_DEPOSIT = "\nDeposit successful! New balance: Rs. ";
    constexpr const char* SUCCESS_WITHDRAWAL = "\nWithdrawal successful! New balance: Rs. ";
    constexpr const char* SUCCESS_PASSWORD_CHANGED = "\nPassword changed successfully!";
    constexpr const char* SUCCESS_LOGOUT = "\nLogging out...";

    constexpr const char* ERROR_INVALID_CREDENTIALS = "\nInvalid credentials! Please try again.";
    constexpr const char* ERROR_ACCOUNT_DEACTIVATED = "\nAccount has been deactivated! Please contact admin.";
    constexpr const char* ERROR_ACCOUNT_NOT_FOUND = "\nAccount not found!";
    constexpr const char* ERROR_INVALID_NAME = "Invalid name! Name should contain only alphabets and spaces (2-50 characters).";
    constexpr const char* ERROR_INVALID_EMAIL = "Invalid email format! Please enter a valid email.(Ex: example@gmail.com)";
    constexpr const char* ERROR_INVALID_PASSWORD = "Invalid password! Must be 6-20 characters with uppercase, lowercase, and digit.";
    constexpr const char* ERROR_PASSWORD_MISMATCH = "\nPasswords do not match! Account creation failed.";
    constexpr const char* ERROR_INVALID_AMOUNT = "Invalid amount! Please enter a positive value.";
    constexpr const char* ERROR_INSUFFICIENT_BALANCE = "\nWithdrawal failed! Insufficient balance.";
    constexpr const char* ERROR_DEPOSIT_FAILED = "\nDeposit failed!";
    constexpr const char* ERROR_WITHDRAWAL_FAILED = "\nWithdrawal failed!";
    constexpr const char* ERROR_INCORRECT_PASSWORD = "Incorrect current password!";
    constexpr const char* ERROR_DELETE_FAILED = "\nFailed to delete account!";
    constexpr const char* ERROR_MIN_DEPOSIT = "Initial deposit must be at least Rs. ";
    constexpr const char* ERROR_CONFIRM_PASSWORD = "Maximum attempts exceeded. Account creation cancelled.\n";

    constexpr const char* INFO_WELCOME_ADMIN = "\nWelcome ";
    constexpr const char* INFO_WELCOME_USER = "\nWelcome ";
    constexpr const char* INFO_ACCOUNT_FOUND = "\nAccount Found:";
    constexpr const char* INFO_ACCOUNT_DETAILS_BEFORE_DELETE = "\nAccount Found:\n";
    constexpr const char* INFO_DELETE_CANCELLED = "\nAccount deletion cancelled.";
    constexpr const char* INFO_DATA_REMOVED = "All account data and transaction history have been permanently removed.";
    constexpr const char* INFO_NO_ACCOUNTS = "No accounts found.";
    constexpr const char* INFO_NO_TRANSACTIONS = "No transactions found.";
    constexpr const char* INFO_CURRENT_BALANCE = "\nCurrent Balance: Rs. ";
    constexpr const char* INFO_NEW_BALANCE = "New balance: Rs. ";
    constexpr const char* INFO_TOTAL_ACCOUNTS = "Total Accounts: ";

    constexpr const char* LABEL_ACCOUNT_NUMBER = "Account Number: ";
    constexpr const char* LABEL_ACCOUNT_HOLDER = "Account Holder: ";
    constexpr const char* LABEL_NAME = "Name";
    constexpr const char* LABEL_EMAIL = "Email: ";
    constexpr const char* LABEL_BALANCE = "Balance: Rs. ";
    constexpr const char* LABEL_STATUS = "Status: ";
    constexpr const char* LABEL_CREATED_AT = "Created At: ";
    constexpr const char* LABEL_TOTAL_TRANSACTIONS = "Total Transactions: ";
    constexpr const char* LABEL_CURRENT_BALANCE = "Current Balance: Rs. ";
    constexpr const char* LABEL_INITIAL_BALANCE = "Initial Balance: Rs. ";
    constexpr const char* LABEL_DATE_TIME = "Date & Time";
    constexpr const char* LABEL_TRANSACTION_ID = "Transaction ID";
    constexpr const char* LABEL_TYPE = "Type";
    constexpr const char* LABEL_AMOUNT = "Amount";
    constexpr const char* LABEL_MINI_STATEMENT = "\n========== MINI STATEMENT ==========\n";

    constexpr const char* VALIDATION_NAME_RULE = "Invalid name! Name should contain only alphabets and spaces (2-50 characters).";
    constexpr const char* VALIDATION_EMAIL_RULE = "Invalid email format! Please enter a valid email (example@gmail.com).";
    constexpr const char* VALIDATION_PASSWORD_RULE = "Invalid password! Must be 6-20 characters with uppercase, lowercase, and digit.";
    constexpr const char* VALIDATION_AMOUNT_RULE = "Invalid amount! Please enter a positive value.";

    constexpr const char* SEARCH_BY_NUMBER = "1. Account Number";
    constexpr const char* SEARCH_BY_NAME = "2. Account Holder Name";

    constexpr const char* SEPARATOR_EQUALS = "==================================================";
    constexpr const char* SEPARATOR_DASHES = "================================";
    constexpr const char* NEWLINE = "\n";

    constexpr const char* LOGIN_INFO_ACCOUNT_NUMBER = "  - Account Number: ";
    constexpr const char* LOGIN_INFO_EMAIL = "  - Email: ";
    constexpr const char* LOGIN_INFO_REMEMBER = "Please remember your credentials for future login.";

}

#endif
