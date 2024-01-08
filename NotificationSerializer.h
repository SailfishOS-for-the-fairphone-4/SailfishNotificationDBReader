//
// Created by lukkens on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H
#define SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H

#include <cstdint>
#include <vector>

#include "Notification.h"

class NotificationSerializer
{
public:
    using ErrorCode_t = int32_t;

    static ErrorCode_t Serialize(const Notification& notification, std::vector<uint8_t>& result);
    static ErrorCode_t Deserialize(const std::vector<uint8_t>& data, Notification& result);

private:
    NotificationSerializer() = default;
    ~NotificationSerializer() = default;
};


#endif //SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H
