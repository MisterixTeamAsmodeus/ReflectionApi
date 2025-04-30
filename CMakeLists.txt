cmake_minimum_required(VERSION 3.10)

set(reflection_api_project_name ReflectionApi)
option(REFLECTION_API_EXAMPLE "Add ReflectionApi examples file as executable (on|off)" OFF)

project(${reflection_api_project_name} LANGUAGES CXX)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include
        DESTINATION include
)

if (${REFLECTION_API_EXAMPLE})
    add_subdirectory(example)
endif ()