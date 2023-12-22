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

    template <typename T>
    ErrorCode_t SerializeInteger(T value, std::vector<uint8_t>& result)
    {
        auto* lengthBuffer = (uint8_t*)&value;
        for (size_t i = 0; i < sizeof(value); i++)
            result.emplace_back(lengthBuffer[i]);

        return 0;
    }

    ErrorCode_t SerializeString(const std::string& string, std::vector<uint8_t>& result);

    ErrorCode_t CreateMessage(const std::vector<uint8_t>& payload, std::vector<uint8_t>& result);
}


#endif //SAILFISHNOTIFICATIONDBREADER_SERIALIZER_H
