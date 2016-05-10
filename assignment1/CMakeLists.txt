include_directories(include)

set(assignment1_SOURCE_FILES src/main.cpp
                             src/HiddenMarkovModel.cpp
                             src/DataParser.cpp)

add_executable(assignment1 ${assignment1_SOURCE_FILES})

add_custom_command(TARGET assignment1 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assignment1/data $<TARGET_FILE_DIR:assignment1>/data)