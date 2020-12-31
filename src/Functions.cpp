#include "main.h"
#include "Headers/Motors.hpp"
#include "Headers/Functions.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Sensors.hpp"
#include "Headers/Robot.hpp"
#include <iostream>

using namespace std;
using namespace pros;
using namespace motion;

void print(void*)
{
    pros::lcd::initialize();//initialize the lcd on the brain
    while(!pros::lcd::is_initialized()){pros::delay(1);}//wait until lcd is initialized
    int target = pros::millis() + 5000, count = 0;//set target time to 15 seconds into the future
    while(true)
    {
        pros::lcd::print(1, "X:%f, Y:%f, A:%f\n", odom.x, odom.y, radToDeg(odom.a));
        pros::lcd::print(2, "WS:%f, LR:%f, B:%f", odom.wheelSize, odom.distance_LR, odom.distance_B);
        //print potentiometer values and coordinate location and angle of the bot
        if(target <= pros::millis())
        {
          target += 5000;//updates target
          count++;//increases count
        }

        if(count % 2 == 0)//if count is an even number display motor temperatures
        {

        }
        else//if count is odd display current draw of the motors
        {

        }
        pros::delay(5);
    }
}
