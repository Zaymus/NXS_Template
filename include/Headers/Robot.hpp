#include "main.h"
#include "Headers/Functions.hpp"

#ifndef ROBOT_HPP
#define ROBOT_HPP
using namespace std;

namespace robot{

    bool is_reversed(int x){
        return x < 0;
    }

    struct baseStruct{
        static pros::Motor RF, RM, RB, LF, LM, LB, RFT, RBT, LFT, LBT;

        enum style_e {
            QUAD,
            SEX,
            OCT,
            ERR
        };

        style_e style = ERR;

        /*
        * 4 motor drive base creation
        */
        void create(int RightFront, int RightBack, int LeftFront, int LeftBack, pros::motor_gearset_e gearset){
            pros::Motor RF(RightFront, gearset, is_reversed(RightFront));
            pros::Motor RB(RightBack, gearset, is_reversed(RightBack));
            pros::Motor LF(LeftFront, gearset, is_reversed(LeftFront));
            pros::Motor LB(LeftBack, gearset, is_reversed(LeftBack));

            style = QUAD;
        }

        /*
        * 6 motor tank drive base creation
        */
        void create(int RightFront, int RightMid, int RightBack, int LeftFront, int LeftMid, int LeftBack, pros::motor_gearset_e gearset){
            pros::Motor RF(RightFront, gearset, is_reversed(RightFront));
            pros::Motor RM(RightMid, gearset, is_reversed(RightMid));
            pros::Motor RB(RightBack, gearset, is_reversed(RightBack));
            pros::Motor LF(LeftFront, gearset, is_reversed(LeftFront));
            pros::Motor LM(LeftMid, gearset, is_reversed(LeftMid));
            pros::Motor LB(LeftBack, gearset, is_reversed(LeftBack));

            style = SEX;
        }

        /*
        * 8 motor drive base creation
        */
        void create(int RightFront, int RightFrontTop, int RightBack, int RightBackTop, int LeftFront, int LeftFrontTop, int LeftBack, int LeftBackTop, pros::motor_gearset_e gearset){
            pros::Motor RF(RightFront, gearset, is_reversed(RightFront));
            pros::Motor RFT(RightFrontTop, gearset, is_reversed(RightFrontTop));
            pros::Motor RB(RightBack, gearset, is_reversed(RightBack));
            pros::Motor RBT(RightBackTop, gearset, is_reversed(RightBackTop));
            pros::Motor LF(LeftFront, gearset, is_reversed(LeftFront));
            pros::Motor LFT(LeftFrontTop, gearset, is_reversed(LeftFrontTop));
            pros::Motor LB(LeftBack, gearset, is_reversed(LeftBack));
            pros::Motor LBT(LeftBackTop, gearset, is_reversed(LeftBackTop));

            style = OCT;
        }

        void move(int left, int right){
            switch(style){
                case QUAD:
                    RF.move_voltage(right);
                    RB.move_voltage(right);
                    LF.move_voltage(left);
                    LB.move_voltage(left);
                    break;

                case SEX:
                    RF.move_voltage(right);
                    RM.move_voltage(right);
                    RB.move_voltage(right);
                    LF.move_voltage(left);
                    LM.move_voltage(left);
                    LB.move_voltage(left);
                    break;

                case OCT:
                    RF.move_voltage(right);
                    RFT.move_voltage(right);
                    RB.move_voltage(right);
                    RBT.move_voltage(right);
                    LF.move_voltage(left);
                    LFT.move_voltage(left);
                    LB.move_voltage(left);
                    LBT.move_voltage(left);
                    break;
                default:
                break;

            }
        }

        void move(int x, int y, int a){
            switch(style){
                case QUAD:
                    LF.move_voltage(y + x + a);
                    LB.move_voltage(y + x - a);
                    RF.move_voltage(y - x - a);
                    RB.move_voltage(y - x + a);
                    break;

                case OCT:
                    LF.move_voltage(y + x + a);
                    LFT.move_voltage(y + x + a);
                    LB.move_voltage(y + x - a);
                    LBT.move_voltage(y + x - a);
                    RF.move_voltage(y - x - a);
                    RFT.move_voltage(y - x - a);
                    RB.move_voltage(y - x + a);
                    RBT.move_voltage(y - x + a);
                    break;
                default:
                break;
            }
        }

        void move(double h, int pow, int rot){
            switch(style){
                case QUAD:
                    LF.move_voltage(pow * cos(h) + rot);
                    LB.move_voltage(pow * sin(h) + rot);
                    RF.move_voltage(pow * sin(h) - rot);
                    RB.move_voltage(pow * cos(h) - rot);
                    break;

                case OCT:
                    LF.move_voltage(pow * cos(h) + rot);
                    LFT.move_voltage(pow * cos(h) + rot);
                    LB.move_voltage(pow * sin(h) + rot);
                    LBT.move_voltage(pow * sin(h) + rot);
                    RF.move_voltage(pow * sin(h) - rot);
                    RFT.move_voltage(pow * sin(h) - rot);
                    RB.move_voltage(pow * cos(h) - rot);
                    RBT.move_voltage(pow * cos(h) - rot);
                    break;
                default:
                break;
            }
        }

        //function that holds the motor position
        void brake() {
            switch(style){
                case QUAD:
                    LF.move_velocity(0);
                    RF.move_velocity(0);
                    RB.move_velocity(0);
                    LB.move_velocity(0);

                    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    break;

                case SEX:
                    LF.move_velocity(0);
                    RF.move_velocity(0);
                    LM.move_velocity(0);
                    RM.move_velocity(0);
                    RB.move_velocity(0);
                    LB.move_velocity(0);

                    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LM.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RM.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    break;

                case OCT:
                    LF.move_velocity(0);
                    LFT.move_velocity(0);
                    RF.move_velocity(0);
                    RFT.move_velocity(0);
                    RB.move_velocity(0);
                    RBT.move_velocity(0);
                    LB.move_velocity(0);
                    LBT.move_velocity(0);

                    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LFT.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RFT.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    LBT.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
                    RBT.set_brake_mode(MOTOR_BRAKE_HOLD);
                    break;

                default:
                break;
            }
        }
    };

    struct intakeStruct{
        static pros::Motor LI, LIT, RI, RIT, TI, TIT;

        void create(int top, pros::motor_gearset_e gearset){
            pros::Motor TI(top, gearset, is_reversed(top));
        }

        void create(int left, int right, pros::motor_gearset_e gearset){
            pros::Motor LI(left, gearset, is_reversed(left));
            pros::Motor RI(right, gearset, is_reversed(right));
        }

        void create(int left, int right, int top, pros::motor_gearset_e gearset){
            pros::Motor LI(left, gearset, is_reversed(left));
            pros::Motor RI(right, gearset, is_reversed(right));
            pros::Motor TI(top, gearset, is_reversed(top));
        }

        void create(int left, int leftT, int right, int rightT, pros::motor_gearset_e gearset){
            pros::Motor LI(left, gearset, is_reversed(left));
            pros::Motor LIT(leftT, gearset, is_reversed(leftT));
            pros::Motor RI(right, gearset, is_reversed(right));
            pros::Motor RIT(rightT, gearset, is_reversed(rightT));
        }

        void create(int left, int leftT, int right, int rightT, int top, pros::motor_gearset_e gearset){
            pros::Motor LI(left, gearset, is_reversed(left));
            pros::Motor LIT(leftT, gearset, is_reversed(leftT));
            pros::Motor RI(right, gearset, is_reversed(right));
            pros::Motor RIT(rightT, gearset, is_reversed(rightT));
            pros::Motor TI(top, gearset, is_reversed(top));
        }

        void create(int left, int leftT, int right, int rightT, int top, int topT pros::motor_gearset_e gearset){
            pros::Motor LI(left, gearset, is_reversed(left));
            pros::Motor LIT(leftT, gearset, is_reversed(leftT));
            pros::Motor RI(right, gearset, is_reversed(right));
            pros::Motor RIT(rightT, gearset, is_reversed(rightT));
            pros::Motor TI(top, gearset, is_reversed(top));
            pros::Motor TIT(topT, gearset, is_reversed(topT));
        }

        void runSides(int power){
            LI.move_voltage(power);
            LIT.move_voltage(power);
            RI.move_voltage(power);
            RIT.move_voltage(power);
        }

        void runTop(int power){
            TI.move_voltage(power);
            TIT.move_voltage(power);
        }

        void runAll(int power){
            runSides(power);
            runTop(power);
        }

        void runAll(int sides, int top){
            runSides(sides);
            runTop(top);
        }

        void hold(){
            LI.move_velocity(0);
            LIT.move_velocity(0);
            RI.move_velocity(0);
            RIT.move_velocity(0);
            TI.move_velocity(0);
            TIT.move_velocity(0);

            LI.set_brake_mode(MOTOR_BRAKE_HOLD);
            LIT.set_brake_mode(MOTOR_BRAKE_HOLD);
            RI.set_brake_mode(MOTOR_BRAKE_HOLD);
            RIT.set_brake_mode(MOTOR_BRAKE_HOLD);
            TI.set_brake_mode(MOTOR_BRAKE_HOLD);
            TIT.set_brake_mode(MOTOR_BRAKE_HOLD);
        }
    };

    struct conveyorStruct{
        static pros::Motor C1, C2, C3, C4, C5, C6;

        void create(int c1, int c2, pros::motor_gearset_e gearset){
            pros::Motor C1(c1, gearset, is_reversed(c1));
            pros::Motor C2(c2, gearset, is_reversed(c2));
        }

        void create(int c1, int c2, int c3, pros::motor_gearset_e gearset){
            pros::Motor C1(c1, gearset, is_reversed(c1));
            pros::Motor C2(c2, gearset, is_reversed(c2));
            pros::Motor C3(c3, gearset, is_reversed(c3));
        }

        void create(int c1, int c2, int c3, int c4, pros::motor_gearset_e gearset){
            pros::Motor C1(c1, gearset, is_reversed(c1));
            pros::Motor C2(c2, gearset, is_reversed(c2));
            pros::Motor C3(c3, gearset, is_reversed(c3));
            pros::Motor C4(c4, gearset, is_reversed(c4));
        }

        void create(int c1, int c2, int c3, int c4, int c5, pros::motor_gearset_e gearset){
            pros::Motor C1(c1, gearset, is_reversed(c1));
            pros::Motor C2(c2, gearset, is_reversed(c2));
            pros::Motor C3(c3, gearset, is_reversed(c3));
            pros::Motor C4(c4, gearset, is_reversed(c4));
            pros::Motor C5(c5, gearset, is_reversed(c5));
        }

        void create(int c1, int c2, int c3, int c4, int c5, int c6, pros::motor_gearset_e gearset){
            pros::Motor C1(c1, gearset, is_reversed(c1));
            pros::Motor C2(c2, gearset, is_reversed(c2));
            pros::Motor C3(c3, gearset, is_reversed(c3));
            pros::Motor C4(c4, gearset, is_reversed(c4));
            pros::Motor C5(c5, gearset, is_reversed(c5));
            pros::Motor C6(c6, gearset, is_reversed(c6));
        }

        void run(int power){
            C1.move_voltage(power);
            C2.move_voltage(power);
            C3.move_voltage(power);
            C4.move_voltage(power);
            C5.move_voltage(power);
            C6.move_voltage(power);
        }

        void hold(){
            C1.move_velocity(0);
            C2.move_velocity(0);
            C3.move_velocity(0);
            C4.move_velocity(0);
            C5.move_velocity(0);
            C6.move_velocity(0);

            C1.set_brake_mode(MOTOR_BRAKE_HOLD);
            C2.set_brake_mode(MOTOR_BRAKE_HOLD);
            C3.set_brake_mode(MOTOR_BRAKE_HOLD);
            C4.set_brake_mode(MOTOR_BRAKE_HOLD);
            C5.set_brake_mode(MOTOR_BRAKE_HOLD);
            C6.set_brake_mode(MOTOR_BRAKE_HOLD);
        }
    };
};

extern robot::conveyorStruct conveyors;
extern robot::intakeStruct intakes;
extern robot::baseStruct base;

namespace motion{

    struct pidStruct{
        double kP = 0;
        double kD = 0;
        double dT = 0;
        double kF = 0;
        int minDt = 10;

        double error = 0;
        double derivative = 0;
        double lastError = 0;
        double lastTime = 0;
        double output = 0;

        void pidInit(double kP, double kD, double kF, int minDt = 10){
            this->kP = kP;
            this->kD = kD;
            this->kF = kF;
            this->minDt = minDt;
            this->lastTime = pros::millis();
        }

        double pidCalculate(double target, double current, int maxPow = 10000, int minPow = 3000) {
            this->error = target - current;

            double dT = pros::millis() - lastTime;

        if (dT < this->dT){
            return this->output;
        }

        this->derivative = (this->error - this->lastError) / this->dT;

        this->output = (this->error * this->kP) + (this->derivative * this->kD) + (this->kF * this->output);

        if(fabs(this->output) > maxPow){
            this->output = sgn(this->output) * maxPow;
        }

        else if(fabs(this->output) < minPow){
            this->output = sgn(this->output) * minPow;
        }

        this->lastError = this->error;
        this->lastTime = pros::millis();

        return this->output;
      }
    };

    struct odomStruct{
        static double wheelSize, distance_LR, distance_B;

        static pros::ADIEncoder LeftTracker, RightTracker, BackTracker;

        static double x, y, a;

        static double radiusR, radiusB, h, h2;
        static double theta, beta, alpha;
        static double Xx, Xy, Yx, Yy;
        static double lastleft, lastright, lastback, Right, Left, Back, newleft, newright, newback;

        static void odomInit(pros::ADIEncoder left, pros::ADIEncoder right, pros::ADIEncoder back, double LR = 0, double B = 0, double WS = 2.75){
            pros::ADIEncoder LeftTracker(left);
            pros::ADIEncoder RightTracker(right);
            pros::ADIEncoder BackTracker(back);

            wheelSize = WS;
            distance_LR = LR;
            distance_B = B;
        }

        static void reset(){
            LeftTracker.reset(); RightTracker.reset(); BackTracker.reset();
            newleft = 0; newright = 0; newback = 0;
            Right = 0; Left = 0; Back = 0;
            lastleft = 0; lastright = 0; lastback = 0;
        }

        static void update(void*){
            while(true){
                //amount encoders moved (radians)
                newleft = LeftTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the left encoder moved
            	newright = RightTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the right encoder moved
                newback = BackTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the rear encoder moved
                Right = newright - lastright;//the delta of the right encoder
                Left = newleft - lastleft;//the delta of the left encoder
                Back = newback - lastback;//the delta of the rear encoder

                //update last values
            	lastright = newright;
            	lastleft = newleft;
            	lastback = newback;
            	theta = (Left - Right) / distance_LR;//angle of the bot in radians

                //if robot turned in any direction
            	if (theta != 0)
                {
                radiusR = Right / theta;
                beta = theta / 2.0;
              	h = (radiusR + distance_LR / 2) * 2 * sin(beta);
              	radiusB = Back / theta;
              	h2 = (radiusB + distance_B) * 2 * sin(beta);
            	}

                //if robot moved straight or didn't move
            	else
                {
                    h = Right;
                	h2 = Back;
                	beta = 0;
                }
            	alpha = a + beta;

                //update global x, y and angle
            	Xx = h2 * cos(alpha);
            	Xy = h2 * -sin(alpha);
            	Yx = h * sin(alpha);
            	Yy = h * cos(alpha);
            	x += Yx + Xx;
            	y += Yy + Xy;
                a += theta;

                pros::delay(5);
            }
        }
    };
    extern motion::pidStruct drivingPID;
    extern motion::pidStruct turningPID;
    extern motion::odomStruct odom;

    extern bool init;

    void turnToPoint(double tx, double ty) {
      double pow = turningPID.pidCalculate(atan(tx / ty), odom.a);
      base.move(pow, -pow);
    }

    double turnToPointHolo(double tx, double ty){
        return turningPID.pidCalculate(atan(tx / ty), odom.a);
    }

    double driveToPoint(double sx, double sy, double tx, double ty){
        double currDist = sqrt(pow((tx - odom.x), 2) + pow(ty - odom.y, 2));
        double totalDist = sqrt(pow((tx - sx), 2) + pow(ty - sy, 2));
        return drivingPID.pidCalculate(totalDist, currDist);
    }

    //function that moves a tank base to a coordinate
    void autoDrive(double x, double y) {
        if(!init){
            turningPID.pidInit(0, 0, 0);
            drivingPID.pidInit(0, 0, 0);
            init = true;
        }

        int rotPow, pwr;
        double difX, difY;
        double sx = odom.x;
        double sy = odom.y;

        turnToPoint(x, y);
        do {

            difX = x - odom.x;
            difY = y - odom.y;
            pwr = driveToPoint(sx, sy, x, y);
            rotPow = turnToPointHolo(x, y);

            base.move(pwr + rotPow, pwr - rotPow);
            pros::delay(5);
        }while(fabs(difX <= 0.5) && fabs(difY <= 0.5));
        base.brake();//holds the motor positions
    }

    //function that moves a holonomic base to a coordinate
    void autoDrive(double x, double y, double a) {
        if(!init){
            turningPID.pidInit(0, 0, 0);
            drivingPID.pidInit(0, 0, 0);
            init = true;
        }
        double difX, difY, heading, pow, rot;
        double sx = odom.x;
        double sy = odom.y;

        do {
            difX = x - odom.x;
            difY = y - odom.y;
            heading = angleWrap(angleWrap(atan2(difX, difY)) - odom.a);
            pow = driveToPoint(sx, sy, x, y);
            rot = turnToPointHolo(x, y);


            base.move(heading, pow, rot);
            pros::delay(5);
        }while(fabs(difX <= 0.5) && fabs(difY <= 0.5) && fabs(radToDeg(difA) <= ));
        base.brake();//holds the motor positions
    }
};

namespace driverControl{
    extern void intakeControl(void*);
    extern void driveBase(void*);
}

#endif
