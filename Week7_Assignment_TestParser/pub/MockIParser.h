#ifndef MOCK_IPARSER_H
#define MOCK_IPARSER_H

#include <gmock/gmock.h>
#include "IParser.h"

class MockIParser : public IParser
{
public:
    MOCK_METHOD(bool, parseFile, (const std::string& filePath), (override));
    MOCK_METHOD(bool, showParsedFile, (), (override));
};

#endif
