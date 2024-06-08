#include <iostream>
#include "menu/Menu.h" 
using namespace std;


int main() {
    Menu* menu;
    menu = new Menu();
    menu->menuRunner();
    return 0; 
}
