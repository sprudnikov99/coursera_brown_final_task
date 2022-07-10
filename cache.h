#include<iostream>
#include<unordered_map>
#include<array>
#include<optional>
#include<set>

#include "common.h"

namespace cache
{
    static constexpr double kRouteInitValue = -1.0;
    static constexpr size_t kRealRouteInitValue = kMaxRealDistance + 1;

    class Cache
    {
    public:
        Cache();

        [[nodiscard]] std::optional<std::size_t> GetUniqueStops(BusId bus_id) const;
        void UpdateUniqueStops(BusId bus_id, size_t value);

        [[nodiscard]] std::optional<std::set<BusId>> GetUniqueBusesWithStop(size_t stop_id) const;
        void UpdateUniqueBusesWithStop(size_t stop_id, BusId bus_id);

        [[nodiscard]] std::optional<double> GetTwoStopsDirectDistance(size_t stop_from, size_t stop_to) const;
        void UpdateTwoStopsDirectDistance(size_t stop_from, size_t stop_to, double value);

        [[nodiscard]] std::optional<size_t> GetTwoStopsRealDistance(size_t stop_from, size_t stop_to);
        void UpdateTwoStopsRealDistance(size_t stop_from, size_t stop_to, size_t value);

        [[nodiscard]] std::optional<double> GetBusDirectRouteLength(BusId bus_id) const;
        void UpdateBusDirectRouteLength(BusId bus_id, double value);

        [[nodiscard]] std::optional<size_t> GetBusRealRouteLength(BusId bus_id);
        void UpdateBusRealRouteLength(BusId bus_id, double value);

    private:
        std::vector<std::vector<double>> m_direct_routes_from_to = {};
        std::vector<std::vector<size_t>> m_real_routes_from_to = {};
        std::array<std::set<BusId>, kMaxAddQueriesNum> m_unique_buses_with_stop = {};
        std::unordered_map<BusId, std::size_t> m_unique_cache = {};
        std::unordered_map<BusId, double> m_bus_direct_length_cache = {};
        std::unordered_map<BusId, double> m_bus_real_length_cache = {};
    };
}

