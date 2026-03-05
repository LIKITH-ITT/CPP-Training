#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "IParser.h"
#include "rapidcsv.h"
#include <string>

class CsvParser : public IParser {
    std::string _filePath;
    rapidcsv::Document _csvDocument;

public:
    bool parseFile(const std::string& filePath) override;
    bool showParsedFile() override;

    ~CsvParser() {}
};

#endif
