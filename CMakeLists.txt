cmake_minimum_required(VERSION 3.10)

project(CityPowerManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core/app.cpp
    src/core/billing_system.cpp
    src/models/commercial_subscriber.cpp
    src/models/industrial_subscriber.cpp
    src/models/residential_subscriber.cpp
    src/models/subscriber.cpp
    src/models/tariff.cpp
    src/utils/file_io.cpp
)

# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

# target_link_libraries(${PROJECT_NAME} some_library)
