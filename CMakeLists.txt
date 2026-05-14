cmake_minimum_required(VERSION 3.16)
project(FortressGuard)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    ptsd

    URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip

    # Or alternatively if you want to use a specific git commit instead of a release:
    # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
    # GIT_TAG         <git_tag>

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

FetchContent_MakeAvailable(ptsd)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)



# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)
# file(GLOB_RECURSE SRC_FILES
#     CONFIGURE_DEPENDS
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
# )
# file(GLOB_RECURSE HEADER_FILES
#     CONFIGURE_DEPENDS
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
# )

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # 靜態連結 MinGW (GCC) 運行時庫
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # 靜態連結 llvm-mingw (Clang) 運行時庫
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -lc++ -lunwind")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="./Resources")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)

# Install the executable
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "."
)

# Install Resources directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    DESTINATION "."
)

# Install required runtime DLLs (only for non-static builds)
if(MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    get_filename_component(MINGW_DLL_DIR ${CMAKE_CXX_COMPILER} PATH)
    install(FILES
        "${MINGW_DLL_DIR}/libgcc_s_seh-1.dll"
        "${MINGW_DLL_DIR}/libwinpthread-1.dll"
        "${MINGW_DLL_DIR}/libstdc++-6.dll"
        DESTINATION "."
    )
endif()

# CPack configuration
set(CPACK_PACKAGE_NAME "FortressGuard")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "IanChen611")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fortress Guard - A Tower Defense Game")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "FortressGuard")
set(CPACK_GENERATOR "ZIP")
set(CPACK_MONOLITHIC_INSTALL TRUE)

include(CPack)