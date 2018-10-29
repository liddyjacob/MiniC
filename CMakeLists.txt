set(CMAKE_CXX_FLAGS -std="c++14")

project(miniC)
add_executable(miniC main.cpp
                     type.cpp
                     value.cpp
                     expr.cpp
                     stmt.cpp
                     printer.cpp)

add_executable(exprtest exprtest.cpp
                        expr.cpp
                        type.cpp
                        value.cpp
                        printer.cpp)

add_executable(stmttest stmttest.cpp
                        stmt.cpp
                        expr.cpp
                        type.cpp
                        value.cpp
                        printer.cpp)


                      #add_executable(decltest decltest.cpp
                      # decl.cpp
                      # stmt.cpp
                      # printer.cpp)
