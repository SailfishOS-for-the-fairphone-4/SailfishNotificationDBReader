//
// Created by stolij on 12/22/23.
//

#include "SQLite3Result.h"

int SQLite3Result::LoadFromQuery(void* cResult, int argc, char** values, char** columNames)
{
    auto* result = (SQLite3Result*)cResult;

    SQLite3Item item;
    SQLite3Item::LoadFromQuery(&item, argc, values, columNames);

    result->_items.emplace_back(item);
    return 0;
}
