#ifndef UISTRINGS_H
#define UISTRINGS_H

namespace UIStrings
{
    constexpr char SEPARATOR[]             = "  ================================================\n";
    constexpr char NEWLINE[]               = "\n";

    constexpr char TITLE_SYSTEM[]          = "SALARY MANAGEMENT SYSTEM";
    constexpr char TITLE_LOGIN[]           = "LOGIN";
    constexpr char TITLE_ADMIN_PANEL[]     = "ADMIN PANEL";
    constexpr char TITLE_EMP_PANEL[]       = "EMPLOYEE PANEL";
    constexpr char TITLE_ROLE_SELECT[]     = "SELECT CONTROL MODE";

    constexpr char HEADER_ADD_EMP[]           = "ADD EMPLOYEE";
    constexpr char HEADER_ALL_EMP[]           = "ALL EMPLOYEES";
    constexpr char HEADER_UPDATE_EMP[]        = "UPDATE EMPLOYEE";
    constexpr char HEADER_DELETE_EMP[]        = "DELETE EMPLOYEE";
    constexpr char HEADER_ALL_SALARIES[]      = "ALL SALARIES";
    constexpr char HEADER_GRANT_ADMIN[]       = "GRANT ADMIN ACCESS";
    constexpr char HEADER_REVOKE_ADMIN[]      = "REVOKE ADMIN ACCESS";
    constexpr char HEADER_MY_DETAILS[]        = "MY DETAILS";
    constexpr char HEADER_MY_LEAVE[]          = "MY LEAVE BALANCE";
    constexpr char HEADER_MY_SALARY[]         = "MY SALARY";
    constexpr char HEADER_RECORD_LEAVES[]     = "RECORD LEAVES";

    constexpr char MENU_MAIN_LOGIN[]       = "  [1] Login\n";
    constexpr char MENU_MAIN_EXIT[]        = "  [2] Exit\n";

    constexpr char MENU_ADMIN_ADD[]        = "  [1] Add Employee\n";
    constexpr char MENU_ADMIN_VIEW[]       = "  [2] View All Employees\n";
    constexpr char MENU_ADMIN_UPDATE[]     = "  [3] Update Employee\n";
    constexpr char MENU_ADMIN_DELETE[]     = "  [4] Delete Employee\n";
    constexpr char MENU_ADMIN_SALARY[]     = "  [5] View All Salaries\n";
    constexpr char MENU_ADMIN_GRANT[]      = "  [6] Grant Admin Access\n";
    constexpr char MENU_ADMIN_REVOKE[]     = "  [7] Revoke Admin Access\n";
    constexpr char MENU_ADMIN_LOGOUT[]     = "  [8] Logout\n";

    constexpr char MENU_EMP_DETAILS[]      = "  [1] View My Details\n";
    constexpr char MENU_EMP_LEAVE[]        = "  [2] View Leave Balance\n";
    constexpr char MENU_EMP_SALARY[]       = "  [3] View My Salary\n";
    constexpr char MENU_EMP_RECORD[]       = "  [4] Record Leaves Taken\n";
    constexpr char MENU_EMP_LOGOUT[]       = "  [5] Logout\n";

    constexpr char MENU_ROLE_ADMIN[]       = "  [1] Admin Controls\n";
    constexpr char MENU_ROLE_EMP[]         = "  [2] Employee Controls\n";
    constexpr char MENU_ROLE_LOGOUT[]      = "  [3] Logout\n";

    constexpr char PROMPT_CHOICE[]         = "  Choice: ";
    constexpr char PROMPT_CONTINUE[]       = "\n  Press Enter to continue...";
    constexpr char PROMPT_ID[]       = "  Employee ID / Admin ID: ";
    constexpr char PROMPT_PASSWORD[]       = "  Password              : ";
    constexpr char PROMPT_EMP_ID[]         = "  Employee ID: ";
    constexpr char PROMPT_CONFIRM_DEL[]    = "  Are you sure? (y/n): ";

    constexpr char INPUT_NAME[]            = "  Name       : ";
    constexpr char INPUT_DOB[]             = "  DOB (DD/MM/YYYY): ";
    constexpr char INPUT_EMAIL[]           = "  Email      : ";
    constexpr char INPUT_PHONE[]           = "  Phone      : ";
    constexpr char INPUT_DEPT[]            = "  Department : ";
    constexpr char INPUT_POSITION[]        = "  Position   : ";
    constexpr char INPUT_SALARY[]          = "  Basic Salary: ";
    constexpr char INPUT_PASSWORD[]        = "  Password   : ";
    constexpr char INPUT_LEAVES[]          = "  Enter total leaves taken this month: ";

    constexpr char DETAIL_HEADER[]         = "\n  -- EMPLOYEE DETAILS ---------------------\n";
    constexpr char DETAIL_FOOTER[]         = "  -----------------------------------------\n";
    constexpr char LABEL_ID[]              = "  ID         : ";
    constexpr char LABEL_NAME[]            = "  Name       : ";
    constexpr char LABEL_DOB[]             = "  DOB        : ";
    constexpr char LABEL_EMAIL[]           = "  Email      : ";
    constexpr char LABEL_PHONE[]           = "  Phone      : ";
    constexpr char LABEL_DEPT[]            = "  Department : ";
    constexpr char LABEL_POSITION[]        = "  Position   : ";
    constexpr char LABEL_ADMIN[]           = "  Admin      : ";

    constexpr char LEAVE_HEADER[]          = "\n  -- LEAVE INFORMATION --------------------\n";
    constexpr char LEAVE_FOOTER[]          = "  -----------------------------------------\n";
    constexpr char LABEL_ALLOC_LEAVES[]    = "  Allocated Leaves : ";
    constexpr char LABEL_TAKEN_LEAVES[]    = "  Leaves Taken     : ";
    constexpr char LABEL_LEAVE_BAL[]       = "  Leave Balance    : ";

    constexpr char SALARY_HEADER[]         = "\n  -- SALARY BREAKDOWN ---------------------\n";
    constexpr char SALARY_FOOTER[]         = "  -----------------------------------------\n";
    constexpr char LABEL_BASIC_SAL[]       = "  Basic Salary   : ";
    constexpr char LABEL_LEAVES_TAKEN[]    = "  Leaves Taken   : ";
    constexpr char LABEL_ALLOC_LVS[]       = "  Allocated Leave: ";
    constexpr char LABEL_LEAVE_BAL2[]      = "  Leave Balance  : ";
    constexpr char LABEL_DAILY_RATE[]      = "  Daily Rate     : ";
    constexpr char LABEL_BONUS[]           = "  Bonus (+)      : ";
    constexpr char LABEL_DEDUCTION[]       = "  Deduction (-)  : ";
    constexpr char LABEL_NET_SAL[]         = "  NET SALARY     : ";

    constexpr char COL_ID[]                = "ID";
    constexpr char COL_NAME[]              = "Name";
    constexpr char COL_DEPT[]              = "Department";
    constexpr char COL_POSITION[]          = "Position";
    constexpr char COL_ADMIN[]             = "Admin";
    constexpr char COL_BASIC[]             = "Basic";
    constexpr char COL_LEAVES[]            = "Leaves";
    constexpr char COL_BONUS[]             = "Bonus";
    constexpr char COL_DEDUCTION[]         = "Deduction";
    constexpr char COL_NET[]               = "Net Salary";

    constexpr char UPDATE_BLANK_ENTER[]     = "\n  Leave blank and press Enter to keep current value.\n\n";
    constexpr char UPDATE_INVALID_NAME[]   = "[!] Invalid name, kept original.\n";
    constexpr char UPDATE_INVALID_DATE[]   = "[!] Invalid date, kept original.\n";
    constexpr char UPDATE_INVALID_EMAIL[]  = "[!] Invalid email, kept original.\n";
    constexpr char UPDATE_INVALID_PHONE[]  = "[!] Invalid phone, kept original.\n";
    constexpr char UPDATE_INVALID_SAL[]    = "[!] Invalid salary, kept original.\n";

    constexpr char CURR_LEAVES_TAKEN[]     = "  Current leaves taken: ";
    constexpr char ALLOC_LEAVES_LABEL[]    = "  Allocated leaves    : ";

    constexpr char MSG_EMP_ADDED[]         = "\n  [OK] Employee added successfully.\n";
    constexpr char MSG_EMP_UPDATED[]       = "\n  [OK] Employee updated successfully.\n";
    constexpr char MSG_EMP_DELETED[]       = "  [OK] Employee deleted.\n";
    constexpr char MSG_GRANT_OK[]          = "\n  [OK] Admin access granted to ";
    constexpr char MSG_REVOKE_OK[]         = "\n  [OK] Admin access revoked from ";
    constexpr char MSG_SHUTDOWN[]           = "\n  Program ended...!\n";
    constexpr char MSG_DELETING[]          = "\n  Deleting: ";
    constexpr char MSG_TOTAL_EMP[]         = "\n  Total: ";
    constexpr char MSG_TOTAL_EMP_SUFFIX[]  = " employee(s).\n";

    constexpr char ERR_ADD_FAILED[]        = "\n[!] Failed to add employee. Email may already exist.\n";
    constexpr char ERR_SELF_REVOKE[]       = "\n[!] You cannot revoke your own admin access while logged in.\n";
    constexpr char ERR_NOT_FOUND[]         = "\n[!] Employee not found.\n";
    constexpr char ERR_LOGIN_FAILED[]      = "\n[!] Invalid ID or password. Please try again.\n";
    constexpr char ERR_DEL_CANCELLED[]     = "[!] Deletion cancelled.\n";
    constexpr char ERR_NO_EMPLOYEES[]      = "\n  No employees found.\n";
    constexpr char ERR_INVALID_CHOICE[]    = "[!] Invalid choice. Enter ";

    constexpr char YES[]                   = "Yes";
    constexpr char NO[]                    = "No";
} 

#endif
