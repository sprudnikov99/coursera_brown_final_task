#include<iostream>
#include<unordered_map>
#include<array>
#include<optional>
#include<set>

#include "common.h"

namespace cache
{
    static constexpr double kRouteInitValue = -1.0;

    class Cache
    {
    public:
        Cache();

        [[nodiscard]] std::optional<std::size_t> GetUniqueStops(BusId bus_id) const;
        void UpdateUniqueStops(BusId bus_id, size_t value);

        [[nodiscard]] std::optional<double> GetBusRouteLength(BusId bus_id) const;
        void UpdateBusRouteLength(BusId bus_id, double value);

        [[nodiscard]] std::optional<double> GetTwoStopsDistance(size_t stop_from, size_t stop_to) const;
        void UpdateTwoStopsDistance(size_t stop_from, size_t stop_to, double value);

        [[nodiscard]] std::optional<std::set<BusId>> GetUniqueBusesWithStop(size_t stop_id) const;
        void UpdateUniqueBusesWithStop(size_t stop_id, BusId bus_id);

    private:
        std::array<std::array<double, kMaxStopsOnRouteNum>, kMaxStopsOnRouteNum> m_routes_cache = {};
        std::array<std::set<BusId>, kMaxStopsOnRouteNum> m_unique_buses_with_stop = {};
        std::unordered_map<BusId, std::size_t> m_unique_cache = {};
        std::unordered_map<BusId, double> m_bus_length_cache = {};
    };
}

