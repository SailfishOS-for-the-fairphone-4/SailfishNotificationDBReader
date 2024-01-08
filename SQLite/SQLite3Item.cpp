//
// Created by stolij on 12/22/23.
//

#include "SQLite3Item.h"

int SQLite3Item::LoadFromQuery(void* cResult, int argc, char** values, char** columNames)
{
    auto* result = (SQLite3Item*)cResult;
    for (size_t i = 0; i < argc; i++)
        result->_items.emplace(columNames[i], values[i]);

    return 0;
}
