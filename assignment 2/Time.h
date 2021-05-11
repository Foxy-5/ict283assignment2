#ifndef TIME_H
#define TIME_H
#include <iostream>

using namespace std;
     /**
	 * @class  Time
	 * @brief  store information regarding time object
	 *
	 *
	 *
	 *
	 * @author Seow Wei Cheng
	 * @version 01
	 * @date 6/2/2021
	 *
	 *
	 *
	 * @todo
	 *
	 * @bug
	 */
class Time
{
    public:
                /**
                * @brief create a time object
                *
                * default constructor
                *
                * @return void
                */
        Time();
                /**
                * @brief create a time object
                *
                * Construct a date object with int h and int m
                *
                * @return void
                */
        Time(int h, int m);
                /**
                * @brief Set hour
                *
                * Assign hour with int h
                *
                * @return void
                */
        void SetHour(int h);
                /**
                * @brief set minute
                *
                * Assign minute with int m
                *
                * @return void
                */
        void SetMinute(int m);
                /**
                * @brief return hour
                *
                * function that return the hour value
                *
                * @return int
                */
        int GetHour() const;
                /**
                * @brief return minute
                *
                * function that return the minute value
                *
                * @return int
                */
        int GetMinute() const;
    private:
            ///stores hour member
        int hour;
            ///stores minute member
        int minute;
};
istream & operator>>(istream& input, Time& t);

ostream & operator<<(ostream& os, const Time& t);
#endif // TIME_H
