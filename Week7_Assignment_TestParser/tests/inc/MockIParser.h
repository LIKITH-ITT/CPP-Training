#ifndef MOCK_IPARSER_H
#define MOCK_IPARSER_H

#include "IParser.h"
#include <gmock/gmock.h>

class MockIParser : public IParser
{
public:
    MOCK_METHOD(bool, parseFile, (const std::string& filePath), (override));
    MOCK_METHOD(bool, showParsedFile, (), (override));
};

#endif
