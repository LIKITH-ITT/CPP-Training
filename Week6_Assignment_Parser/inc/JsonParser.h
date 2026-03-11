#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "IParser.h"
#include "json.hpp"
#include <string>

class JsonParser : public IParser {
    std::string _filePath;
    nlohmann::ordered_json _jsonDocument;

public:
    bool parseFile(const std::string& filePath) override;
    bool showParsedFile() override;

    ~JsonParser() {}
};

#endif
