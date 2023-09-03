# 指定最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.0)

# 设置项目名称
project(EMS_system)

# 添加可执行文件并列出源代码文件
add_executable(EMS_system EMS.cpp workerManager.cpp employee.cpp manager.cpp boss.cpp)

# 设置可执行文件的名称（可选）
# 如果需要指定可执行文件的名称，可以使用以下方式设置
set_target_properties(EMS_system PROPERTIES OUTPUT_NAME "System")

# 如果需要链接外部库，可以使用以下方式配置依赖项
# find_package(SomePackage REQUIRED)
# target_link_libraries(my_app SomePackage::SomeLibrary)
