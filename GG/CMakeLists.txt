add_library(GG SHARED
  src/Engine/Application.cpp
)
target_include_directories(GG PUBLIC ${PROJECT_SOURCE_DIR}/GG/src)
add_definitions(-DGG_EXPORTS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")