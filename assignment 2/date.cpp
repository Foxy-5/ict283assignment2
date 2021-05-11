#include "date.h"

date::date()
{
    day = 1;
    month = 1;
    year = 2000;
}

date::date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void date::setDay(int d)
{
    day = d;
}

int date::getDay() const
{
    return day;
}

void date::setMonth(int m)
{
    month = m;
}

int date::getMonth() const
{
    return month;
}

void date::setYear(int y)
{
    year = y;
}

int date::getYear() const
{
    return year;
}

void date::SetDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

string date::monthConvert(int m)
{
    string MonthArray[] = {"January", "February", "March", "April", "May", "June"
                           , "July", "August", "September", "October", "November", "December"
                          };

    return MonthArray[m-1];
}

void date::PrintDate()
{
    cout << getDay() << "/" << getMonth() << "/" << getYear() << endl;
}
istream & operator>>(istream& input, date& d)
{
    string tempD, tempM, tempY;
    getline(input,tempD,'/');
    getline(input,tempM,'/');
    getline(input,tempY,' ');
    int day = stoi(tempD);
    int month = stoi(tempM);
    int year = stoi(tempY);
    d.SetDate(day,month,year);
    return input;
}

ostream & operator<<(ostream& os, const date& d)
{
    os << d.getDay() << "/" << d.getMonth() << "/" << d.getYear() << " ";
    return os;
}

bool date::operator==(const date& RhsObj) const
{
    return(year == RhsObj.year && month == RhsObj.month && day == RhsObj.day);
}

bool date::operator<(const date& RhsObj) const
{
    if (year < RhsObj.year)
        return true;
    else if (year == RhsObj.year)
    {
        if (month < RhsObj.month)
        {
            return true;
        }
        else if (month == RhsObj.month)
        {
            if(day < RhsObj.day)
                return true;
        }
    }
    return false;
}

bool date::operator>(const date& RhsObj) const
{
    if(year > RhsObj.year)
        return true;
    else if(year == RhsObj.year)
    {
        if(month > RhsObj.month)
        {
            return true;
        }
        else if(month == RhsObj.month)
        {
            if(day > RhsObj.day)
            {
                return true;
            }
        }
    }
    return false;
}

bool date::operator!=(const date& RhsObj) const
{
    return(!(*this == RhsObj));
}

bool date::operator<=(const date& RhsObj) const
{
    return(*this < RhsObj || *this == RhsObj);
}

bool date::operator>=(const date& RhsObj) const
{
    return(*this > RhsObj || *this == RhsObj);
}
