#include <iostream>
#include "menu/Menu.h" 
using namespace std;


int main() {
    Menu* menu;
    menu = new Menu();
    menu->menu_runner();
    return 0; 
}
