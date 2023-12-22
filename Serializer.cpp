//
// Created by stolij on 12/22/23.
//

#include "Serializer.h"

#include <limits>

namespace Serializer
{
    ErrorCode_t SerializeString(const std::string& string, std::vector<uint8_t>& result)
    {
        uint16_t stringLength = string.size();
        SerializeInteger(stringLength, result);

        for (auto c : string)
            result.emplace_back(c);

        return 0;
    }

    ErrorCode_t CreateMessage(const std::vector<uint8_t>& payload, std::vector<uint8_t>& result)
    {
        auto payloadSize = payload.size();
        if (payloadSize > std::numeric_limits<PayloadSize_t>::max())
            return -1;

        SerializeInteger((PayloadSize_t)payload.size(), result);
        result.insert(result.end(), payload.begin(), payload.end());

        return 0;
    }
}