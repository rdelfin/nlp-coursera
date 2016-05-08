include_directories(include)

set(assignment1_SOURCE_FILES src/main.cpp
                             src/HiddenMarkovModel.cpp)

add_executable(assignment1 ${assignment1_SOURCE_FILES})