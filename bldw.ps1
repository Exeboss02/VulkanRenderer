cls
mkdir build
cd build
cmake .. -A x64 -DSDL3_DIR="C:/VulkanSDK/1.4.363.0/cmake" "-DCMAKE_PREFIX_PATH=C:/VulkanSDK/1.4.363.0"
cmake --build . --config Debug
cd ..