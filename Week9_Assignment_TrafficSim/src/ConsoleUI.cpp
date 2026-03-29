#include "ConsoleUI.h"
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

void ConsoleUI::showWelcome()
{
    print("\n" + UI::HEADER + "\n" + UI::SEPARATOR + "\n");
}

void ConsoleUI::showIntersection()
{
    std::ostringstream oss;
    oss << "\n"
        << "            [ NORTH ]\n"
        << "               | |\n"
        << "               | |\n"
        << "[ WEST ]---+-------+---[ EAST ]\n"
        << "               | |\n"
        << "               | |\n"
        << "            [ SOUTH ]\n"
        << "\n" << UI::SEPARATOR << "\n";
    print(oss.str());
}

LaneId ConsoleUI::promptLane(const std::string& prompt)
{
    LaneId result = LaneId::NORTH;
    bool valid = false;

    while (!valid && std::cin.good())
    {
        std::lock_guard<std::mutex> lock(printMutex_);
        std::cout << prompt << std::flush;

        std::string line;
        std::getline(std::cin, line);

        if (!std::cin.good()) 
        break;

        char c = '\0';
        valid = parseLaneInput(line, c);

        if (valid)
        {
            result = parseLane(c);
        }
        else
        {
            std::cout << "  Invalid input. Please enter N, S, E, W or north, south, east, west.\n";
        }
    }

    return result;
}

void ConsoleUI::showStatus(const QueryResult& r)
{
    std::ostringstream oss;

    oss << "\n" << UI::SEPARATOR << "\n";
    oss << "  From      : " << laneToString(r.fromLane) << "\n";
    oss << "  To        : " << laneToString(r.toLane)   << "\n";
    oss << "  Move type : " << moveToString(r.moveType) << "\n";
    oss << UI::SEPARATOR << "\n";

    if (r.moveType == MoveType::FREE_MOVE)
    {
        oss << "  " << UI::STATUS_FREE << "Free left-turn — no wait required.\n";
    }
    else if (r.laneState == LightState::GREEN)
    {
        oss << "  " << UI::STATUS_GREEN << "Your lane is GREEN. Go now!\n";
        oss << "  Green for     : " << r.secondsRemaining << " more second(s).\n";
        oss << "  Traffic delay : " << r.estDelaySecs << "s (" << r.carsInside << " cars)\n";
        oss << "  Cars inside   : " << r.carsInside << " / " << Config::MAX_CARS << "\n";
    }
    else
    {
        oss << "  " << UI::STATUS_RED << "Your lane is RED.\n";
        oss << "  Currently green : " << laneToString(r.currentGreen) << "\n";
        oss << "  Signal wait     : " << r.waitSeconds << " second(s)\n";
        oss << "  Traffic delay   : " << r.estDelaySecs << " second(s) (" << r.carsInside << " cars)\n";
        oss << "  Total wait      : " << (r.waitSeconds + r.estDelaySecs) << " second(s)\n";
        oss << "  Cars inside     : " << r.carsInside << " / " << Config::MAX_CARS << "\n";
    }

    oss << UI::SEPARATOR << "\n";
    print(oss.str());
}

bool ConsoleUI::askRepeat()
{
    bool result = false;
    bool valid = false;

    while (!valid && std::cin.good())
    {
        std::lock_guard<std::mutex> lock(printMutex_);
        std::cout << "\n  Query again? [Y/N]: " << std::flush;

        std::string line;
        std::getline(std::cin, line);

        if (!std::cin.good()) { break; }

        valid = parseYesNoInput(line, result);

        if (!valid)
        {
            std::cout << "  Invalid input. Please enter Y, N, yes or no.\n";
        }
    }

    return result;
}

void ConsoleUI::print(const std::string& msg) const
{
    std::lock_guard<std::mutex> lock(printMutex_);
    std::cout << msg << std::flush;
}

LaneId ConsoleUI::parseLane(char c) const
{
    LaneId result = LaneId::NORTH;

    if (c == 'S')
    result = LaneId::SOUTH;
    else if (c == 'E')
    result = LaneId::EAST;
    else if (c == 'W')
    result = LaneId::WEST;

    return result;
}

bool ConsoleUI::parseLaneInput(const std::string& line, char& c) const
{
    std::size_t first = line.find_first_not_of(" \t\n");
    std::size_t last = line.find_last_not_of(" \t\n");

    bool result = false;

    if (first != std::string::npos)
    {
        std::string token = line.substr(first, last - first + 1);

        std::string lower = token;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch){ return std::tolower(ch); });

        if (lower == "n" || lower == "north")
        c = 'N'; result = true;
        else if (lower == "s" || lower == "south")
        c = 'S'; result = true;
        else if (lower == "e" || lower == "east")
        c = 'E'; result = true;
        else if (lower == "w" || lower == "west")
        c = 'W'; result = true;
    }

    return result;
}

bool ConsoleUI::parseYesNoInput(const std::string& line, bool& value) const
{
    std::size_t first = line.find_first_not_of(" \t\n");
    std::size_t last = line.find_last_not_of(" \t\n");

    bool result = false;

    if (first != std::string::npos)
    {
        std::string token = line.substr(first, last - first + 1);

        std::string lower = token;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch){ return std::tolower(ch); });

        if (lower == "y" || lower == "yes")
        value = true; result = true;
        else if (lower == "n" || lower == "no")
        value = false; result = true;
    }

    return result;
}

std::string ConsoleUI::laneToString(LaneId id) const
{
    std::string result;

    if (id == LaneId::NORTH)
    result = "NORTH";
    else if (id == LaneId::SOUTH)
    result = "SOUTH";
    else if (id == LaneId::EAST)
    result = "EAST";
    else
    result = "WEST";

    return result;
}

std::string ConsoleUI::moveToString(MoveType m) const
{
    std::string result;

    if (m == MoveType::STRAIGHT)
    result = "Straight";
    else if (m == MoveType::LEFT_TURN)
    result = "Left turn";
    else if (m == MoveType::RIGHT_TURN)
    result = "Right turn";
    else if (m == MoveType::U_TURN)
    result = "U-turn";
    else
    result = "Free move";

    return result;
}

std::string ConsoleUI::stateToString(LightState s) const
{
    std::string result;

    if (s == LightState::GREEN)
    result = "GREEN";
    else if (s == LightState::YELLOW)
    result = "YELLOW";
    else
    result = "RED";

    return result;
}