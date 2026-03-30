#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include "QueryResult.h"
#include "Enums.h"

class Intersection;

class QueryEngine
{
public:
    QueryEngine(Intersection* intersection);

    QueryResult resolve(LaneId from, LaneId to) const;

private:
    MoveType calcMoveType(LaneId from, LaneId to) const;
    int calcWait(LaneId id) const;
    bool isFreeMove(LaneId from, LaneId to) const;
    Intersection* intersection_;
};

#endif 
