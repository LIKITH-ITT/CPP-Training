#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "IParser.h"
#include "tinyxml2.h"
#include <string>

class XmlParser : public IParser {
    std::string _filePath;
    tinyxml2::XMLDocument _xmlDocument;

public:
    bool parseFile(const std::string& filePath) override;
    bool showParsedFile() override;

    ~XmlParser() {}
};

#endif
