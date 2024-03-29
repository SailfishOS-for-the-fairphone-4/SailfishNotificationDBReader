//
// Created by stolij on 12/22/23.
//

#ifndef SAILFISHNOTIFICATIONDBREADER_SERIALIZER_H
#define SAILFISHNOTIFICATIONDBREADER_SERIALIZER_H

#include <cstdint>

#include <vector>
#include <string>

namespace Serializer
{
    using ErrorCode_t = int32_t;
    using PayloadSize_t = uint16_t;

    template<typename T>
    ErrorCode_t SerializeInteger(T value, std::vector<uint8_t>& result)
    {
        auto* lengthBuffer = (uint8_t*)&value;
        for (size_t i = 0; i < sizeof(value); i++)
            result.emplace_back(lengthBuffer[i]);

        return 0;
    }

    template<typename T>
    std::vector<uint8_t> SerializeInteger(T value)
    {
        std::vector<uint8_t> result;
        SerializeInteger(value, result);

        return result;
    }

    template<typename T>
    ErrorCode_t DeserializeInteger(std::vector<uint8_t>::const_iterator& position, T& result)
    {
        auto* resultBuffer = (uint8_t*)&result;
        for (size_t i = 0; i < sizeof(T); i++)
            resultBuffer[i] = *position++;

        return 0;
    }

    ErrorCode_t SerializeString(const std::string& string, std::vector<uint8_t>& result);
    ErrorCode_t DeserializeString(std::vector<uint8_t>::const_iterator& position, std::string& result);

    ErrorCode_t CreateMessage(const std::vector<uint8_t>& payload, std::vector<std::vector<uint8_t>>& result, size_t maxChunkSize);
}


#endif //SAILFISHNOTIFICATIONDBREADER_SERIALIZER_H
