//
// Created by stolij on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_SQLITE3RESULT_H
#define SAILFISHNOTIFICATIONDBREADER_SQLITE3RESULT_H


#include <vector>

#include "SQLite3Item.h"

class SQLite3Result
{
public:
    static int LoadFromQuery(void* cResult, int argc, char** values, char** columNames);

    const std::vector<SQLite3Item>& GetItems() const
    {
        return _items;
    }

private:
    std::vector<SQLite3Item> _items;
};


#endif //SAILFISHNOTIFICATIONDBREADER_SQLITE3RESULT_H
