#ifndef APPLICATION_H
#define APPLICATION_H

#include "IParser.h"
#include "Logger.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    IParser*  _parser;
};

#endif
