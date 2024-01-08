//
// Created by stolij on 1/8/24.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_SQLITE3_H
#define SAILFISHNOTIFICATIONDBREADER_SQLITE3_H

#include <sqlite3.h>

#include <string>
#include "SQLite3Result.h"

class SQLite3
{
public:
    explicit SQLite3(const std::string& path);
    ~SQLite3();

    SQLite3(const SQLite3& other) = delete;
    SQLite3 operator=(const SQLite3& other) = delete;

    std::string GetLastError();

    [[nodiscard]]
    bool IsOpen() const
    {
        return _isOpen;
    }

    int PerformQuery(const std::string& query, SQLite3Result& result);

private:
    std::string _lastError;
    bool _isOpen = false;

    sqlite3* _database;
};


#endif //SAILFISHNOTIFICATIONDBREADER_SQLITE3_H
