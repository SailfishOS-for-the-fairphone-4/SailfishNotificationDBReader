#include <iostream>
#include <vector>
#include <string>

#include <sqlite3.h>

#include "SQLite3Result.h"

#include "Notification.h"
#include "NotificationSerializer.h"

#include "Serializer.h"

struct {
    std::string DBPath;
} Arguments;

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

    //I2CDevice device(0, 0x18);

    for (auto &item : result.GetItems())
    {
        Notification notification;
        Notification::LoadFromItem(item, notification);

        SQLite3Result extrasResult;
        sqlite3_exec(dataBase, ("SELECT * FROM hints WHERE id = " + std::to_string(notification.GetId())).c_str(),
                SQLite3Result::LoadFromQuery, &extrasResult, &errorMessage);

        notification.LoadExtras(extrasResult.GetItems());

        std::cout << "ID = " << std::to_string(notification.GetId()) << "\n"
                  << "AppName = " << notification.GetAppName() << "\n"
                  << "AppIcon = " << notification.GetAppIcon() << "\n"
                  << "Summary = " << notification.GetSummary() << "\n"
                  << "Body = " << notification.GetBody() << "\n"
                  << "ExpireTimeout = " << std::to_string(notification.GetExpireTimeout()) << "\n"
                  << "DisambiguatedAppName = " << notification.GetDisambiguatedAppName() << "\n"
                  << "ExplicitAppName = " << notification.GetExplicitAppName() << "\n"
                  << "AppIconOrigin = " << notification.GetAppIconOrigin() << "\n";

        std::cout << "Extras.Timestamp = " << notification.GetExtras().Timestamp << "\n";

        std::cout << std::endl;

        std::vector<uint8_t> serializedNotification;
        NotificationSerializer::Serialize(notification, serializedNotification);

        Notification test;
        NotificationSerializer::Deserialize(serializedNotification, test);

        std::vector<uint8_t> messageToSend;
        Serializer::CreateMessage(serializedNotification, messageToSend);

        //device.SendData(testData);
    }

    return 0;
}
