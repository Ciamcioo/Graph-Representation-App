#ifndef MENU
#define MENU
#include "../graphRepresentation/GraphList.h"
#include "../graphRepresentation/GraphMatrix.h"
#include <iostream>

class Menu {
    private:
        Graph_List* graph_list;
        Graph_List* copy_graph_list;
        Graph_Matrix* graph_matrix;
        int vertex_number = 5;
        int density = 50;
        
        void generate_random_matrix_graph(bool is_directed);
        void copy_graph_matrix_to_graph_list(bool is_directed);
    public:

        // Function invokes the main application implementation
        void menu_runner();

        // Function displays availabel algorithms in the application
        void display_main_menu() const;

        // Function controls the flow of the program based on user input
        bool main_menu_controller();

        // Function displays submenu with options for the MST algorithm -> MST - minimal spanning tree
        void display_mst_menu() const;

        // Function controls the flow of the program when user chose the minimal spanning tree option 
        void mst_menu_controller();
        
        // Function controls the flow of the program when user chose the shorthest path option 
        void display_sp_menu() const; 
        
        // Function controls the flow of the program based on user input
        void sp_menu_controller(); 

        // Function checks if source vertex provided by the user is correct
        bool check_if_vertex_exist(int src_vertex) const;

        // Function handles the process of genearting the graph
        void generate_graphs_mst();
        void generate_graphs_sp();
        
        void generate_graph_from_file_mst(std::string file_name);
        void generate_graph_from_file_sp(std::string file_name); 

        // Function checks if graphs have been initialized
        bool check_graph_state() const ;
        int get_input() const ;
        
};






#endif 
