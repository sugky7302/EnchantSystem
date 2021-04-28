message("Start to install ${CMAKE_CURRENT_SOURCE_DIR}...")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 不能用file(GLOB_RECURSE *.cpp)，會報錯
# 還找不到SET讀取目錄下所有檔案的方法
add_library(SQLITE sqlite3.h sqlite3ext.h sqlite3.c shell.c)

message("Installed ${SQLITE}")