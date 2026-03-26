#include "QueryEngine.h"
#include "Intersection.h"
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
    ILane* lane = intersection_->getLane(from);

    LightState laneState = (phase.currentGreen == from) ? LightState::GREEN : LightState::RED;

    MoveType move = calcMoveType(from, to);
    bool free = isFreeMove(from, to, phase.currentGreen);
    int waitSecs = calcWait(from);

    if (free)
    {
        move = MoveType::FREE_MOVE;
        laneState = LightState::GREEN;
        waitSecs = 0;
    }

    int carsInside = lane->getCarsInside();
    int estDelay = 0;
    if (laneState == LightState::GREEN && carsInside >= Config::MAX_CARS)
    {
        estDelay = Timing::CAR_CROSS_DURATION;
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
    result.estDelaySecs = estDelay;
    return result;
}

MoveType QueryEngine::calcMoveType(LaneId from, LaneId to) const
{
    int fromIndex = laneIndex(from);
    int toIndex = laneIndex(to);
    int delta = (toIndex - fromIndex + Config::LANE_COUNT) % Config::LANE_COUNT;

    MoveType result;
    if (delta == 0) { result = MoveType::U_TURN;     }
    else if (delta == 1) { result = MoveType::LEFT_TURN;  }
    else if (delta == 2) { result = MoveType::STRAIGHT;   }
    else { result = MoveType::RIGHT_TURN; }

    return result;
}

int QueryEngine::calcWait(LaneId id) const
{
    PhaseInfo phase = intersection_->getPhaseInfo();

    int result = 0;

    if (phase.currentGreen != id)
    {
        int timeLeftInCurrent = phase.secondsRemaining + Timing::YELLOW_DURATION;

        int greenIndex = laneIndex(phase.currentGreen);
        int targetIndex = laneIndex(id);
        int steps = (targetIndex - greenIndex + Config::LANE_COUNT) % Config::LANE_COUNT;

        int fullPhase = Timing::GREEN_DURATION + Timing::YELLOW_DURATION;

        result = timeLeftInCurrent + (steps - 1) * fullPhase;
    }

    return result;
}

bool QueryEngine::isFreeMove(LaneId from, LaneId to, LaneId green) const
{
    MoveType move = calcMoveType(from, to);
    return move == MoveType::LEFT_TURN;
}
