#include "Application.h"
#include "Utility.h"
#include "ParserFactory.h"
#include "Constants.h"

Application::Application(): _parser(nullptr){}

Application::~Application()
{
    delete _parser;
    _parser = nullptr;
}

void Application::run()
{
    Logger::printMessage(Constants::MSG_WELCOME);

    while (true)
    {
        std::string filePath = Utility::getFilePath();

        _parser = ParserFactory::create(filePath);

        if (_parser == nullptr)
        {
            Logger::printMessage(Constants::MSG_UNSUPPORTED_TYPE);
        }
        else if (!_parser->parseFile(filePath))
        {
            Logger::printMessage(Constants::MSG_PARSE_FAILED);
        }
        else
        {
            Logger::printMessage(Constants::MSG_PARSE_SUCCESS);

            if (!_parser->showParsedFile())
            {
                Logger::printMessage(Constants::MSG_DISPLAY_FAILED);
            }
        }

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
