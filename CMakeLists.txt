cmake_minimum_required(VERSION 3.24)
project(VulkanRenderer)

find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED COMPONENTS volk shaderc_combined)
if(WIN32)
    find_path(GLM_INCLUDE_DIR glm/glm.hpp HINTS $ENV{VULKAN_SDK}/Include)
    set(GLM_LIBS "")              # header-only and nothing to link
else()
    find_package(glm REQUIRED)
    set(GLM_LIBS glm::glm)
endif()

# Collect all source files
file(GLOB ENGINE "src/engine/*.cpp")
file(GLOB GAME "src/game/*.cpp")
file(GLOB SOURCE "src/*.cpp")

set(ALL_SOURCES ${SOURCE} ${ENGINE} ${GAME})

# Add the executable with ALL source files
add_executable(VulkanRenderer ${ALL_SOURCES})

if(MSVC)
    target_compile_options(VulkanRenderer PRIVATE /std:c++latest)
endif()

target_link_libraries(VulkanRenderer PRIVATE

    Vulkan::Vulkan
    Vulkan::volk
    Vulkan::shaderc_combined
    SDL3::SDL3
    ${GLM_LIBS}
)

# Add the headers directory and GLM include directory
target_include_directories(VulkanRenderer PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/headers/game
    ${CMAKE_SOURCE_DIR}/headers/engine

    if(GLM_INCLUDE_DIR)
        ${GLM_INCLUDE_DIR}
    endif()
)