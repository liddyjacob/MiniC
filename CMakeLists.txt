
set(CMAKE_CXX_FLAGS -std="c++11")

project(miniC)
add_executable(miniC main.cpp
                     type.cpp
                     expr.cpp
                     stmt.cpp)

add_executable(exprtest exprtest.cpp
                        expr.cpp
                        type.cpp)
