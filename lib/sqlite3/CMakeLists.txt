message("Start to install SQLite3...")

file(GLOB SRC_FILE *.cpp)
file(GLOB HEADER_FILE *.h)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(SQLite ${HEADER_FILE} ${SRC_FILE})

message("Installed SQLite3")