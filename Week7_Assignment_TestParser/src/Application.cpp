#include "Application.h"
#include "Utility.h"
#include "ParserFactory.h"
#include "Constants.h"

Application::Application()
    : _parser(nullptr), _filePath("")
{
}

Application::Application(IParser* parser, const std::string& filePath)
    : _parser(parser), _filePath(filePath)
{
}

Application::~Application()
{
    delete _parser;
    _parser = nullptr;
}

void Application::handleParsing()
{
    if (_parser == nullptr)
    {
        Logger::printMessage(Constants::MSG_UNSUPPORTED_TYPE);
        return;
    }

    if (!_parser->parseFile(_filePath))
    {
        Logger::printMessage(Constants::MSG_PARSE_FAILED);
        return;
    }

    Logger::printMessage(Constants::MSG_PARSE_SUCCESS);

    if (!_parser->showParsedFile())
    {
        Logger::printMessage(Constants::MSG_DISPLAY_FAILED);
    }
}

void Application::run()
{
    Logger::printMessage(Constants::MSG_WELCOME);
    while (true)
    {
        _filePath = Utility::getFilePath();
        _parser   = ParserFactory::create(_filePath);

        handleParsing();  
        delete _parser;
        _parser = nullptr;

        char choice = Utility::getUserChoice();
        if (choice == Constants::CHOICE_NO || choice == Constants::CHOICE_NO_CAP)
        {
            Logger::printMessage(Constants::MSG_EXITING_PROGRAM);
            break;
        }
    }
}
