set(CMAKE_CXX_FLAGS -std="c++14")

project(miniC)
add_library(libmc
                       expr_rules.cpp
                       expr_typing.cpp
                       expr_conv.cpp
                       value.cpp
                       decl.cpp
                       type.cpp
                       stmt.cpp
                       expr.cpp
                       printer.cpp
                       lexer.cpp
                       keywords.cpp
                       token.cpp
                       parser.cpp
                       parser.expr.cpp
                       parser.stmt.cpp
                       )

add_executable(miniC main.cpp)
target_link_libraries(miniC libmc)

add_executable(exprtest exprtest.cpp)
target_link_libraries(exprtest libmc)

add_executable(stmttest stmttest.cpp)
target_link_libraries(stmttest libmc)

add_executable(decltest decl.test.cpp)
target_link_libraries(decltest libmc)

add_executable(rulestest expr_rules.test.cpp)
target_link_libraries(rulestest libmc)

add_executable(convtest expr_conv.test.cpp)
target_link_libraries(convtest libmc)

add_executable(typedtest expr_typing.test.cpp)
target_link_libraries(typedtest libmc)

add_executable(lexertest lexer.test.cpp)
target_link_libraries(lexertest libmc)

add_executable(parser parser.test.cpp)
target_link_libraries(parser libmc)

                      #add_executable(decltest decltest.cpp
                      # decl.cpp
                      # stmt.cpp
                      # printer.cpp)
