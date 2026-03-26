#include "Simulation.h"
#include "Intersection.h"
#include "Constants.h"
#include <thread>
#include <chrono>

Simulation::Simulation(Intersection* intersection)
    : intersection_(intersection)
    , ui_(nullptr)
    , query_(intersection)
    , running_(false)
    , stopped_(false)
{
}

void Simulation::setUI(IConsoleUI* ui)
{
    ui_ = ui;
}

void Simulation::run()
{
    running_ = true;
    stopped_ = false;

    ui_->showWelcome();
    ui_->showIntersection();

    // Run the query loop synchronously on the calling thread.
    // The intersection controller runs on its own thread (started externally).
    runQueryLoop();

    stopped_ = true;
}

void Simulation::stop()
{
    running_ = false;
}

// ── Private ───────────────────────────────────────────────────────────────────

void Simulation::runQueryLoop()
{
    bool keepGoing = true;

    while (running_ && keepGoing)
    {
        LaneId from = ui_->promptLane(UI::PROMPT_FROM);
        LaneId to   = ui_->promptLane(UI::PROMPT_TO);

        QueryResult result = query_.resolve(from, to);
        ui_->showStatus(result);

        keepGoing = ui_->askRepeat();
    }
}