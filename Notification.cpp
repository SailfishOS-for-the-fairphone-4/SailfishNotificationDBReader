//
// Created by stolij on 12/22/23.
//

#include "Notification.h"
#include "SQLite3Item.h"

int Notification::LoadFromItem(const SQLite3Item& item, Notification& result)
{
    if (item.GetItems().size() != COLUMN_COUNT)
        return false;

    result._id = std::stoi(item["id"]);
    result._appName = item["app_name"];
    result._appIcon = item["app_icon"];
    result._summary = item["summary"];
    result._body = item["body"];
    result._expireTimeout = std::stoi(item["expire_timeout"]);
    result._disambiguatedAppName = item["disambiguated_app_name"];
    result._explicitAppName = item["explicit_app_name"];
    result._appIconOrigin = item["app_icon_origin"];

    return true;
}
