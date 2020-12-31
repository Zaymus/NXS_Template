#include "main.h"
#include "Headers/Functions.hpp"
#include "Headers/Robot.hpp"
#include "Headers/Tasks.hpp"


pros::Task printTask(print);
pros::Task driveTask(driverControl::driveBase);
pros::Task intakeTask(driverControl::intakes);
pros::Task updateTask(motion::odom.update);
