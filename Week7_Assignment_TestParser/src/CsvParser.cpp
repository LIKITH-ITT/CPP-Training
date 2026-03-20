#include "CsvParser.h"
#include "Logger.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool CsvParser::parseFile(const std::string& filePath) {
    bool isParsedSuccessfully = true;
    _filePath = filePath;
    std::ifstream file(filePath);

    try
    {
        if (!file.is_open())
        {
            Logger::printMessage(Constants::MSG_CSV_READ_FAIL + filePath + Logger::printNextLine());
            isParsedSuccessfully = false;
        }
        else if (file.peek() == std::ifstream::traits_type::eof())
        {
            Logger::printMessage(Constants::MSG_CSV_EMPTY_FILE + filePath + Logger::printNextLine());
            isParsedSuccessfully = false;
        }
        else
        {
            file.close();
            _csvDocument = rapidcsv::Document(filePath);
        }
    }
    catch (const std::exception& error)
    {
        Logger::printMessage(Constants::MSG_CSV_READ_FAIL + std::string(error.what()) + Logger::printNextLine());
        isParsedSuccessfully = false;
    }

    return isParsedSuccessfully;
}

bool CsvParser::showParsedFile() {
    bool isDisplayedSuccessfully = true;

    try
    {
        int totalRows = _csvDocument.GetRowCount();
        int totalColumns = _csvDocument.GetColumnCount();

        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_RESULT_FILE << _filePath;
        std::cout << Constants::MSG_RESULT_FORMAT << Constants::LABEL_CSV;
        std::cout << Constants::MSG_RESULT_RECORDS << totalRows;
        std::cout << Constants::MSG_RESULT_BORDER;

        if (totalRows == 0)
        {
            std::cout << Constants::MSG_NO_RECORDS;
        }
        else
        {
            for (int rowIndex = 0; rowIndex < totalRows; ++rowIndex)
            {
                std::cout << Constants::MSG_RESULT_DIVIDER << (rowIndex + 1) << Constants::MSG_RECORD_SUFFIX;

                for (int colIndex = 0; colIndex < totalColumns; ++colIndex)
                {
                    std::string header = _csvDocument.GetColumnName(colIndex);
                    std::string value = _csvDocument.GetCell<std::string>(colIndex, rowIndex);
                    std::cout << "  " << std::left << std::setw(15) << header << " : " << value << Logger::printNextLine();
                }

                std::cout << Logger::printNextLine();
            }
        }

        std::cout << Constants::MSG_RESULT_BORDER;
        std::cout << Constants::MSG_PARSE_COMPLETE;
        std::cout << Constants::MSG_RESULT_BORDER;
    }
    catch (const std::exception& error)
    {
        Logger::printMessage(Constants::MSG_CSV_OUT_OF_RANGE + std::string(error.what()) + Logger::printNextLine());
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}