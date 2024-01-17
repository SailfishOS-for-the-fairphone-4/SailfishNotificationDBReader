//
// Created by stolij on 12/22/23.
//

#include <algorithm>
#include "Notification.h"
#include "SQLite/SQLite3Item.h"
#include <sstream>
#include <chrono>
#include <iomanip>

#define TIMESTAMP_HINT_NAME "x-nemo-timestamp"

time_t ISO8601StringToTimePoint(const std::string& encoded)
{
    std::tm result = {};

    strptime(encoded.c_str(), "%FT%T%z", &result);
    return std::mktime(&result);
}

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

int Notification::LoadExtras(const std::vector<SQLite3Item>& extras)
{
    auto timestampExtra = std::find_if(extras.begin(), extras.end(),
            [](const SQLite3Item& item) { return item["hint"] == TIMESTAMP_HINT_NAME; });

    if (timestampExtra != extras.end())
    {
        auto time = ISO8601StringToTimePoint(timestampExtra->operator[]("value"));

        std::stringstream stream;
        auto test = std::localtime(&time);
        stream << std::put_time(test, "%H:%M");

        _extras.Timestamp = stream.str();
    }

    return 0;
}
