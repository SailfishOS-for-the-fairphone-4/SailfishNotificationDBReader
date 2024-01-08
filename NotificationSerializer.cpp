//
// Created by lukkens on 12/22/23.
//

#include "NotificationSerializer.h"
#include "Serializer.h"

NotificationSerializer::ErrorCode_t NotificationSerializer::Serialize(const Notification& notification, std::vector<uint8_t>& result)
{
    Serializer::SerializeInteger(notification.GetId(), result);

    Serializer::SerializeString(notification.GetAppName(), result);
    Serializer::SerializeString(notification.GetBody(), result);
    Serializer::SerializeString(notification.GetExtras().Timestamp, result);

    return 0;
}

NotificationSerializer::ErrorCode_t NotificationSerializer::Deserialize(const std::vector<uint8_t>& data, Notification& result)
{
    auto cursor = data.begin();
    Serializer::DeserializeInteger(cursor, result._id);

    Serializer::DeserializeString(cursor, result._appName);
    Serializer::DeserializeString(cursor, result._body);
    Serializer::DeserializeString(cursor, result._extras.Timestamp);

    return 0;
}