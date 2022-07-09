#include "cache.h"


namespace cache{

    Cache::Cache()
    {
        for(auto& nested_arr: m_routes_cache)
        {
            nested_arr.fill(kRouteInitValue);
        }

        m_unique_cache.reserve(kMaxAddQueriesNum);
        m_bus_length_cache.reserve(kMaxAddQueriesNum);
    }

    std::optional<std::size_t> Cache::GetUniqueStops(BusId bus_id) const
    {
        const auto it = m_unique_cache.find(bus_id);

        if(it != m_unique_cache.end())
        {
            return it->second;
        }

        return std::nullopt;
    }

    void Cache::UpdateUniqueStops(BusId bus_id, size_t value)
    {
        m_unique_cache[bus_id] = value;
    }

    std::optional<double> Cache::GetBusRouteLength(BusId bus_id) const
    {
        const auto it = m_bus_length_cache.find(bus_id);

        if(it != m_bus_length_cache.end())
        {
            return it->second;
        }

        return std::nullopt;
    }

    void Cache::UpdateBusRouteLength(BusId bus_id, double value)
    {
        m_bus_length_cache[bus_id] = value;
    }

    std::optional<double> Cache::GetTwoStopsDistance(size_t stop_from, size_t stop_to) const
    {
        const auto& distance = m_routes_cache[stop_from][stop_to];
        if(distance >= 0.0)
        {
            return distance;
        }

        return std::nullopt;
    }

    void Cache::UpdateTwoStopsDistance(size_t stop_from, size_t stop_to, double value)
    {
        if(value < 0.0)
        {
            throw std::runtime_error("Exception from UpdateTwoStopsDistance. Distance between two stops cannot be negative: "
            + std::to_string(value));
        }
        m_routes_cache[stop_from][stop_to] = value;
        m_routes_cache[stop_to][stop_from] = value;
    }

    [[nodiscard]] std::optional<std::set<BusId>> Cache::GetUniqueBusesWithStop(size_t stop_id) const
    {
        if(stop_id > kMaxStopsOnRouteNum)
        {
            cout << "Stop id is too big: "<< stop_id << " max: "<< kMaxStopsOnRouteNum << endl;
            return std::nullopt;
        }

        return m_unique_buses_with_stop[stop_id];
    }

    void Cache::UpdateUniqueBusesWithStop(size_t stop_id, BusId bus_id)
    {
//        cout << "insert bus_id: " << bus_id << " to stop_id: "<< stop_id << endl;
        m_unique_buses_with_stop[stop_id].insert(bus_id);
    }
} // cache