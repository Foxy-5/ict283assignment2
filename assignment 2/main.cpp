#include "date.h"
#include "Time.h"
#include "menu.h"
#include "Bst.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    Menu menu;
    menu.readMetIndex();
    menu.printMenu();
    menu.menuOption();

    system("pause");
    return 0;
}
