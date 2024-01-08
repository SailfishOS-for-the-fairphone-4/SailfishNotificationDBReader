//
// Created by stolij on 12/22/23.
//

#include "Serializer.h"

#include <limits>

namespace Serializer
{
    ErrorCode_t SerializeString(const std::string& string, std::vector<uint8_t>& result)
    {
        PayloadSize_t stringLength = string.size();
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

    ErrorCode_t DeserializeString(std::vector<uint8_t>::const_iterator& position, std::string& result)
    {
        PayloadSize_t stringLength = 0;
        DeserializeInteger(position, stringLength);

        for (size_t i = 0; i < stringLength; i++)
            result += ((char)*position++);

        if (result.size() != stringLength)
            return -1;

        return 0;
    }
}