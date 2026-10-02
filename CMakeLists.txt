cmake_minimum_required(VERSION 3.24)
project(VulkanRenderer)

find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED COMPONENTS volk shaderc_combined)
find_package(glm REQUIRED)

# Collect all source files
file(GLOB ENGINE "src/engine/*.cpp")
file(GLOB GAME "src/game/*.cpp")
file(GLOB SOURCE "src/*.cpp")

set(ALL_SOURCES ${SOURCE} ${ENGINE} ${GAME})

# Add the executable with ALL source files
add_executable(VulkanRenderer ${ALL_SOURCES})

if(MSVC)
    target_compile_options(vulkanapp PRIVATE /std:c++latest)
endif()

# Add the headers directory and GLM include directory
target_include_directories(VulkanRenderer PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/headers/game
    ${CMAKE_SOURCE_DIR}/headers/engine

    Vulkan::Vulkan
    Vulkan::volk
    Vulkan::shaderc_combined
    SDL3::SDL3
    glm::glm

    /usr/include  # GLM is installed here on Ubuntu
)