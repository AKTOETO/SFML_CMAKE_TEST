cmake_minimum_required(VERSION 3.16)
project(sfml_test 
        LANGUAGES CXX
        VERSION 0.0.0.1
)

# setting output dir for executable file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# build all libs staticly 
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

###################################################
#               DOWNLOADING PACKAGES
###################################################

# enable FetchContent
include(FetchContent)

# enable fetchcontent messages
set(FETCHCONTENT_QUIET FALSE)

message(STATUS "downloading SFML")

# Downloading SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
	GIT_PROGRESS TRUE
)

message(STATUS "downloading spdlog")

# Downloading SPDLOG
FetchContent_Declare(
    SPDLOG
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
	GIT_PROGRESS TRUE
)

# Making Avalible !!!ALL!!! libs
FetchContent_MakeAvailable(SFML SPDLOG)

# link spdlog to all files (SFML already linked)
set(CMAKE_STANDARD_LIBRARIES 
    ${CMAKE_STANDARD_LIBRARIES}
    spdpog::spdlog
)

###################################################
#           CREATING EXECUTABLE FILE
###################################################

# fetching all .cpp files from src/
file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HDRS "include/*.hpp")

foreach(el IN LISTS SRCS)
    message(${el})    
endforeach()


foreach(el IN LISTS HDRS)
    message(${el})
endforeach()

# Creating excecutable file
add_executable(${CMAKE_PROJECT_NAME} WIN32 
    ${SRCS}
	${HDRS}
)

# linking all libs to executable file
target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
        sfml-graphics sfml-network sfml-audio
        spdlog::spdlog
)

# including all headers to executable
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        include
)

###################################################
#               COMPILER SETTINGS
###################################################

# compile all with c++20
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# if compiler is clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

# disabling console window in release build type
if (WIN32)
    # if config is debug set the variable to "/SUBSYSTEM:CONSOLE," else "/SUBSYSTEM:WINDOWS", append "/ENTRY:mainCRTStartup>" in any case 
    set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS;/ENTRY:mainCRTStartup>")
else()
    # if config is not debug set the variable to "-mwindows" else nothing
    # set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<NOT:$<CONFIG:Debug>>,-mwindows,>")
endif()

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

###################################################
#               ADDITIONAL SETTINGS
###################################################

# For Windows sfml
# (Copy DLLs for Windows runtime)
if(WIN32)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

# copy asset folder to bin folder
add_custom_target(
    copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "${CMAKE_BINARY_DIR}/bin/assets"
    COMMENT "Copy assets from ${PROJECT_SOURCE_DIR}/assets to ${CMAKE_BINARY_DIR}/bin/assets"
)
add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)

install(TARGETS ${CMAKE_PROJECT_NAME})