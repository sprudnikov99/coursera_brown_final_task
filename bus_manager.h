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
        size_t length;
        double curvature;
    };

    class BusManager
    {
    public:
        BusManager();

        void ReadAddQueries(std::istream& input, size_t query_num);
        void ProcessSearchQueries(std::istream& input, size_t query_num);


        void ConnectStations();
    private:
        void ReadBus(std::istream &input);
        void ParseBusValue(Bus& bus, string&& value);
        void AddBus(Bus&& bus);

        void ReadStop(std::istream &input);
        size_t AddStop(Stop&& stop);
        void ReadStopDistances(std::istream &input, size_t stop_id);


        void PrintBusInfo(BusId bus_id);
        BusInfo GetBusInfo(const Bus& bus);

        void PrintStopInfo(const string& stop_name);
    private:
        std::unordered_map<BusId, Bus> m_busses;
        std::unordered_map<string, StopPtr> m_stops_index;

        cache::Cache m_cache;
    };
}

