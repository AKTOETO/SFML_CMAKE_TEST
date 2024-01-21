# adding subdirectory with hello lib
add_subdirectory(hello)

###################################################
#           CREATING EXECUTABLE FILE
###################################################

# Creating excecutable file
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# linking libs to executable file
target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
        sfml-graphics sfml-network sfml-audio
        hello
        spdlog::spdlog
)