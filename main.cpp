#include <iostream>
#include <map>
#include <vector>
#include <string>

#include <sqlite3.h>

#include <I2CDevice.h>

struct {
    std::string DBPath;
} Arguments;

class SQLite3Item
{
public:
    static int LoadFromQuery(void *cResult, int argc, char **values, char **columNames)
    {
        auto* result = (SQLite3Item*)cResult;
        for (size_t i = 0; i < argc; i++)
            result->_items.emplace(columNames[i], values[i]);

        return 0;
    }

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

class SQLite3Result
{
public:
    static int LoadFromQuery(void* cResult, int argc, char** values, char** columNames)
    {
        auto* result = (SQLite3Result*)cResult;

        SQLite3Item item;
        SQLite3Item::LoadFromQuery(&item, argc, values, columNames);

        result->_items.emplace_back(item);
        return 0;
    }

    const std::vector<SQLite3Item>& GetItems() const
    {
        return _items;
    }

private:
    std::vector<SQLite3Item> _items;
};

class Notification
{
public:
    static const constexpr size_t COLUMN_COUNT = 9;

    static int LoadFromItem(const SQLite3Item& item, Notification& result)
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

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " DBPath" << std::endl;
        return 1;
    }

    Arguments.DBPath = std::string(argv[1]);

    sqlite3 *dataBase;
    sqlite3_open(Arguments.DBPath.c_str(), &dataBase);

    char *errorMessage = nullptr;
    SQLite3Result result;
    sqlite3_exec(dataBase, "SELECT * FROM notifications", SQLite3Result::LoadFromQuery, &result, &errorMessage);

    I2CDevice device(0, 0x18);

    for (auto &item : result.GetItems())
    {
        Notification notification;
        Notification::LoadFromItem(item, notification);

        std::cout << "ID = " << std::to_string(notification.GetId()) << "\n"
                  << "AppName = " << notification.GetAppName() << "\n"
                  << "AppIcon = " << notification.GetAppIcon() << "\n"
                  << "Summary = " << notification.GetSummary() << "\n"
                  << "Body = " << notification.GetBody() << "\n"
                  << "ExpireTimeout = " << std::to_string(notification.GetExpireTimeout()) << "\n"
                  << "DisambiguatedAppName = " << notification.GetDisambiguatedAppName() << "\n"
                  << "ExplicitAppName = " << notification.GetExplicitAppName() << "\n"
                  << "AppIconOrigin = " << notification.GetAppIconOrigin() << "\n"
                  << std::endl;
    }

    std::vector<__u8> testData = { 'a', 'b', 'c', 'd' };
    device.SendData(testData);

    return 0;
}
