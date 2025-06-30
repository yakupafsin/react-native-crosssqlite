#include "sqlite3.h"
#include "sqlite_bridge.h"

#include <sstream>
#include <string>

static sqlite3* db = nullptr;
static std::string last_select_result;

int open_db(const char* path) {
    int rc = sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr);
    }
    return rc;
}

int exec_sql(const char* sql) {
    if (!db) return -1;
    char* errMsg = nullptr;
    return sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
}

void close_db() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

const char* select_json(const char* sql) {
    if (!db) return "[]";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return "[]";
    }

    std::ostringstream oss;
    oss << "[";
    bool firstRow = true;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!firstRow) oss << ",";
        oss << "{";

        int colCount = sqlite3_column_count(stmt);
        for (int i = 0; i < colCount; ++i) {
            const char* colName = sqlite3_column_name(stmt, i);
            const char* colText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));

            if (i > 0) oss << ",";
            oss << "\"" << colName << "\":";
            if (colText) {
                oss << "\"" << colText << "\"";
            } else {
                oss << "null";
            }
        }

        oss << "}";
        firstRow = false;
    }

    oss << "]";
    sqlite3_finalize(stmt);

    last_select_result = oss.str();
    return last_select_result.c_str();
}

const char* get_journal_mode() {
    if (!db) return "closed";

    sqlite3_stmt* stmt;
    const char* sql = "PRAGMA journal_mode;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return "error";
    }

    const char* mode = "unknown";
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        mode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return mode;
}

