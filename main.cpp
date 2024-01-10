#include <iostream>
#include <vector>
#include <string>

#include "SQLite/SQLite3Result.h"

#include "Notification.h"
#include "NotificationSerializer.h"

#include "I2CDevice.h"

#include "Serializer.h"
#include "SQLite/SQLite3.h"

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

    SQLite3 database(Arguments.DBPath);

    SQLite3Result result;
    database.PerformQuery("SELECT * FROM notifications", result);

    I2CDevice device(1, 0x0E);

    for (auto &item : result.GetItems())
    {
        Notification notification;
        Notification::LoadFromItem(item, notification);

        SQLite3Result extrasResult;
        database.PerformQuery("SELECT * FROM hints WHERE id = " + std::to_string(notification.GetId()), extrasResult);

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

        std::vector<std::vector<uint8_t>> messageToSend;
        Serializer::CreateMessage(serializedNotification, messageToSend, 240);

        device.SendData(messageToSend[0]);
    }

    return 0;
}
