#pragma once

#include<iostream>
#include<unordered_map>

#include "common.h"
#include "cache.h"

namespace bus_manager
{
    struct BusInfo
    {
        size_t stops_num;
        size_t unique;
        double length;
    };

    class BusManager
    {
    public:
        BusManager();

        void ReadBaseQueries(std::istream& input, size_t query_num);
        void ProcessSearchQueries(std::istream& input, size_t query_num);


        void ConnectStations();
    private:
        void ReadBus(std::istream &input);
        void AddBus(Bus&& bus);

        void ReadStop(std::istream &input);
        void AddStop(Stop&& stop);


        void PrintBusInfo(BusId bus_id);
        BusInfo GetBusInfo(const Bus& bus);

        void PrintStopInfo(const string& stop_name);
    private:
        std::unordered_map<BusId, Bus> m_busses;
        std::unordered_map<string, StopPtr> m_stops_index;

        cache::Cache m_cache;
    };
}

