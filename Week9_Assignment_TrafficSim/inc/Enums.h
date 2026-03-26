#pragma once

enum class LightState
{
    RED,
    YELLOW,
    GREEN
};

enum class LaneId
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

enum class MoveType
{
    STRAIGHT,
    LEFT_TURN,
    RIGHT_TURN,
    U_TURN,
    FREE_MOVE
};
