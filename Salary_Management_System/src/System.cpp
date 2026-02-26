#include "System.h"
#include "Constants.h"
#include "Logger.h"

System::System() : admin(ADMIN_ID, ADMIN_PASSWORD), employeeManager(), authController(admin, employeeManager) {}

void System::run() {
    authController.run();
}
