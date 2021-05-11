#ifndef MENU_H
#define MENU_H

#include "Bst.h"
#include "Time.h"
#include "date.h"

#include <string>
#include <map>

using namespace std;
/**
* @struct WindLogType
* struct that contains the WindLogType data of date, Time
* speed, solar Radiation and air temperature
*/
typedef struct {
    date d;
    Time t;
    float speed;
    float solarRad;
    float aAirTemp;
} WindLogType;
//=====================================================================================================
    /**
	 * @class  Menu
	 * @brief  Store all the options and menu information
	 *
	 *
	 *
	 *
	 * @author Seow Wei Cheng
	 * @version 01
	 * @date 14/3/2021
	 *
	 * @version 02
	 * @date 18/3/2021
     * Added option 2 into menu class
     *
     * @version 03
     * @date 22/3/2021
     * Added the bonus option 6
	 * @todo
	 *
	 * @bug
	 */
class Menu
{
    public:
            /**
            * @brief create a Menu object
            *
            * default constructor
            *
            */
        Menu();
            /**
            * @brief Destructor
            *
            * default destructor
            *
            */
        virtual ~Menu();
            /**
            * @brief Does the file reading and storing of data
            *
            * This function reads in the file and store all the required data
            * into the data structures
            *
            * @param string
            * @return void
            */
        void readFile(string);
            /**
            * @brief read the metIndex.txt file
            *
            * Read in the metIndex.txt file and passes the file index into the readfile function
            *
            * @return void
            */
        void readMetIndex();
            /**
            * @brief print menu
            *
            * function that prints out all the menu
            *
            * @return void
            */
        void printMenu();
            /**
            * @brief Option 1
            *
            * Option 1 of menu that prints out the average wind speed and
            * average ambient air temperature for a specified month and year.
            *
            * @param Bst<date>, multimap<date, WindLogType>, multimap<date, WindLogType>::iterator
            * @return void
            */
        void option1(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr);
            /**
            * @brief Option 2
            *
            * Option 2 of menu that prints out Average wind speed and average ambient air temperature
            * for each month of a specified year.
            *
            * @param Bst<date>, multimap<date, WindLogType>, multimap<date, WindLogType>::iterator
            * @return void
            */
        void option2(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr);
            /**
            * @brief Option 3
            *
            * Option 3 of menu that prints out the total solar radiation in kWh/m2 for each month of a specified year.
            *
            * @param Bst<date>, multimap<date, WindLogType>, multimap<date, WindLogType>::iterator
            * @return void
            */
        void option3(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr);
            /**
            * @brief Option 4
            *
            * Option 4 of menu that prints out the Average wind speed (km/h),
            * average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year.
            *
            * @param Bst<date>, multimap<date, WindLogType>, multimap<date, WindLogType>::iterator
            * @return void
            */
        void option4(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr);
            /**
            * @brief Option 5
            *
            * Option 5 of menu that prints out the average wind speed and
            * average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year
            * to the output file.
            *
            * @param Bst<date>, multimap<date, WindLogType>, multimap<date, WindLogType>::iterator
            * @return void
            */
        void option5(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr);
            /**
            * @brief Option 6
            *
            * exit the program
            *
            * @return void
            */
        void option6();
            /**
            * @brief menuOption
            *
            * Ask the user for option input
            *
            * @return void
            */
        void menuOption();
    private:
            ///Bst that contains all the date
        Bst<date> m_dateTree;
            ///multimap that stores date as keys and WindLogType as the data
        multimap<date, WindLogType> m_dataMap;
            ///iterator that is used for m_dataMap
        multimap<date, WindLogType>::iterator m_itr;
};

#endif // MENU_H
