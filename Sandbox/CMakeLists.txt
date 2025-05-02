add_executable(Sandbox src/Sandbox.cpp)

# 包含 GG 头文件
target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/GG/src)

# 链接 GG 库
target_link_libraries(Sandbox GG)