#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

constexpr int ALLOCATED_LEAVES = 2;
constexpr int WORKING_DAYS = 30;
constexpr int INITIAL_CAPACITY = 4;
constexpr int INITIAL_EMP_ID = 1001;

const std::string ADMIN_ID = "admin";
const std::string ADMIN_PASSWORD = "Admin@123";

enum class MainMenuOption {
    LOGIN = 1,
    EXIT
};

enum class RoleMenuOption {
    ADMIN_CONTROLS = 1,
    EMPLOYEE_CONTROLS,
    LOGOUT
};

enum class AdminMenuOption {
    ADD_EMPLOYEE = 1,
    VIEW_EMPLOYEES,
    UPDATE_EMPLOYEE,
    DELETE_EMPLOYEE,
    VIEW_SALARIES,
    GRANT_ADMIN,
    REVOKE_ADMIN,
    LOGOUT
};

enum class EmployeeMenuOption {
    VIEW_DETAILS = 1,
    VIEW_LEAVE,
    VIEW_SALARY,
    RECORD_LEAVES,
    LOGOUT
};

#endif
