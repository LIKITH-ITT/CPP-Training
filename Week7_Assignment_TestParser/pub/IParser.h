#ifndef IPARSER_H
#define IPARSER_H

#include <string>

class IParser {
public:
    virtual bool parseFile(const std::string& filePath) = 0;
    virtual bool showParsedFile() = 0;
    virtual ~IParser() {}
};

#endif
