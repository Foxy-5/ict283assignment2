#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

     /**
	 * @class  date
	 * @brief  store information regarding date object
	 *
	 *
	 *
	 *
	 * @author Seow Wei Cheng
	 * @version 01
	 * @date 31/1/2021
	 *
	 * @version 02
	 * @date 15/3/2021
	 *
	 * @todo
	 *
	 * @bug
	 */
using namespace std;

class date
{
    public:
                /**
                * @brief create a date object
                *
                * Construct a default date object
                *
                * @return
                */
        date();
                /**
                * @brief create a date object
                *
                * Construct a date object with int d, string m and int y
                *
                * @return void
                */
        date(int d, int m, int y);

                /**
                * @brief set day
                *
                * function that sets day variable
                *
                * @return void
                */
        void setDay(int d);
                /**
                * @brief return day
                *
                * function that returns day variable
                *
                * @return int
                */
        int getDay() const;
                /**
                * @brief set month
                *
                * function that sets month variable
                *
                * @return void
                */
        void setMonth(int m);
                /**
                * @brief get month
                *
                * function that returns month variable
                *
                * @return string
                */
        int getMonth() const;
                /**
                * @brief set year
                *
                * function that sets year variable
                *
                * @return void
                */
        void setYear(int y);
                /**
                * @brief get year
                *
                * function that returns year variable
                *
                * @return int
                */
        int getYear() const;
                /**
                * @brief set date object
                *
                * function that sets date object with int d, string m and int y
                *
                * @return void
                */
        void SetDate(int d, int m, int y);
                /**
                * @brief convert month
                *
                * function that converts month from numbers to word
                *
                * @return string
                */
        string monthConvert(int m);
                /**
                * @brief print date
                *
                * function that prints the full date to screen
                * @return void
                */
        void PrintDate();
                /**
                * @brief overloaded == operator
                *
                * allows the use of == operator
                * @return bool
                */
        bool operator == (const date& RhsObj) const;
                /**
                * @brief overloaded < operator
                *
                * allows the use of < operator
                * @return bool
                */
        bool operator < (const date& RhsObj) const;
                /**
                * @brief overloaded > operator
                *
                * allows the use of > operator
                * @return bool
                */
        bool operator > (const date& RhsObj) const;
                /**
                * @brief overloaded != operator
                *
                * allows the use of != operator
                * @return bool
                */
        bool operator != (const date& RhsObj) const;
                /**
                * @brief overloaded >= operator
                *
                * allows the use of >= operator
                * @return bool
                */
        bool operator >= (const date& RhsObj) const;
                /**
                * @brief overloaded <= operator
                *
                * allows the use of <= operator
                * @return bool
                */
        bool operator <= (const date& RhsObj) const;
    private:
            ///day integer
        int day;
            ///month string
        int month;
            ///year integer
        int year;
};

istream & operator>>(istream& input, date& d);

ostream & operator<<(ostream& os, const date& d);
#endif // DATE_H
