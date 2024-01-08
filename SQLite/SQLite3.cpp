//
// Created by stolij on 1/8/24.
//

#include "SQLite3.h"

SQLite3::SQLite3(const std::string& path)
{
     _isOpen = sqlite3_open(path.c_str(), &_database) == 0;
}

std::string SQLite3::GetLastError()
{
    return sqlite3_errmsg(_database);
}

int SQLite3::PerformQuery(const std::string& query, SQLite3Result& result)
{
    char* errorMessage;
    auto status = sqlite3_exec(_database, query.c_str(), SQLite3Result::LoadFromQuery, &result, &errorMessage);
    if (errorMessage != nullptr)
        _lastError = std::string(errorMessage);

    return status;
}

SQLite3::~SQLite3()
{
    sqlite3_close(_database);
}
