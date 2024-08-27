#pragma once

#include <string_view>
#include "LineAbstractRequestParser.h"

namespace Line
{
    class AbstractRequestWithNameParser : public AbstractRequestParser
    {
    public:
        AbstractRequestWithNameParser() = default;

    protected:
        virtual std::string_view ParseName() const;
    };
    using AbstractRequestWithNameParserShp = std::shared_ptr<AbstractRequestWithNameParser>;
}

