# 规定该CMakeLists.txt适用的cmake最小版本，这里是 3.20
cmake_minimum_required(VERSION 3.20)

# set the project name
project(EnchantSystem)

add_definitions(-std=c++11)

# specify the C++ standard 
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# 这行要添加，否则gdb调试会出问题
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 定义SRC_FILE为当前目录下后缀为cpp的文件列表
file(GLOB SRC_FILE src/*.cpp)

# set the include folderh
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/lib/sqlite3
)

## 新增子資料夾
# add_subdirectory(src)

# 定义生成的可执行文件(程序)的名称，
# 相当于visual studio项目属性中的目标文件名，
# 这里是 Tutorial
# 用${PROJECT_NAME}替代，即可执行文件名称等于项目名称
# 和加入编译的源文件路径列表，路径相对于`CMakeLists.txt`所在目录，
# 相当于visual studio项目解决方案资源管理器中列出来的文件，这里是 tutroial.c
add_executable(${PROJECT_NAME} ${SRC_FILE})

# 將執行檔(executable)和外部庫(library)連結，使執行檔能夠使用外部庫
# target_link_libraries(${PROJECT_NAME} sqlite3)