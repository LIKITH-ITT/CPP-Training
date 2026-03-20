#include "ParserFactory.h"
#include "Constants.h"
#include "JsonParser.h"
#include "CsvParser.h"
#include "XmlParser.h"
#include "Validator.h"
#include <algorithm>

IParser* ParserFactory::create(const std::string& filePath)
{
    IParser* parser = nullptr;
    std::string extension = Validator::extractExtension(filePath);

    if (extension == Constants::FORMAT_JSON)
    {
        parser = new JsonParser();
    }
    else if (extension == Constants::FORMAT_CSV)
    {
        parser = new CsvParser();
    }
    else if (extension == Constants::FORMAT_XML)
    {
        parser = new XmlParser();
    }

    return parser;
}
