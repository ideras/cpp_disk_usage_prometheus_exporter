cmake_minimum_required(VERSION 3.16)
project(disk_usage_exporter_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(oatpp          1.3.0 REQUIRED)
find_package(prometheus-cpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME}  App.cpp 
                                AppComponent.hpp
                                DiskUsage.cpp
                                DiskUsage.h
                                ErrorHandler.cpp
                                ErrorHandler.hpp
                                DiskUsageController.hpp
                                StaticController.hpp
                                dto/DiskUsageDto.hpp
                                dto/StatusDto.hpp)

target_link_libraries(${PROJECT_NAME}
        PUBLIC oatpp::oatpp
        prometheus-cpp::push
        prometheus-cpp::pull
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()
