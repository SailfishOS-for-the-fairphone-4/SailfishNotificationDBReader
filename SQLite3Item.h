//
// Created by stolij on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_SQLITE3ITEM_H
#define SAILFISHNOTIFICATIONDBREADER_SQLITE3ITEM_H

#include <cstddef>
#include <cstdint>

#include <map>
#include <string>

class SQLite3Item
{
public:
    static int LoadFromQuery(void *cResult, int argc, char **values, char **columNames);

    const std::map<std::string, std::string>& GetItems() const
    {
        return _items;
    }

    std::string operator[](const std::string &key) const
    {
        return _items.at(key);
    }

private:
    std::map<std::string, std::string> _items;
};


#endif //SAILFISHNOTIFICATIONDBREADER_SQLITE3ITEM_H
