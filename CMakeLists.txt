cmake_minimum_required(VERSION "3.25.0")
project("graphProject")
add_executable("${PROJECT_NAME}" "src/main.cpp" "src/graphRepresentation/GraphMatrix.cpp" "src/graphRepresentation/GraphList.cpp" "src/algorithmAdditionalElements/UnionFind.cpp" "src/menu/Menu.cpp")

