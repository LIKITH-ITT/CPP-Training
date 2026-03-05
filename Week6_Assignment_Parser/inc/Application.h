#ifndef APPLICATION_H
#define APPLICATION_H

#include "IParser.h"

class Application {
    IParser* _parser;

public:
    Application();
    void run();
};

#endif