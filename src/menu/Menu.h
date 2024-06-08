#ifndef MENU
#define MENU
#include "../graphRepresentation/GraphList.h"
#include "../graphRepresentation/GraphMatrix.h"

class Menu {
    private:
        GraphList* graphList;
        GraphMatrix* graphMatrix;
        int vertexNumber;
        int density;
    public:

        // Function invokes the main application implementation
        void menuRunner();

        // Function displays availabel algorithms in the application
        void displayMainMenu() const;

        // Function controls the flow of the program based on user input
        bool mainMenuController() const;

        // Function displays submenu with options for the MST algorithm -> MST - minimal spanning tree
        void displayMSTMenu() const;

        // Function controls the flow of the program when user chose the minimal spanning tree option 
        void mstMenuController() const;
        
        // Function controls the flow of the program when user chose the shorthest path option 
        void displaySPMenu() const; 
        
        // Function controls the flow of the program based on user input
        void spMenuController() const; 

        // Function checks if source vertex provided by the user is correct
        bool check_if_vertex_exist(int src_vertex) const;

        // Function displays submenu for graph generation
        //void displayGraphGenerationMenu() const;

        // Function checks if graphs have been initialized
        bool checkGraphsState() const ;
        
};






#endif 
