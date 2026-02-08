#ifndef MENU_H
#define MENU_H

class Menu
{
private:
    bool isProgramRunning;

    void displayOptions() const;
    int getChoice();

public:
    Menu();

    void run();
};

#endif
