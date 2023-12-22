//
// Created by lukkens on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H
#define SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H

#include <cstdint>
#include <vector>

#include "Notification.h"

namespace NotificationSerializer
{
    using ErrorCode_t = int32_t;

    ErrorCode_t Serialize(const Notification& notification, std::vector<uint8_t>& result);
}


#endif //SAILFISHNOTIFICATIONDBREADER_NOTIFICATIONSERIALIZER_H
