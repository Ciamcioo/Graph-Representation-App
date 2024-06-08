#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

/**
 * Function waits for button press of a user 
 */
void waitForButtonPress() {
    std::cout << "Press any key to continue...\n";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Function cleras terminal based on the user operating system
 */
void clearTerminal() {
   #ifdef _WIN32
        system("cls");
   #else
        system("clear");
   #endif
}

/**
 * Function runs application until the user decides to close the appliaction
 */
void Menu::menuRunner() {
   bool shouldRun = true;
   do {
      displayMainMenu();
      shouldRun = mainMenuController(); 
   } while (shouldRun);
}

/**
 * Function displays the options of the main menu
 */
void Menu::displayMainMenu() const {
    clearTerminal(); 
    std::cout << "\nGraph Represenatation Menu\n";
    std::cout << "1. Find minimal spanning tree in graph\n";
    std::cout << "2. Find the shorthest path from source vertex in the graph\n";
    std::cout << "3. Exit the app\n";
}

/**
 * Function controls the flow of the application based on the user input. Function returns true in every case 
 * beside the third case. When third case is inserted application return false.
 */
bool Menu::mainMenuController() const {
    int userInput; 
    bool isValid = true ;
    do {
        std::cout << "Enter number related to action: ";
        std::cin >> userInput;
        switch (userInput) {
            case 1:{ 
               displayMSTMenu();
               mstMenuController();
               break;
            }
            case 2:{
               displaySPMenu();
               spMenuController();
               break; 
            }
            case 3: {
                return false;
            }
            default: {
                std::cout << "Invalid input" << std::endl;
                isValid = false;
                break;
             }
        }
    }while(!isValid);
    return true;
}

/**
 * Function displays the minimal spanning tree menu with it's options.
 */
void Menu::displayMSTMenu() const {
    clearTerminal();
    std::cout << "\nFind minimal spanning tree submenu\n";
    std::cout << "1. Read graph from file\n";
    std::cout << "2. Generate graph\n";
    std::cout << "3. Display matrix and list represenatation of graph\n";
    std::cout << "4. Prim's Algorithm for minimal spanning tree for botherepresenatations of graph\n";
    std::cout << "5. Kruskal's Algorithm for minimal spanning tree for both represenatation of graph\n";
}

/**
 * Function controls the user options for minimal spanning tree menu. 
 * Additionaly function is checking if all data necesary for calculations is availabel.
 */
void Menu::mstMenuController() const {
    int userInput;
    bool validInput = true;
    do {
    std::cout << "\nEnter number relate to action: ";
    std::cin >> userInput;
        switch(userInput) {
            case 1: {
                std::cout << "Read from file" << std::endl;
                waitForButtonPress();
                break;
            }
            case 2: {
                std::cout << "Generate random graph" << std::endl;
                waitForButtonPress();
                break; 
            }
            case 3: {
                if (checkGraphsState())
                    continue;
                std::cout << "Represenatation of graph in form of a matrix:\n";
                graphMatrix->print_matrix();  
                std::cout << "Representation of graph in form of a list:\n";
                graphList->print_list();
                break;
            }
            case 4: {
                if (checkGraphsState())
                    continue;
                std::cout << "Prim's algorithm for both represenationts of graph:\n";
                std::cout << "Matrix represenatation:\n";
                graphMatrix->prim_mst();
                std::cout << "List represenatation:\n";
                graphList->prim_mst();
                break;
            }
            case 5: {
                if (checkGraphsState())
                    continue;
                std::cout << "Kruskal's algorithm for both represenatation of graph:\n";
                std::cout << "Matrix represenatation:\n";
                graphMatrix->kruskla_mst();
                std::cout << "List represenatation:\n";
                graphList->kruskla_mst();
                break;
            }
            default: {
                std::cout << "Invalid input\n";
                waitForButtonPress();
                validInput = false;
                break;
             }
        } 
    } while(!validInput);
}

/**
 * Function displays the shorthest path menu with all the options provided to the user.
 */
void Menu::displaySPMenu() const {
    clearTerminal();
    std::cout << "\nShothest path from vertex submenu\n";
    std::cout << "1. Read graph from file\n";
    std::cout << "2. Generate graph\n";
    std::cout << "3. Display matrix and list represenatation of graph\n";
    std::cout << "4. Dijkstra's Algorithm for the shortherst path from srouce vertex to other vertecies for both represenatations of graph\n";
    std::cout << "5. Ford-Bellman's Algorithm for the shortherst path from srouce vertex to other vertecies for both represenatation of graph\n";
}

/**
 * Function controls the options for the shorthest path menu in graph.
 * Additionaly function handles the correctness of data and if all the necesary varialbe are initalized in the program.
 */
void Menu::spMenuController() const {
   bool isValid = true;
   int userInput;
   do {
       std::cout << "\nEnter number relate to action: ";
       std::cin >> userInput; 

       switch (userInput){
            case 1: {
                std::cout << "Read from file\n";
                waitForButtonPress();
                break;
            }
            case 2: {
                std::cout << "Generate random graph\n";
                waitForButtonPress();
                break;
            }
            case 3: {
                if (checkGraphsState())
                    continue;
                std::cout << "Represenatation of graph in form of a matrix:\n";
                graphMatrix->print_matrix();  
                std::cout << "Representation of graph in form of a list:\n";
                graphList->print_list();
                break;
            }
            case 4: {
                int sourceVertex= -1; 
                bool isSourceVeretexValid = true;
                if (checkGraphsState())
                    continue;

                do {
                    std::cout << "Dijkstra's algorithm for both representations:\n";
                    std::cout << "Input the source vertex: ";
                    std::cin >> sourceVertex; 
                    isSourceVeretexValid= check_if_vertex_exist(sourceVertex);
                    if (!isSourceVeretexValid)
                        clearTerminal();
                } while(!isSourceVeretexValid);

                std::cout << "Matrix representation:\n";
                graphMatrix->dijkstra(sourceVertex);
                std::cout << "List representation:\n";
                graphList->dijkstra(sourceVertex);
                break;
            }
            case 5: {
                int sourceVertex = -1;
                bool isSourceVeretexValid = true;
                if (checkGraphsState())
                    continue;
                do {
                    std::cout << "Ford Bellman's algorithm for both representations:\n";
                    std::cout << "Input the source vertex: ";
                    isSourceVeretexValid = check_if_vertex_exist(sourceVertex);
                    if (!isSourceVeretexValid)
                        clearTerminal();
                } while(!isSourceVeretexValid);

                std::cout << "Matrix representation:\n";
                graphMatrix->bellman_ford(sourceVertex);
                std::cout << "List representation:\n";
                graphList->bellman_ford(sourceVertex);
                break;
            }
            default: {
                std::cout << "Invalid input" << std::endl;
                waitForButtonPress();
                isValid = false;
                break;
            }
       } 
   }while(!isValid);
}

/**
 * Functio checks if the vertex provided by the user is availabel in the graphs.
 * Function returns the true if the vertex exists in other case the function return false.
 */
bool Menu::check_if_vertex_exist(int src_vertex) const  {
    return (vertexNumber >= 0 && src_vertex <= vertexNumber) ? true : false;
}

/**
 * Function checks if both graphs have been initalized before performing any calculations.
 * In case of situation when the both graph are initalized function returns false in any other case function displays
 * information about needed initalization of graph and returns true.
 * Function ensures the safty of an application.
 */
bool Menu::checkGraphsState() const  {
    if (graphList == nullptr || graphMatrix == nullptr) {
        std::cout << "Initalize graphs before performing calculations\n";
        waitForButtonPress();
        return true;
    }
    return false;
}
