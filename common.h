#pragma once

#include<iostream>
#include <stdexcept>

#include<string>
#include<vector>
#include<memory>

using namespace std;

static constexpr double kPi = 3.1415926535;
static constexpr size_t kEarthR = 6371'000;

static constexpr size_t kMaxStopsOnRouteNum = 100;
static constexpr size_t kMaxRealStopsConnectionNum = 100;
static constexpr size_t kMaxAddQueriesNum = 2000;
static constexpr size_t kMaxRealDistance = 1'000'000;

struct Stop
{
    size_t id;
    std::string name;
    double latitude = -1.0;
    double longitude = -1.0;
};

using StopPtr = shared_ptr<Stop>;

using BusId = std::size_t;
using BusId = std::size_t;
struct Bus
{
    BusId number;
    std::vector<StopPtr> stops;
    // if not cycled,
    // then route = m_stops + reversed(m_stops)
    bool cycled = false;
};

enum class EQueryType : size_t
{
    EUnknown,
    EBusInfo,
    EStopInfo
};

struct Query
{
    EQueryType type;
    BusId bus_id;
    string stop_name;
};
