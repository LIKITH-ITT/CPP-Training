#include "JsonParser.h"
#include "Logger.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool JsonParser::parseFile(const std::string& filePath) {
    bool isParsedSuccessfully = true;
    _filePath = filePath;
    std::ifstream file(filePath);

    try
    {
        if (!file.is_open())
        {
            Logger::printMessage(Constants::MSG_JSON_EMPTY_FAIL + filePath + Logger::printNextLine());
            isParsedSuccessfully = false;
        }
        else if (file.peek() == std::ifstream::traits_type::eof())
        {
            Logger::printMessage(Constants::MSG_JSON_EMPTY_FAIL + filePath + Logger::printNextLine());
            isParsedSuccessfully = false;
        }
        else
        {
            file >> _jsonDocument;
        }
    }
    catch (const nlohmann::json::parse_error& error)
    {
        Logger::printMessage(Constants::MSG_JSON_SYNTAX_ERROR + error.what() + Logger::printNextLine());
        isParsedSuccessfully = false;
    }
    catch (const nlohmann::json::exception& error)
    {
        Logger::printMessage(Constants::MSG_JSON_TYPE_ERROR + error.what() + Logger::printNextLine());
        isParsedSuccessfully = false;
    }
    catch (const std::exception& error)
    {
        Logger::printMessage(Constants::MSG_JSON_KEY_ERROR + error.what() + Logger::printNextLine());
        isParsedSuccessfully = false;
    }

    file.close();
    return isParsedSuccessfully;
}

bool JsonParser::showParsedFile() {
    bool isDisplayedSuccessfully = true;

    try
    {
        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_RESULT_FILE << _filePath;
        std::cout << Constants::MSG_RESULT_FORMAT << Constants::LABEL_JSON;
        std::cout << Constants::MSG_RESULT_RECORDS << _jsonDocument.size();
        std::cout << Constants::MSG_RESULT_BORDER;

        if (_jsonDocument.empty())
        {
            std::cout << Constants::MSG_NO_RECORDS;
        }
        else if (_jsonDocument.is_array())
        {
            int recordNumber = 1;
            for (const nlohmann::ordered_json& element : _jsonDocument)
            {
                std::cout << Constants::MSG_RESULT_DIVIDER << recordNumber << Constants::MSG_RECORD_SUFFIX;

                for (nlohmann::ordered_json::const_iterator iterator = element.begin(); iterator != element.end(); ++iterator)
                {
                    std::cout << "  " << std::left << std::setw(15) << iterator.key() << " : " << iterator.value() << Logger::printNextLine();
                }

                std::cout << Logger::printNextLine();
                ++recordNumber;
            }
        }
        else if (_jsonDocument.is_object())
        {
            std::cout << Constants::MSG_RESULT_DIVIDER << 1 << Constants::MSG_RECORD_SUFFIX;

            for (nlohmann::ordered_json::const_iterator iterator = _jsonDocument.begin(); iterator != _jsonDocument.end(); ++iterator)
            {
                std::cout << "  " << std::left << std::setw(15) << iterator.key() << " : " << iterator.value() << Logger::printNextLine();
            }

            std::cout << Logger::printNextLine();
        }

        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_PARSE_COMPLETE;
        std::cout << Constants::MSG_RESULT_BORDER;
    }
    catch (const nlohmann::json::exception& error)
    {
        Logger::printMessage(Constants::MSG_JSON_TYPE_ERROR + std::string(error.what()) + Logger::printNextLine());
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}