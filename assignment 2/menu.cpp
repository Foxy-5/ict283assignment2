#include "menu.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}
void Menu::readMetIndex()
{
    ifstream infile;
    string filename = "data/met_index.txt";
    infile.open(filename);
    if(infile.is_open())
    {
        while(!infile.eof())
        {
            string datafile;
            getline(infile,datafile,'\n');
            cout << "Now opening: " << datafile << "\n";
            datafile = "data/"+datafile; //append data/ to the front so the program can find where the file is
            readFile(datafile);
        }
    }
}
void Menu::readFile(string DataFile)
{
    ifstream infile;
    infile.open(DataFile);
    infile.ignore(500,'\n');

    if(infile.is_open())
    {
        while(!infile.eof())
        {
            date tempDate;
            Time tempTime;
            float tempSpeed,tempSolarRad,TempAAirTemp;
            string temp;
            if(!isdigit(infile.peek())) //check to see if the next value is empty, if so skip
            {
                infile.ignore(500,'\n');    //go to next line
            }
            else
            {
                infile >> tempDate >> tempTime; // input into date and time
                for (int i = 0; i < 10; i++) //skip 10 columns
                {
                    getline(infile,temp,',');
                }
                if(temp != "N/A") //check for N/A
                {
                    tempSpeed = stof(temp);
                }
                else
                {
                    tempSpeed = -1.0; //sentinel value to skip the row
                }
                getline(infile,temp,',');
                if(temp !="N/A")
                {
                    tempSolarRad = stof(temp);
                }
                else
                {
                    tempSolarRad = -1.0;
                }
                for (int i = 0; i <5; i++) //skip 5 columns
                {
                    getline(infile,temp,',');
                }
                getline(infile,temp);
                if(temp != "N/A")
                {
                    TempAAirTemp = stof(temp);
                }
                else
                {
                    TempAAirTemp = -1.0;
                }

                if(TempAAirTemp == -1.0 || tempSolarRad == -1.0 || tempSpeed == -1.0) //if any of the 3 values are
                {
                    //-1.0 it will skip that line
                    infile.ignore(500,'\n');                                          //and continue the next loop
                    continue;
                }
                WindLogType TempWindLog;    //creating a windlog to store the values
                TempWindLog.d = tempDate;
                TempWindLog.t = tempTime;
                TempWindLog.speed = tempSpeed;
                TempWindLog.solarRad = tempSolarRad;
                TempWindLog.aAirTemp = TempAAirTemp;

                m_dateTree.Insert(tempDate); //insert the date object into the Bst
                m_dataMap.insert(pair<date, WindLogType> (tempDate, TempWindLog)); //insert the date and windlog into the map
            }
        }
    }
    infile.close();
}

void Menu::printMenu()
{
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Please select a option 1 - 5\n";
    cout << "1. The average wind speed and average ambient air temperature for a specified month and year. (print on screen only)\n";
    cout << "2. Average wind speed and average ambient air temperature for each month of a specified year. (print on screen only)\n";
    cout << "3. Total solar radiation in kWh/m2 for each month of a specified year. (print on screen only)\n";
    cout << "4. Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2\n"
         << "   for each month of a specified year. (write to a file called WindTempSolar.csv)\n";
    cout << "5. The highest solar radiation for the specified date. (print on screen only)\n";
    cout << "6. exit the program.\n";
}
void Menu::menuOption()
{
    cout << "Please enter (1-6): ";
    int option = 0;
    cin >> option;
    while(option < 1 || option > 6 || cin.fail()) //checking for 1 to 6 input
    {
        cout << "Invalid option please try again\n";
        cin.clear();
        cin.ignore(255,'\n');
        cin >> option;
    }
    if(option == 1)
    {
        option1(m_dateTree,m_dataMap,m_itr);
    }
    else if(option == 2)
    {
        option2(m_dateTree,m_dataMap,m_itr);
    }
    else if(option == 3)
    {
        option3(m_dateTree,m_dataMap,m_itr);
    }
    else if(option == 4)
    {
        option4(m_dateTree,m_dataMap,m_itr);
    }
    else if(option == 5)
    {
        option5(m_dateTree,m_dataMap,m_itr);
    }
    else
    {
        option6();
    }
}
void Menu::option1(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr)
{
    float TotalSpeed = 0.0, AverageSpeed = 0.0;
    float TotalTemperature = 0.0, AverageTemperature = 0.0;
    int TempMonth, TempYear, count = 0;
    date TempDate;
    pair<multimap<date, WindLogType>::iterator, multimap<date, WindLogType>::iterator> tempitr; //pair of iterators used for checking through the map
    cout << "Please Enter the month (In Integer!): ";
    cin >> TempMonth;
    cout << "Please Enter the year: ";
    cin >> TempYear;
    if(((TempYear % 4 == 0) && (TempYear % 100 !=0)) || (TempYear % 400 == 0)) //leap year checker, the loops inside
    {
        //are basically the same beside the number
        if(TempMonth == 2) //leap year feb                                     //of days in each month
        {
            for(int i = 1; i<=29; i++)
            {
                TempDate.SetDate(i,TempMonth,TempYear);
                if(m_dateTree.Search(TempDate) == true) //checking if date is found in the tree
                {
                    tempitr = m_dataMap.equal_range(TempDate);  //use the pair of iterators assign it with the date
                    for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++) //use the iterator and loop it through the first and last iterator of the pair
                    {
                        TotalSpeed = TotalSpeed + m_itr->second.speed; //adding up all the speed
                        TotalTemperature = TotalTemperature + m_itr->second.aAirTemp; //adding up all the temperature
                        count++; //add to count
                    }
                }
            }
        }
    }
    else
    {
        switch(TempMonth)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            for(int i = 1; i<=31; i++)
            {
                TempDate.SetDate(i,TempMonth,TempYear);
                if(m_dateTree.Search(TempDate) == true)
                {
                    tempitr = m_dataMap.equal_range(TempDate);
                    for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                    {
                        TotalSpeed = TotalSpeed + m_itr->second.speed;
                        TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                        count++;
                    }
                }
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            for(int i = 1; i<=30; i++)
            {
                TempDate.SetDate(i,TempMonth,TempYear);
                if(m_dateTree.Search(TempDate) == true)
                {
                    tempitr = m_dataMap.equal_range(TempDate);
                    for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                    {
                        TotalSpeed = TotalSpeed + m_itr->second.speed;
                        TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                        count++;
                    }
                }
            }
            break;
        case 2:
            for(int i = 1; i<=28; i++)
            {
                TempDate.SetDate(i,TempMonth,TempYear);
                if(m_dateTree.Search(TempDate) == true)
                {
                    tempitr = m_dataMap.equal_range(TempDate);
                    for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                    {
                        TotalSpeed = TotalSpeed + m_itr->second.speed;
                        TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                        count++;
                    }
                }
            }
            break;
        }
    }
    AverageSpeed = (TotalSpeed/count) * 3.6; //get the converted speed
    AverageTemperature = (TotalTemperature/count); //get the average temperature
    if(count != 0) //if there is date stored print the following
    {
        cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
             << fixed << setprecision(1) << AverageSpeed << "km/h, "
             << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
    }
    else //print the following if no data
    {
        cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
    }

}

void Menu::option2(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr)
{
    float TotalSpeed = 0.0, AverageSpeed = 0.0;
    float TotalTemperature = 0.0, AverageTemperature = 0.0;
    int TempMonth, TempYear, count = 0;
    date TempDate;
    pair<multimap<date, WindLogType>::iterator, multimap<date, WindLogType>::iterator> tempitr;
    cout << "Please Enter the year: ";
    cin >> TempYear;
    if(((TempYear % 4 == 0) && (TempYear % 100 !=0)) || (TempYear % 400 == 0)) //leap year checker
    {
        for(TempMonth=1; TempMonth<=12; TempMonth++) //loop through all the months
        {
            if(TempMonth == 2) //leap year feb
            {
                for(int i = 1; i<=29; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true) //check if the date is in the Bst
                    {
                        tempitr = m_dataMap.equal_range(TempDate); //assign the pair of iterators to the value of date
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++) //loop through the pair of iterators
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed; //add up the speed
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp; // add up the temperature
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6; //convert the speed
                AverageTemperature = (TotalTemperature/count); //get the average temperature
                if(count != 0) //if count not 0 print out the following
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else //if count is 0 print out the following
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                //reset all the values back to 0.0 as it will be reused for the next month
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
            }
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6;
                AverageTemperature = (TotalTemperature/count);
                if(count != 0)
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6;
                AverageTemperature = (TotalTemperature/count);
                if(count != 0)
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            }
        }
    }
    else
    {
        for(int TempMonth=1; TempMonth<=12; TempMonth++)
        {
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6;
                AverageTemperature = (TotalTemperature/count);
                if(count != 0)
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6;
                AverageTemperature = (TotalTemperature/count);
                if(count != 0)
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 2:
                for(int i = 1; i<=28; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            count++;
                        }
                    }
                }
                AverageSpeed = (TotalSpeed/count) * 3.6;
                AverageTemperature = (TotalTemperature/count);
                if(count != 0)
                {
                    cout << TempDate.monthConvert(TempMonth) << " " << TempYear << ": "
                         << fixed << setprecision(1) << AverageSpeed << "km/h, "
                         << fixed << setprecision(1) << AverageTemperature << " degrees C\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSpeed = 0.0;
                AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            }
        }
    }
}
void Menu::option3(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr)
{
    float TotalSolarRad = 0.0;
    float ConvertedSolarRad = 0.0;
    int count = 0;
    int TempMonth, TempYear;
    date TempDate;
    pair<multimap<date, WindLogType>::iterator, multimap<date, WindLogType>::iterator> tempitr;

    cout << "Please enter the year: ";
    cin >> TempYear;
    if(((TempYear % 4 == 0) && (TempYear % 100 !=0)) || (TempYear % 400 == 0)) //leap year checker
    {
        for(TempMonth=1; TempMonth<=12; TempMonth++) //loop through all the month
        {
            if(TempMonth == 2) //leap year feb
            {
                for(int i = 1; i<=29; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true) //search the Bst for the date
                    {
                        tempitr = m_dataMap.equal_range(TempDate); //set the pair of iterator to the date
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++) //loop through the pair of iterator
                        {
                            if(m_itr->second.solarRad >= 100) //only store solar radiation >= 100
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad; //add up all the solar radiation
                                count++;
                            }
                        }
                    }
                }
                if(count != 0) //if count not 0 do the following
                {
                    ConvertedSolarRad = TotalSolarRad / 6000; //convert the solar radiation
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                }
                else //if no data do the following
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                //reset the values for the next loop
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
            }
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                                count++;
                            }
                        }
                    }
                }
                if(count != 0)
                {
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                                count++;
                            }
                        }
                    }
                }
                if(count != 0)
                {
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
                break;
            }
        }
    }
    else
    {
        for(int TempMonth=1; TempMonth<=12; TempMonth++)
        {
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                                count++;
                            }
                        }
                    }
                }
                if(count != 0)
                {
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                    //cout << "Total number of values: " << count << endl;
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                                count++;
                            }
                        }
                    }
                }
                if(count != 0)
                {
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                    //cout << "Total number of values: " << count << endl;
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
                break;
            case 2:
                for(int i = 1; i<=28; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                                count++;
                            }
                        }
                    }
                }
                if(count != 0)
                {
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    cout << TempDate.monthConvert(TempMonth) << ": " << fixed << setprecision(1)
                         << ConvertedSolarRad << " kWh/m^2\n";
                    //cout << "Total number of values: " << count << endl;
                }
                else
                {
                    cout << TempDate.monthConvert(TempMonth) << ": No Data\n";
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                count = 0;
                break;
            }
        }
    }
}

void Menu::option4(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr)
{
    ofstream outfile;
    outfile.open("WindTempSolar.csv"); //file that stores the output of the option
    float TotalSolarRad = 0.0;
    float ConvertedSolarRad = 0.0;
    float TotalSpeed = 0.0, AverageSpeed = 0.0;
    float TotalTemperature = 0.0, AverageTemperature = 0.0;
    int count = 0, noOfemtpy = 0;
    int TempMonth, TempYear = 0;
    date TempDate;
    pair<multimap<date, WindLogType>::iterator, multimap<date, WindLogType>::iterator> tempitr;
    cout << "Please enter the year: ";
    cin >> TempYear;
    outfile << "Year: "<< TempYear << endl;
    if(((TempYear % 4 == 0) && (TempYear % 100 !=0)) || (TempYear % 400 == 0)) //leap year checker
    {
        for(TempMonth=1; TempMonth<=12; TempMonth++) //loop through the all the month
        {
            if(TempMonth == 2) //leap year feb
            {
                for(int i = 1; i<=29; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true) //check the Bst for date
                    {
                        tempitr = m_dataMap.equal_range(TempDate); //assign pair of iterator to the date
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++) // loop through the pair of iterator
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed; //add up all the speed
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp; //add up all the temperature
                            if(m_itr->second.solarRad >= 100) //check if solar radiation is >=100
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad; // add up all the solarRadiation
                            }
                            count++;
                        }
                    }
                }
                if(count != 0) //if count not 0 do the following
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6; //convert the speed
                    AverageTemperature = (TotalTemperature/count); //get the average temperature
                    ConvertedSolarRad = TotalSolarRad / 6000; //convert the solar radiation
                    //store the data into the output file
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else //if count is 0 do the following
                {
                    //store no data into the output file
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++; //check the number of empty months
                }
                //resets the values for the next loop
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
            }
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                            }
                            count++;
                        }
                    }
                }
                if(count != 0)
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6;
                    AverageTemperature = (TotalTemperature/count);
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else
                {
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++;
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                            }
                            count++;
                        }
                    }
                }
                if(count != 0)
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6;
                    AverageTemperature = (TotalTemperature/count);
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else
                {
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++;
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            }
        }
    }
    else
    {
        for(int TempMonth=1; TempMonth<=12; TempMonth++)
        {
            switch(TempMonth)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                for(int i = 1; i<=31; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                            }
                            count++;
                        }
                    }
                }
                if(count != 0)
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6;
                    AverageTemperature = (TotalTemperature/count);
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else
                {
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++;
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                for(int i = 1; i<=30; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                            }
                            count++;
                        }
                    }
                }
                if(count != 0)
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6;
                    AverageTemperature = (TotalTemperature/count);
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else
                {
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++;
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            case 2:
                for(int i = 1; i<=28; i++)
                {
                    TempDate.SetDate(i,TempMonth,TempYear);
                    if(m_dateTree.Search(TempDate) == true)
                    {
                        tempitr = m_dataMap.equal_range(TempDate);
                        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
                        {
                            TotalSpeed = TotalSpeed + m_itr->second.speed;
                            TotalTemperature = TotalTemperature + m_itr->second.aAirTemp;
                            if(m_itr->second.solarRad >= 100)
                            {
                                TotalSolarRad = TotalSolarRad + m_itr->second.solarRad;
                            }
                            count++;
                        }
                    }
                }
                if(count != 0)
                {
                    AverageSpeed = (TotalSpeed/count) * 3.6;
                    AverageTemperature = (TotalTemperature/count);
                    ConvertedSolarRad = TotalSolarRad / 6000;
                    outfile << fixed << setprecision(1);
                    outfile << TempDate.monthConvert(TempMonth) << "," << AverageSpeed << ","
                            << AverageTemperature << "," << ConvertedSolarRad << endl;
                }
                else
                {
                    outfile << TempDate.monthConvert(TempMonth) << ": No Data\n";
                    noOfemtpy++;
                }
                TotalSolarRad = 0.0;
                ConvertedSolarRad = 0.0;
                TotalSpeed = 0.0, AverageSpeed = 0.0;
                TotalTemperature = 0.0;
                AverageTemperature = 0.0;
                count = 0;
                break;
            }
        }
    }
    outfile.close();
    if(noOfemtpy == 12) //if the whole year have no data do the following
    {
        ofstream outfile;
        outfile.open("WindTempSolar.csv");
        outfile << TempYear << endl;
        outfile << "NO DATA\n";
        outfile.close();
    }
    cout << "Data have been written to WindTempSolar.csv\n";
}

void Menu::option5(Bst<date> m_dateTree,multimap<date, WindLogType> m_dataMap,multimap<date, WindLogType>::iterator m_itr)
{
    //declare temp variable
    int tempDay = 0, tempMonth = 0, tempYear = 0;
    string tempInput;
    string delimiter = "/";
    size_t pos = 0;
    string token;
    date tempDate;
    Time tempTime[100];
    int count = 0;
    int counter = 1;
    pair<multimap<date, WindLogType>::iterator, multimap<date, WindLogType>::iterator> tempitr;
    cout << "Please enter the date in d/m/yyyy format: ";
    cin >> tempInput;
    //while loop to break the input into 3 string (tempDay/tempMonth/tempYear)
    while((pos = tempInput.find(delimiter)) != string::npos)
    {
        token = tempInput.substr(0,pos);
        //get the day string up to /
        if(counter == 1)
        {
            tempDay = stoi(token);
            tempInput.erase(0,pos + delimiter.length());
            counter++;
        }
        //get the month string up to /
        else if(counter == 2)
        {
            tempMonth = stoi(token);
            tempInput.erase(0,pos + delimiter.length());
            counter++;
        }
    }
    //get the year string
    tempYear = stoi(tempInput);
    //cout << tempDay << "," << tempMonth << "," << tempYear << endl;
    //set the date using tempDay, tempMonth, tempYear
    tempDate.SetDate(tempDay,tempMonth,tempYear);
    //find the date in the date tree
    if(m_dateTree.Search(tempDate)== true)
    {
        //print out the date
        cout << "Date: " << tempDate << endl;
        float HighSolarRad = 0;
        int tempMin, tempHour;
        //set the pair of iterator to the tempdate
        tempitr = m_dataMap.equal_range(tempDate);
        //loop through the pair of iterator
        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
        {
            //check if the next solar radiation is larger then before
            if(m_itr->second.solarRad > HighSolarRad)
            {
                //set the solar radiation if it is higher
                HighSolarRad = m_itr->second.solarRad;
            }
            //cout << m_itr->second.t << endl;
        }
        //loop through the pair of iterator
        for(m_itr = tempitr.first; m_itr != tempitr.second; m_itr++)
        {
            //check if solar radiation is the highest
            if(m_itr->second.solarRad == HighSolarRad)
            {
                //store the time for the highest solar radiation
                tempMin = m_itr->second.t.GetMinute();
                tempHour = m_itr->second.t.GetHour();
                //store into the tempTime array use if there are multiple time with the highest solar radiation
                tempTime[count].SetHour(tempHour);
                tempTime[count].SetMinute(tempMin);
                count++;
            }
        }
        //print out the needed data to the screen
        //print out the highest solar radiation
        cout << "High solar radiation for the day: " << HighSolarRad << endl << endl;
        //print out all the time that has the highest solar radiation
        cout << "Time:\n";
        for(int i=0; i<count; i++)
        {
            cout << tempTime[i] << endl;
        }
    }
    else
        //print no data if no data
        cout << "No data.\n";
}

void Menu::option6()
{
    exit(0);
}
