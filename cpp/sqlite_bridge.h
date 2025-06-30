#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int open_db(const char* path);
int exec_sql(const char* sql);
void close_db();
const char* select_json(const char* sql);
const char* get_journal_mode();

#ifdef __cplusplus
}
#endif
