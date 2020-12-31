#include "main.h"
#include "Headers/Motors.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Robot.hpp"

using namespace motion;
using namespace robot;

//base object declaration
baseStruct base;

//base motor declaration
pros::Motor baseStruct::RF(0);
pros::Motor baseStruct::RM(0);
pros::Motor baseStruct::RB(0);
pros::Motor baseStruct::LF(0);
pros::Motor baseStruct::LM(0);
pros::Motor baseStruct::LB(0);
pros::Motor baseStruct::RFT(0);
pros::Motor baseStruct::LFT(0);
pros::Motor baseStruct::RBT(0);
pros::Motor baseStruct::LBT(0);

//pid and odom object declaration
pidStruct drivingPID;
pidStruct turningPID;
odomStruct odom;

bool init = false;

//odom variable initialization
double odomStruct::wheelSize = 0;
double odomStruct::distance_LR = 0;
double odomStruct::distance_B = 0;
pros::ADIEncoder odomStruct::LeftTracker(0,0);
pros::ADIEncoder odomStruct::RightTracker(0,0);
pros::ADIEncoder odomStruct::BackTracker(0,0);
double odomStruct::x = 0;
double odomStruct::y = 0;
double odomStruct::a = 0;
double odomStruct::radiusR = 0;
double odomStruct::radiusB = 0;
double odomStruct::h = 0;
double odomStruct::h2 = 0;
double odomStruct::theta = 0;
double odomStruct::beta = 0;
double odomStruct::alpha = 0;
double odomStruct::Xx = 0;
double odomStruct::Xy = 0;
double odomStruct::Yx = 0;
double odomStruct::Yy = 0;
double odomStruct::newleft = 0;
double odomStruct::newright = 0;
double odomStruct::newback = 0;
double odomStruct::Right = 0;
double odomStruct::Left = 0;
double odomStruct::Back = 0;
double odomStruct::lastleft = 0;
double odomStruct::lastright = 0;
double odomStruct::lastback = 0;

void driverControl::intakes(void*)
{
    int L1, L2, R1;//buttons used for intakes
    while(true)
    {
        //set button variables to controller inputs
        L1 = master.get_digital(DIGITAL_L1);
        L2 = master.get_digital(DIGITAL_L2);
        R1 = master.get_digital(DIGITAL_R1);

        //use ternary functions to set voltages depending on the buttons pressed
        // RI.move_voltage(L1 ? 10000 : L2 ? -10000 : 0);
        // LI.move_voltage(L1 ? 10000 : L2 ? -10000 : 0);
        pros::delay(5);
    }
}

void driverControl::driveBase(void*)
{
    int lPow, rPow;//motor power variables
    while(true)
    {
        //set power variables to controller inputs mapped to voltage
        lPow = int(master.get_analog(ANALOG_LEFT_Y) * 10000/127);
        rPow = int(master.get_analog(ANALOG_RIGHT_Y) * 10000/127);

        base.move(lPow, rPow);//apply variables to robot base library move function
        pros::delay(5);
    }
}
