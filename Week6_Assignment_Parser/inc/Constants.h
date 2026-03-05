#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {

    constexpr char FULL_STOP      = '.';
    constexpr char CHOICE_YES     = 'y';
    constexpr char CHOICE_YES_CAP = 'Y';
    constexpr char CHOICE_NO      = 'n';
    constexpr char CHOICE_NO_CAP  = 'N';

    constexpr const char* FORMAT_JSON = "JSON";
    constexpr const char* FORMAT_CSV  = "CSV";
    constexpr const char* FORMAT_XML  = "XML";

    constexpr const char* MSG_WELCOME =
        "\n========================================\n"
        "       Welcome to File Parser App       \n"
        "========================================\n"
        "This app can parse the following formats:\n"
        "  1. JSON (.json)\n"
        "  2. CSV  (.csv)\n"
        "  3. XML  (.xml)\n"
        "\n----------------------------------------\n\n";

    constexpr const char* MSG_ENTER_FILE_PATH = "Enter the full file path: ";
    constexpr const char* MSG_CONTINUE        = "\nParse another file? (y/n): ";
    constexpr const char* MSG_INVALID_CHOICE  = "\nInvalid input. Please enter y or n: ";
    constexpr const char* MSG_EXITING_PROGRAM = "\nThank you for using the parser!\n";

    constexpr const char* MSG_EMPTY_PATH       = "File path cannot be empty. Try again.\n";
    constexpr const char* MSG_UNSUPPORTED_TYPE = "Unsupported file type. Supported: .json, .csv, .xml\n\n";
    constexpr const char* MSG_CHECK_PATH       = " Please check the path and try again.\n\n";

    const std::string MSG_FILE_NOT_FOUND = "File not found: ";

    constexpr const char* MSG_PARSE_SUCCESS  = "\nFile successfully parsed.\n";
    constexpr const char* MSG_PARSE_FAILED   = "\nParsing completed with errors.\n";
    constexpr const char* MSG_DISPLAY_FAILED = "\n***Error while displaying parsed data.***\n";

    constexpr const char* MSG_RESULT_BORDER  = "\n========================================\n";
    constexpr const char* MSG_RESULT_FILE    = "  File   : ";
    constexpr const char* MSG_RESULT_FORMAT  = "\n  Format : ";
    constexpr const char* MSG_RESULT_RECORDS = "\n  Records: ";
    constexpr const char* MSG_RESULT_DIVIDER = "\n--- Record ";
    constexpr const char* MSG_RECORD_SUFFIX  = " ---\n";
    constexpr const char* MSG_NO_RECORDS     = "  No records found.\n";
    constexpr const char* MSG_PARSE_COMPLETE = "  Parsing complete.";

    constexpr const char* LABEL_JSON = "JSON";
    constexpr const char* LABEL_XML = "XML";
    constexpr const char* LABEL_CSV = "CSV";

    const std::string MSG_JSON_EMPTY_FAIL    = "\n[JsonParser] Empty file: ";
    const std::string MSG_JSON_SYNTAX_ERROR = "\n[JsonParser] Invalid JSON syntax: ";
    const std::string MSG_JSON_TYPE_ERROR   = "\n[JsonParser] Type mismatch: ";
    const std::string MSG_JSON_KEY_ERROR    = "\n[JsonParser] Key not found: ";
    constexpr const char* MSG_JSON_BAD_STRUCT = "\n[JsonParser] Unsupported JSON structure. Expected array of objects.";

    const std::string MSG_CSV_READ_FAIL      = "[CsvParser] Could not read CSV file: ";
    constexpr const char* MSG_CSV_NO_HEADERS = "[CsvParser] CSV file has no headers.";
    const std::string MSG_CSV_OUT_OF_RANGE   = "[CsvParser] Out of range while reading CSV: ";
    const std::string MSG_CSV_EMPTY_FILE   = "[CsvParser] Empty file: ";


    const std::string MSG_XML_PARSE_FAIL     = "[XmlParser] Could not parse XML file: ";
    constexpr const char* MSG_XML_NO_ROOT    = "[XmlParser] XML file has no root element.";
    const std::string MSG_XML_READ_ERROR     = "[XmlParser] Error while reading XML: ";

}

#endif