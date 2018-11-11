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
                        value.cpp
                        stmt.cpp
                        expr.cpp
                        type.cpp
                        printer.cpp)

add_executable(decltest decl.test.cpp

                        value.cpp
                        decl.cpp
                        type.cpp
                        stmt.cpp
                        expr.cpp
                        printer.cpp
                        )

add_executable(rulestest expr_rules.test.cpp
                       expr_rules.cpp
                       value.cpp
                       decl.cpp
                       type.cpp
                       stmt.cpp
                       expr.cpp
                       printer.cpp
                       )

add_executable(convtest expr_conv.test.cpp
                       expr_rules.cpp
                       expr_conv.cpp
                       value.cpp
                       decl.cpp
                       type.cpp
                       stmt.cpp
                       expr.cpp
                       printer.cpp
                       )

add_executable(typedtest expr_typing.test.cpp
                       expr_typing.cpp
                       expr_rules.cpp
                       expr_conv.cpp
                       value.cpp
                       decl.cpp
                       type.cpp
                       stmt.cpp
                       expr.cpp
                       printer.cpp
                       )


                      #add_executable(decltest decltest.cpp
                      # decl.cpp
                      # stmt.cpp
                      # printer.cpp)
