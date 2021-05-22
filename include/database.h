#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3/sqlite3.h"
#include <string>

namespace Enchant {
// NOTE: 不加inline會導致include這個header file的所有程式會重複定義這個函數
void inline LoadDatabase(std::string      path,
                         std::string      command,
                         sqlite3_callback callback,
                         void*            data) {
    sqlite3* db;
    char*    err_msg = 0;
    int      rc      = sqlite3_open(path.c_str(), &db);

    // Database don't be opened, then we close it and stop this function.
    if (rc) {
        fprintf(stderr, "[SQL error] Can't open database, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Load data from database by executing SQL statement
    rc = sqlite3_exec(db, command.c_str(), callback, data, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[SQL error] %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);
}
}  // namespace Enchant

#endif