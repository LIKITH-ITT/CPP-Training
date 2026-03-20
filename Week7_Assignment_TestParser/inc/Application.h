#ifndef APPLICATION_H
#define APPLICATION_H

#include "IParser.h"
#include "Logger.h"

class Application
{
public:
    Application();
    Application(IParser* parser, const std::string& filePath);
    ~Application();

    void run();
    void handleParsing();

private:
    IParser* _parser;
    std::string _filePath;
};

#endif
