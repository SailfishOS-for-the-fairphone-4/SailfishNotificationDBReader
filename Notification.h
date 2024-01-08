//
// Created by stolij on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_NOTIFICATION_H
#define SAILFISHNOTIFICATIONDBREADER_NOTIFICATION_H

#include <cstddef>
#include <cstdint>

#include <string>

class SQLite3Item;

class Notification
{
public:
    friend class NotificationSerializer;
    static const constexpr size_t COLUMN_COUNT = 9;

    static int LoadFromItem(const SQLite3Item& item, Notification& result);

    [[nodiscard]]
    int32_t GetId() const
    {
        return _id;
    }

    [[nodiscard]]
    const std::string& GetAppName() const
    {
        return _appName;
    }

    [[nodiscard]]
    const std::string& GetAppIcon() const
    {
        return _appIcon;
    }

    [[nodiscard]]
    const std::string& GetSummary() const
    {
        return _summary;
    }

    [[nodiscard]]
    const std::string& GetBody() const
    {
        return _body;
    }

    [[nodiscard]]
    int32_t GetExpireTimeout() const
    {
        return _expireTimeout;
    }

    [[nodiscard]]
    const std::string& GetDisambiguatedAppName() const
    {
        return _disambiguatedAppName;
    }

    [[nodiscard]]
    const std::string& GetExplicitAppName() const
    {
        return _explicitAppName;
    }

    [[nodiscard]]
    const std::string& GetAppIconOrigin() const
    {
        return _appIconOrigin;
    }

private:
    int32_t _id = 0;
    std::string _appName;
    std::string _appIcon;
    std::string _summary;
    std::string _body;
    int32_t _expireTimeout = 0;
    std::string _disambiguatedAppName;
    std::string _explicitAppName;
    std::string _appIconOrigin;
};


#endif //SAILFISHNOTIFICATIONDBREADER_NOTIFICATION_H
