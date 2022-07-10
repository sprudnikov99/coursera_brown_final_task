#include "cache.h"


namespace cache{

    Cache::Cache()
    {
        m_direct_routes_from_to.assign(kMaxAddQueriesNum, std::vector<double>(kMaxAddQueriesNum, kRouteInitValue));

        m_real_routes_from_to.assign(kMaxAddQueriesNum, std::vector<size_t>(kMaxAddQueriesNum, kRealRouteInitValue));

        m_unique_cache.reserve(kMaxAddQueriesNum);
        m_bus_direct_length_cache.reserve(kMaxAddQueriesNum);
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

    std::optional<size_t> Cache::GetBusRealRouteLength(BusId bus_id)
    {
        const auto it = m_bus_real_length_cache.find(bus_id);

        if(it != m_bus_real_length_cache.end())
        {
            return it->second;
        }

        return std::nullopt;
    }

    void Cache::UpdateBusRealRouteLength(BusId bus_id, double value)
    {
        m_bus_real_length_cache[bus_id] = value;
    }

    std::optional<double> Cache::GetBusDirectRouteLength(BusId bus_id) const
    {
        const auto it = m_bus_direct_length_cache.find(bus_id);

        if(it != m_bus_direct_length_cache.end())
        {
            return it->second;
        }

        return std::nullopt;
    }

    void Cache::UpdateBusDirectRouteLength(BusId bus_id, double value)
    {
        m_bus_direct_length_cache[bus_id] = value;
    }


    std::optional<size_t> Cache::GetTwoStopsRealDistance(size_t stop_from, size_t stop_to)
    {
        const auto distance = m_real_routes_from_to[stop_from][stop_to];
        if(distance != kRealRouteInitValue)
        {
            return distance;
        }

        const auto reversed_distance = m_real_routes_from_to[stop_to][stop_from];

        if(reversed_distance != kRealRouteInitValue)
        {
            throw std::runtime_error("Exception from GetTwoStopsRealDistance. Real distance between two stops was not determined: "
                                     + std::to_string(stop_from) + string(" to ") + std::to_string(stop_to));
        }

        m_real_routes_from_to[stop_from][stop_to] = reversed_distance;
        return reversed_distance;
    }

    void Cache::UpdateTwoStopsRealDistance(size_t stop_from, size_t stop_to, size_t value)
    {
        if(value < 0)
        {
            throw std::runtime_error("Exception from UpdateTwoStopsDirectDistance. Distance between two stops cannot be negative: "
                                     + std::to_string(value));
        }
        m_real_routes_from_to[stop_from][stop_to] = value;
    }


    std::optional<double> Cache::GetTwoStopsDirectDistance(size_t stop_from, size_t stop_to) const
    {
        const auto& distance = m_direct_routes_from_to[stop_from][stop_to];
        if(distance > kRouteInitValue)
        {
            return distance;
        }

        return std::nullopt;
    }

    void Cache::UpdateTwoStopsDirectDistance(size_t stop_from, size_t stop_to, double value)
    {
        if(value < 0.0)
        {
            throw std::runtime_error("Exception from UpdateTwoStopsDirectDistance. Distance between two stops cannot be negative: "
            + std::to_string(value));
        }
        m_direct_routes_from_to[stop_from][stop_to] = value;
        m_direct_routes_from_to[stop_to][stop_from] = value;
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