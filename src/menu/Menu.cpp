#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h> 
#include <fstream>

void Menu::generate_graph_from_file_mst(std::string file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cout << "Something went wrong with opening the file\n";
        return;
    }

    int edges_number, vertecies_number;
    file >> edges_number >> vertecies_number;

    graph_matrix = new Graph_Matrix(vertecies_number);
    graph_list = new Graph_List(vertecies_number);
    
    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph_matrix->add_edge(u,v, weight);
        graph_matrix->add_edge(v,u, weight);
        graph_list->add_edge(u,v,weight,false);
    }
    file.close();
}

void Menu::generate_graph_from_file_sp(std::string file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cout << "Something went wrong with opening the file\n";
        return;
    }

    int edges_number, vertecies_number;
    file >> edges_number >> vertecies_number; 

    graph_matrix = new Graph_Matrix(vertecies_number);
    graph_list = new Graph_List(vertecies_number);

    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph_matrix->add_edge(u,v,weight);
        graph_list->add_edge(u,v,weight,true);
    }
    file.close();
}

/**
 * Function waits for button press of a user 
 */
void wait_for_button_press() {
    std::cout << "Press any key to continue...\n";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Function cleras terminal based on the user operating system
 */
void clear_terminal() {
   #ifdef _WIN32
        system("cls");
   #else
        system("clear");
   #endif
}

/// @brief Function generates random integer
/// @param min - minimum boundery of integer value
/// @param max - maximum boundery of integer value
/// @return Function returns random integera value from the specified range
int get_random_int(int min, int max) {
    srand(time(NULL));
    return rand() % (max - min + 1) + min; 
}

/**
 * Function runs application until the user decides to close the appliaction
 */
void Menu::menu_runner() {
   bool should_run = true;
   do {
      display_main_menu();
      should_run = main_menu_controller(); 
   } while (should_run);
}

/**
 * Function displays the options of the main menu
 */
void Menu::display_main_menu() const {
    clear_terminal(); 
    std::cout << "\nGraph Represenatation Menu\n";
    std::cout << "1. Find minimal spanning tree in graph\n";
    std::cout << "2. Find the shorthest path from source vertex in the graph\n";
    std::cout << "3. Exit the app\n";
}

/**
 * Function controls the flow of the application based on the user input. Function returns true in every case 
 * beside the third case. When third case is inserted application return false.
 */
bool Menu::main_menu_controller() {
    int user_input; 
    bool is_valid = true ;
    do {
        is_valid = true ;
        std::cout << "Enter number related to action\n";
        user_input = get_input();
        switch (user_input) {
            case 1:{ 
               display_mst_menu();
               mst_menu_controller();
               break;
            }
            case 2:{
               display_sp_menu();
               sp_menu_controller();
               break; 
            }
            case 3: {
                return false;
            }
            default: {
                std::cout << "Invalid input" << std::endl;
                is_valid = false;
                break;
            }
        }
    }while(!is_valid);
    return true;
}

/**
 * Function displays the minimal spanning tree menu with it's options.
 */
void Menu::display_mst_menu() const {
    clear_terminal();
    std::cout << "\nFind minimal spanning tree submenu\n";
    std::cout << "1. Read graph from file\n";
    std::cout << "2. Generate graph\n";
    std::cout << "3. Display matrix and list represenatation of graph\n";
    std::cout << "4. Prim's Algorithm for minimal spanning tree for botherepresenatations of graph\n";
    std::cout << "5. Kruskal's Algorithm for minimal spanning tree for both represenatation of graph\n";
    std::cout << "6. Return to main menu\n";
}

/**
 * Function controls the user options for minimal spanning tree menu. 
 * Additionaly function is checking if all data necesary for calculations is availabel.
 */
void Menu::mst_menu_controller()  {
    int user_input;
    bool is_valid = false;
    do {
    is_valid = true;
    std::cout << "\nEnter number relate to action\n";
    user_input = get_input();
        switch(user_input) {
            case 1: {
                std::string file_name;
                std::cout << "Provide file name:";
                std::cin >> file_name;
                generate_graph_from_file_mst(file_name);
                wait_for_button_press();
                break;
            }
            case 2: {
                generate_graphs_mst();
                wait_for_button_press();
                break; 
            }
            case 3: {
                if (check_graph_state())
                    continue;
                std::cout << "Represenatation of graph in form of a matrix:\n";
                graph_matrix->print_matrix();  
                std::cout << "Representation of graph in form of a list:\n";
                graph_list->print_list();
                wait_for_button_press();
                break;
            }
            case 4: {
                if (check_graph_state())
                    continue;
                std::cout << "Prim's algorithm for both represenationts of graph:\n";
                std::cout << "Matrix represenatation:\n";
                double result_matrix = graph_matrix->prim_mst();
                std::cout << "Matrix graph time result: " << result_matrix << " ms\n"; 

                std::cout << "List represenatation:\n";
                double result_list = graph_list->prim_mst();
                std::cout << "List graph time result: " << result_list << " ms\n";

                wait_for_button_press();
                break;
            }
            case 5: {
                if (check_graph_state())
                    continue;
                std::cout << "Kruskal's algorithm for both represenatation of graph:\n";

                std::cout << "Matrix represenatation:\n";
                double result_matrix = graph_matrix->kruskla_mst();
                std::cout << "Matrix graph time result: " << result_matrix << " ms\n";

                std::cout << "List represenatation:\n";
                double result_list = graph_list->kruskla_mst();
                std::cout << "Matrix graph time result: " << result_list  << " ms\n";

                wait_for_button_press();
                break;
            }
            case 6: {
                graph_matrix = nullptr;
                graph_list = nullptr;
                return;
            }
            default: {
                std::cout << "Invalid input\n";
                wait_for_button_press();
                break;
             }
        } 
        clear_terminal();
        display_mst_menu();
    } while(true);
}

/**
 * Function displays the shorthest path menu with all the options provided to the user.
 */
void Menu::display_sp_menu() const {
    clear_terminal();
    std::cout << "\nShothest path from vertex submenu\n";
    std::cout << "1. Read graph from file\n";
    std::cout << "2. Generate graph\n";
    std::cout << "3. Display matrix and list represenatation of graph\n";
    std::cout << "4. Dijkstra's Algorithm for the shortherst path from srouce vertex to other vertecies for both represenatations of graph\n";
    std::cout << "5. Ford-Bellman's Algorithm for the shortherst path from srouce vertex to other vertecies for both represenatation of graph\n";
    std::cout << "6. Return to main menu\n";
}

/**
 * Function controls the options for the shorthest path menu in graph.
 * Additionaly function handles the correctness of data and if all the necesary varialbe are initalized in the program.
 */
void Menu::sp_menu_controller() {
   bool is_valid = true;
   int user_input;
   do {
        is_valid = true;
       std::cout << "\nEnter number relate to action\n";
       user_input = get_input(); 

       switch (user_input){
            case 1: {
                std::string file_name;
                std::cout << "Provide file name:";
                std::cin >> file_name;
                generate_graph_from_file_sp(file_name);
                wait_for_button_press();
                break;
            }
            case 2: {
                generate_graphs_sp();
                wait_for_button_press();
                break;
            }
            case 3: {
                if (check_graph_state())
                    continue;
                std::cout << "Represenatation of graph in form of a matrix:\n";
                graph_matrix->print_matrix();  
                std::cout << "Representation of graph in form of a list:\n";
                graph_list->print_list();
                wait_for_button_press();
                break;
            }
            case 4: {
                int src_vertex= -1; 
                bool is_src_vertex_valid = true;
                if (check_graph_state())
                    continue;

                do {
                    std::cout << "Dijkstra's algorithm for both representations:\n";
                    std::cout << "Input the source vertex\n";
                    src_vertex = get_input(); 
                    is_src_vertex_valid= check_if_vertex_exist(src_vertex);
                    if (!is_src_vertex_valid)
                        clear_terminal();
                } while(!is_src_vertex_valid);

                std::cout << "Matrix representation:\n";
                double result_matrix = graph_matrix->dijkstra(src_vertex);
                std::cout << "Matrix graph time result: " << result_matrix << " ms\n";

                std::cout << "List representation:\n";
                double result_list = graph_list->dijkstra(src_vertex);
                std::cout << "List graph time result: " << result_list << " ms\n";

                wait_for_button_press();
                break;
            }
            case 5: {
                int src_vertex = -1;
                bool is_src_vertex_valid = true;
                if (check_graph_state())
                    continue;
                do {
                    std::cout << "Ford Bellman's algorithm for both representations:\n";
                    std::cout << "Input the source vertex: ";
                    src_vertex = get_input();
                    is_src_vertex_valid = check_if_vertex_exist(src_vertex);
                    if (!is_src_vertex_valid)
                        clear_terminal();
                } while(!is_src_vertex_valid);

                std::cout << "Matrix representation:\n";
                double result_matrix = graph_matrix->bellman_ford(src_vertex);
                std::cout << "Matrix graph time result: " << result_matrix << " ms\n";

                std::cout << "List representation:\n";
                double result_list = graph_list->bellman_ford(src_vertex);
                std::cout << "List graph time result: " << result_list << " ms\n";

                wait_for_button_press();
                break;
            }
            case 6: {
                graph_matrix = nullptr;
                graph_list = nullptr;
                return;
            }
            default: {
                std::cout << "Invalid input\n";
                wait_for_button_press();
                break;
             }
        } 
        clear_terminal();
        display_sp_menu();
   }while(true);
}

/**
 * Functio checks if the vertex provided by the user is availabel in the graphs.
 * Function returns the true if the vertex exists in other case the function return false.
 */
bool Menu::check_if_vertex_exist(int src_vertex) const  {
    return (vertex_number >= 0 && src_vertex <= vertex_number) ? true : false;
}

/**
 * Function checks if both graphs have been initalized before performing any calculations.
 * In case of situation when the both graph are initalized function returns false in any other case function displays
 * information about needed initalization of graph and returns true.
 * Function ensures the safty of an application.
 */
bool Menu::check_graph_state() const  {
    if (graph_list == nullptr || graph_matrix == nullptr) {
        std::cout << "Initalize graphs before performing calculations\n";
        wait_for_button_press();
        return true;
    }
    return false;
}

/**
 * Function which invokes the graph generation for matrix graph 
 */
void Menu::generate_graphs_mst() { 
    clear_terminal();
    std::cout << "Right now you are generating the graph for minimal spanning tree problem!\n";
    std::cout << "Provided the number of vertex for graph\n";
    vertex_number = get_input();
    std::cout << "Provided the density for graph\n"; 
    density = get_input();
    generate_random_matrix_graph(false);
}

void Menu::generate_graphs_sp() { 
    clear_terminal();
    std::cout << "Right now you are generating the graph for shorthes path problem!\n";
    std::cout << "Provided the number of vertex for graph\n";
    vertex_number = get_input();
    std::cout << "Provided the density for graph\n"; 
    density = get_input();
    generate_random_matrix_graph(true);
}

/**
 * Function generates the random graph based on the number of vertecies and density of the graph.
 * After graph was properly generated, function invokes the copy function.
*/
void Menu::generate_random_matrix_graph(bool is_directed) {
    graph_matrix = new Graph_Matrix(vertex_number);
    UnionFind uf(vertex_number);
    
    for (int i = 1; i < vertex_number; ++i) {
        int u = get_random_int(0, i -1);
        int v = i; 
        int weight = get_random_int(1, 9); 
        graph_matrix->add_edge(u, v, weight);
        if (!is_directed) 
            graph_matrix->add_edge(v,u, weight);
        uf.union_sets(u, v);
    }
    int total_possible_edges;
    if (is_directed)
        total_possible_edges = vertex_number * (vertex_number - 1);
    else
        total_possible_edges = vertex_number * (vertex_number - 1) / 2;
    int required_edges = total_possible_edges * density / 100;
    int additional_edges = required_edges - (vertex_number-1);

    while (additional_edges > 0) {
        int u = get_random_int(0 , vertex_number-1);
        int v = get_random_int(0, vertex_number-1);
        int weight = get_random_int(1, 9);
        if (u != v && !graph_matrix->has_edge(u, v)) {
            graph_matrix->add_edge(u,v, weight);
            if (!is_directed)
                graph_matrix->add_edge(v,u,weight);
            additional_edges--;
        }
    }

    copy_graph_matrix_to_graph_list(is_directed);
}


/**
 * Function copies the graph matrix to the graph list.
*/
void Menu::copy_graph_matrix_to_graph_list(bool is_directed) {
    graph_list = new Graph_List(vertex_number);
    copy_graph_list = new Graph_List(vertex_number);

    for (int u = 0; u < vertex_number; u++) {
        for (int v = is_directed ? 0 : u; v < vertex_number; v++) {
            if (graph_matrix->has_edge(u,v)) {
                int weight = graph_matrix->get_weight(u, v);
                graph_list->add_edge(u,v, weight, is_directed);
            }
        }
    }
}

/**
 * Function handles the user input. It ensures that the provided input is and number
*/
int Menu::get_input() const {
    bool is_valid = false;
    int number = -1;
    do {
        std::string input;
        std::cout << "> ";
        std::cin >> input;
        try {
            number = std::stoi(input);
        } catch(std::exception& e) {
            std::cerr << "Provided valid input!";
            is_valid = false;
        }
    }while(is_valid);
    return  number;
}
