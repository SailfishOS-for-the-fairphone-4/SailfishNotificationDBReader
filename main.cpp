#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "SQLite/SQLite3Result.h"

#include "Notification.h"
#include "NotificationSerializer.h"

#include "I2CDevice.h"

#include "Serializer.h"
#include "SQLite/SQLite3.h"

struct {
    std::string DBPath;
    uint8_t DeviceAddress;
    time_t SendDelay;
} Arguments;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " DeviceAddress DBPath SendDelay" << std::endl;
        return 1;
    }

    Arguments.DeviceAddress = std::stoi(argv[1], nullptr, 16);
    Arguments.DBPath = std::string(argv[2]);
    Arguments.SendDelay = std::stoll(argv[3], nullptr, 10);

    SQLite3 database(Arguments.DBPath);

    SQLite3Result result;
    database.PerformQuery("SELECT * FROM notifications", result);

    I2CDevice device(0, Arguments.DeviceAddress);

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
        std::this_thread::sleep_for(std::chrono::milliseconds(Arguments.SendDelay));
    }

    return 0;
}
