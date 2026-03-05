#include "XmlParser.h"
#include "Logger.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>

bool XmlParser::parseFile(const std::string& filePath) {
    bool isParsedSuccessfully = true;
    _filePath = filePath;
    tinyxml2::XMLError result = _xmlDocument.LoadFile(filePath);

    if (result != tinyxml2::XML_SUCCESS)
    {
        Logger::printMessage(Constants::MSG_XML_PARSE_FAIL + std::string(_xmlDocument.ErrorStr()) + Logger::printNextLine());
        isParsedSuccessfully = false;
    }

    return isParsedSuccessfully;
}

bool XmlParser::showParsedFile() {
    bool isDisplayedSuccessfully = true;

    try
    {
        tinyxml2::XMLElement* root = _xmlDocument.RootElement();

        if (root == nullptr)
        {
            Logger::printMessage(Constants::MSG_XML_NO_ROOT);
            Logger::printMessage(Logger::printNextLine());
            return false;
        }

        int recordCount = 0;
        for (tinyxml2::XMLElement* child = root->FirstChildElement();
             child != nullptr;
             child = child->NextSiblingElement())
        {
            ++recordCount;
        }

        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_RESULT_FILE << _filePath;
        std::cout << Constants::MSG_RESULT_FORMAT << Constants::LABEL_XML;
        std::cout << Constants::MSG_RESULT_RECORDS << recordCount;
        std::cout << Constants::MSG_RESULT_BORDER;

        if (recordCount == 0)
        {
            std::cout << Constants::MSG_NO_RECORDS;
        }
        else
        {
            int recordNumber = 1;

            for (tinyxml2::XMLElement* child = root->FirstChildElement();
                 child != nullptr;
                 child = child->NextSiblingElement())
            {
                std::cout << Constants::MSG_RESULT_DIVIDER << recordNumber << Constants::MSG_RECORD_SUFFIX;

                for (const auto& attr : child->getAttributes())
                {
                    std::cout << "  " << std::left << std::setw(15) << attr.first << " : " << attr.second << Logger::printNextLine();
                }

                for (tinyxml2::XMLElement* subchild = child->FirstChildElement();
                     subchild != nullptr;
                     subchild = subchild->NextSiblingElement())
                {
                    const char* text = subchild->GetText();
                    std::cout << "  " << std::left << std::setw(15) << subchild->Name() << " : " << (text ? text : "") << Logger::printNextLine();
                }

                std::cout << Logger::printNextLine();
                ++recordNumber;
            }
        }

        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_PARSE_COMPLETE;
        std::cout << Constants::MSG_RESULT_BORDER;
    }
    catch (const std::exception& error)
    {
        Logger::printMessage(Constants::MSG_XML_READ_ERROR + std::string(error.what()) + Logger::printNextLine());
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}
