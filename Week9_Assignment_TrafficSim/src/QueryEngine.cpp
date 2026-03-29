#include "QueryEngine.h"
#include "Intersection.h"
#include "ILane.h"
#include "Constants.h"

static int laneIndex(LaneId id)
{
    int result = 0;
    for (int i = 0; i < Config::LANE_COUNT; ++i)
    {
        if (Config::CYCLE_ORDER[i] == id)
        {
            result = i;
            break;
        }
    }
    return result;
}

QueryEngine::QueryEngine(Intersection* intersection) : intersection_(intersection)
{}

QueryResult QueryEngine::resolve(LaneId from, LaneId to) const
{
    PhaseInfo phase = intersection_->getPhaseInfo();

    LightState laneState;
    if (phase.currentGreen == from)
    {
        laneState = LightState::GREEN;
    }
    else
    {
        laneState = LightState::RED;
    }

    MoveType move = calcMoveType(from, to);
    bool free = isFreeMove(from, to);
    int waitSecs = calcWait(from);

    ILane* lane = intersection_->getLane(from);
    int carsInside = lane->getCarsInside();

    int estDelaySecs = carsInside * Timing::CAR_CROSS_DURATION;

    if (free)
    {
        move = MoveType::FREE_MOVE;
        laneState = LightState::GREEN;
        waitSecs = 0;
        estDelaySecs = 0;
    }

    QueryResult result;
    result.fromLane = from;
    result.toLane = to;
    result.moveType = move;
    result.currentGreen = phase.currentGreen;
    result.laneState = laneState;
    result.secondsRemaining = phase.secondsRemaining;
    result.waitSeconds = waitSecs;
    result.carsInside = carsInside;
    result.estDelaySecs = estDelaySecs;

    return result;
}

MoveType QueryEngine::calcMoveType(LaneId from, LaneId to) const
{
    int fromIdx = laneIndex(from);
    int toIdx = laneIndex(to);
    int delta = (toIdx - fromIdx + Config::LANE_COUNT) % Config::LANE_COUNT;

    MoveType result;
    if (delta == 0) 
    result = MoveType::U_TURN;
    else if (delta == 1) 
    result = MoveType::LEFT_TURN;
    else if (delta == 2) 
    result = MoveType::STRAIGHT;
    else 
    result = MoveType::RIGHT_TURN;

    return result;
}

int QueryEngine::calcWait(LaneId id) const
{
    PhaseInfo phase = intersection_->getPhaseInfo();

    int result = 0;

    if (phase.currentGreen != id)
    {
        int timeLeftInCurrent = phase.secondsRemaining + Timing::YELLOW_DURATION;

        int greenIdx = laneIndex(phase.currentGreen);
        int targetIdx = laneIndex(id);
        int steps = (targetIdx - greenIdx + Config::LANE_COUNT) % Config::LANE_COUNT;

        int fullPhase = Timing::GREEN_DURATION + Timing::YELLOW_DURATION;

        result = timeLeftInCurrent + (steps - 1) * fullPhase;
    }

    return result;
}

bool QueryEngine::isFreeMove(LaneId from, LaneId to) const
{
    MoveType move = calcMoveType(from, to);
    return (move == MoveType::LEFT_TURN);
}