//
// Created by lukkens on 12/22/23.
//

#include "NotificationSerializer.h"
#include "Serializer.h"

namespace NotificationSerializer
{
    ErrorCode_t Serialize(const Notification& notification, std::vector<uint8_t>& result)
    {
        Serializer::SerializeInteger(notification.GetId(), result);

        Serializer::SerializeString(notification.GetAppName(), result);
        Serializer::SerializeString(notification.GetBody(), result);
        Serializer::SerializeString("", result);

        return 0;
    }
}