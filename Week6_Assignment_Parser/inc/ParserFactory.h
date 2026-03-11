#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include "IParser.h"
#include <string>

class ParserFactory {
public:
    static IParser* create(const std::string& filePath);

private:
    ParserFactory() = delete;
};

#endif