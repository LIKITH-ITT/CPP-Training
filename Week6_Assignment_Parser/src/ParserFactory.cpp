#include "ParserFactory.h"
#include "Constants.h"
#include "JsonParser.h"
#include "CsvParser.h"
#include "XmlParser.h"
#include <algorithm>

IParser* ParserFactory::create(const std::string& filePath) {
    int dotPosition = filePath.rfind(Constants::FULL_STOP);

    if (dotPosition == (int)std::string::npos)
        return nullptr;

    std::string extension = filePath.substr(dotPosition + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper);

    if (extension == Constants::FORMAT_JSON)
        return new JsonParser();

    if (extension == Constants::FORMAT_CSV)
        return new CsvParser();

    if (extension == Constants::FORMAT_XML)
        return new XmlParser();

    return nullptr;
}