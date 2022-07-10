#include "bus_manager.h"

#include <iomanip>
#include <cmath>
#include <string_view>
#include <unordered_set>

static constexpr auto kBus = "Bus";
static constexpr auto kStop = "Stop";
static constexpr auto kCircleDelim = '>';
static constexpr auto kUsualDelim = '-';

namespace bus_manager{
    namespace{
        inline size_t GetNextStopId(const std::unordered_map<string, StopPtr>& stop_index)
        {
            return stop_index.size();
        }

        string_view RemoveBoundarySpaces(string_view& view)
        {
            const auto first_pos = view.find_first_not_of(' ');
            const auto last_pos = view.find_last_not_of(' ');

            return view.substr(first_pos, last_pos - first_pos + 1);
        }

        StopPtr GetOrCreateStop(std::unordered_map<string, StopPtr>& stop_index, std::string&& name)
        {
            const auto stop_it = stop_index.find(name);

            if(stop_it != stop_index.end())
            {
                return stop_it->second;
            }

            const size_t stop_id = GetNextStopId(stop_index);
            auto stop_ptr = std::make_shared<Stop>(Stop{stop_id, name});

            stop_index[std::move(name)] = stop_ptr;

            return stop_ptr;
        }

        std::vector<StopPtr> RetrieveStationsByDelim(std::unordered_map<string, StopPtr>& stop_index, string_view&& view, const char delim)
        {
            std::vector<StopPtr> result;

            auto pos = view.find(delim);
            while(pos != string::npos)
            {
                auto name = view.substr(0, pos);
                name = RemoveBoundarySpaces(name);

                result.emplace_back(GetOrCreateStop(stop_index, std::string(name)));

                view.remove_prefix(pos + 1);
                pos = view.find(delim);
            }

            const auto name = RemoveBoundarySpaces(view);
            result.emplace_back(GetOrCreateStop(stop_index, std::string(name)));

            return result;
        }

        std::string ReadUntil(std::istream &input, const char delim) {
            int security_counter = 30'000;

            auto result = std::string{};

            char ch;
            while (security_counter) {
                ch = input.peek();
                if (ch == delim || ch == '\n' || input.eof()) {
                    break;
                } else {
                    result.push_back(ch);
                    input.ignore(1);
                }
                security_counter--;
            }

            return result;
        }

        double CalculateTwoStopsDistance(const StopPtr& p1, const StopPtr& p2)
        {
            double tmp = sin((p2->longitude - p1->longitude)/2);
            const double under_root_right = cos(p1->latitude) * cos(p2->latitude) * (tmp * tmp);

            tmp = sin((p2->latitude - p1->latitude)/2);
            const double under_root = tmp * tmp + under_root_right;

            const double d = 2 * kEarthR * asin(sqrt(under_root));

            return d;
        }

        size_t CalculateRealRouteLength(const vector<StopPtr>& stops, cache::Cache& cache)
        {
            if(stops.size() <= 1)
            {
                return 0u;
            }

            size_t total_distance = 0;
            for(size_t i = 0; i < stops.size() - 1; i++)
            {
                const auto& from = stops[i];
                const auto& to = stops[i + 1];

                cout<< "Calculate route from: " << from->name << " to: " << to->name <<endl;
                const auto cache_distance = cache.GetTwoStopsRealDistance(from->id, to->id);

                if(cache_distance.has_value())
                {
                    total_distance += cache_distance.value();
//                    cout << "Get distance from "<< from->id <<": " << from->name << " <-> " << to->id <<": " << to->name << " from cache : " << cache_distance.value() << endl;
                    continue;
                }
                throw std::runtime_error("There is no information about real rout length between: " + from->name + string(" to ") + to->name);
            }

            return total_distance;
        }

        double CalculateDirectRouteLength(const vector<StopPtr>& stops, cache::Cache& cache)
        {
            if(stops.size() <= 1)
            {
                return 0.0;
            }

            double total_distance = 0.0;
            for(size_t i = 0; i < stops.size() - 1; i++)
            {
                const auto& from = stops[i];
                const auto& to = stops[i + 1];

//                cout<< "Calculate route from: " << from->name << " to: " << to->name <<endl;
                const auto cache_distance = cache.GetTwoStopsDirectDistance(from->id, to->id);

                if(cache_distance.has_value())
                {
                    total_distance += cache_distance.value();
//                    cout << "Get distance from "<< from->id <<": " << from->name << " <-> " << to->id <<": " << to->name << " from cache : " << cache_distance.value() << endl;
                    continue;
                }

                const auto calculated_distance = CalculateTwoStopsDistance(from, to);

//                cout << "Calculate distance from "<< from->id <<": " << from->name << " <-> " << to->id <<": " << to->name << "  distanse " << calculated_distance << endl;

                cache.UpdateTwoStopsDirectDistance(from->id, to->id, calculated_distance);

                total_distance += calculated_distance;
            }

            return total_distance;
        }

        size_t GetRealRouteLength(const Bus& bus, cache::Cache& cache)
        {
            const auto cache_value = cache.GetBusRealRouteLength(bus.number);
            if(cache_value.has_value())
            {
                cout << "GetDirectRouteLength: Bus: " << bus.number << " Get value from cache: " << *cache_value << endl;
                return cache_value.value();
            }

//            cout << "bus stops num: " << bus.stops.size() << endl;
            auto calculated_value = CalculateRealRouteLength(bus.stops, cache);
            if(!bus.cycled)
            {
                calculated_value *= 2;
            }

//            cout << "GetDirectRouteLength: Bus: " << bus.number << " calculate value: " << *cache_value << endl;

            cache.UpdateBusRealRouteLength(bus.number, calculated_value);

            return calculated_value;
        }

        double GetDirectRouteLength(const Bus& bus, cache::Cache& cache)
        {
            const auto cache_value = cache.GetBusDirectRouteLength(bus.number);
            if(cache_value.has_value())
            {
//                cout << "GetDirectRouteLength: Bus: " << bus.number << " Get value from cache: " << *cache_value << endl;
                return cache_value.value();
            }

//            cout << "bus stops num: " << bus.stops.size() << endl;
            auto calculated_value = CalculateDirectRouteLength(bus.stops, cache);
            if(!bus.cycled)
            {
                calculated_value *= 2.0;
            }

//            cout << "GetDirectRouteLength: Bus: " << bus.number << " calculate value: " << *cache_value << endl;

            cache.UpdateBusDirectRouteLength(bus.number, calculated_value);

            return calculated_value;
        }

        size_t CalculateUniqueStops(const Bus& bus)
        {
            std::unordered_set<size_t> unique_stops = {};
            for(const auto& stop: bus.stops)
            {
                unique_stops.insert(stop->id);
            }

            return unique_stops.size();
        }

        size_t GetUniqueStops(const Bus& bus, cache::Cache& cache)
        {
            const auto cache_value = cache.GetUniqueStops(bus.number);
            if(cache_value.has_value())
            {
//                cout << "GetUniqueStops: Bus: " << bus.number << " Get value from cache: " << *cache_value << endl;
                return cache_value.value();
            }

            const auto calculated_value = CalculateUniqueStops(bus);
//            cout << "GetUniqueStops: Bus: " << bus.number << " calculate value: " << *cache_value << endl;

            cache.UpdateUniqueStops(bus.number, calculated_value);

            return calculated_value;
        }

        std::vector<Query> ReadQueries(std::istream &input, size_t query_num) {
            std::vector<Query> queries = {};
            queries.reserve(query_num);

            string command = {};

            for(size_t i = 0; i < query_num; i++)
            {
                input >> command;

                EQueryType type = EQueryType::EUnknown;
                if(command == "Bus")
                {
                    type = EQueryType::EBusInfo;
                    size_t value;
                    input >> value;
                    queries.push_back({type, value});
                }
                else if(command == kStop)
                {
                    type = EQueryType::EStopInfo;
                    input.ignore(1);
                    string value = ReadUntil(input, '\n');
                    input.ignore(1);

                    queries.push_back({type, 0, std::move(value)});
                }

                if(type == EQueryType::EUnknown)
                {
                    throw std::runtime_error("Unknown search command: " + command);
                }
            }

            return queries;
        }


    } // namespace


    BusManager::BusManager()
    {
        m_stops_index.reserve(kMaxAddQueriesNum);
        m_busses.reserve(kMaxAddQueriesNum);
    }

    void BusManager::ProcessSearchQueries(std::istream &input, size_t query_num) {
        const auto queries = ReadQueries(input, query_num);

        for(const auto& query: queries)
        {
            switch (query.type) {
                case EQueryType::EBusInfo:
                    PrintBusInfo(query.bus_id);
                    break;
                case EQueryType::EStopInfo:
                    PrintStopInfo(query.stop_name);
                    break;
                case EQueryType::EUnknown:
                    throw std::runtime_error("Unknown query type while processing queries");
            }
        }
    }

    void BusManager::PrintStopInfo(const string& stop_name)
    {
        const auto it = m_stops_index.find(stop_name);
        if(it == m_stops_index.end())
        {
            cout << "Stop "<< stop_name << ": not found\n";
            return;
        }

        const auto stop_id = it->second->id;
        const auto unique_buses = m_cache.GetUniqueBusesWithStop(stop_id);
        if(!unique_buses.has_value())
        {
            cout << "Stop "<< stop_name << ": not found in cache\n";
            return;
        }

        if(unique_buses->empty())
        {
            cout << "Stop "<< stop_name << ": no buses\n";
            return;
        }

        cout << "Stop "<< stop_name << " : buses";
        for(const auto& bus_id: *unique_buses)
        {
            cout << " " << bus_id;
        }
        cout << "\n";
    }

    void BusManager::PrintBusInfo(BusId bus_id)
    {
        const auto& bus_it = m_busses.find(bus_id);
        if(bus_it == m_busses.end())
        {
            cout << "Bus "<< bus_id << ": not found\n";
            return;
        }

        const auto bus_info = GetBusInfo(bus_it->second);

        cout << std::setprecision(6) << "Bus " << bus_id << " : " << bus_info.stops_num
        << " stops on route, " << bus_info.unique << " unique stops, "
        << bus_info.length << " route length, " << bus_info.curvature << " curvature\n";
    }

    void BusManager::ReadAddQueries(std::istream &input, size_t query_num) {
        for(int i = 0; i < query_num; i++)
        {
            // process line
            std::string title;
            input >> title;
            input.ignore(1);

//            cout << "title: " << title <<endl;
            if(title == kBus)
            {
                ReadBus(input);
            }
            else if(title == kStop)
            {
                ReadStop(input);
            }
            else
            {
                throw std::runtime_error("Unknown title type: " + title);
            }
        }
    }

    void BusManager::ParseBusValue(Bus& bus, string&& value)
    {
        char delim;
        if(value.find(kCircleDelim) != string::npos)
        {
            bus.cycled = true;
            delim = kCircleDelim;
        }
        else
        {
            bus.cycled = false;
            delim = kUsualDelim;
        }
        bus.stops = RetrieveStationsByDelim(m_stops_index, string_view(value), delim);
    }

    void BusManager::ReadBus(std::istream &input) {
        Bus bus;
        input >> bus.number;
        input.ignore(2); // ignore ':' and space
        string value = ReadUntil(input, '\n');
        input.ignore(1);
        // now bus filled with stop names and cycled
        ParseBusValue(bus, std::move(value));

        AddBus(std::move(bus));
    }

    //TODO remove after test
    struct Distance
    {
        string to;
        size_t distance;
    };

    void BusManager::ReadStopDistances(std::istream &input, size_t stop_id)
    {
        if(input.eof() || input.get() != ',')
        {
            return;
        }

        vector<Distance> tests{};

        while(true)
        {
            size_t distance;
            input >> distance;

            input.ignore(5);

            auto destination_name = ReadUntil(input, ',');

            tests.push_back({destination_name, distance});
            auto destination_stop_ptr = GetOrCreateStop(m_stops_index, std::move(destination_name));

            m_cache.UpdateTwoStopsRealDistance(stop_id, destination_stop_ptr->id, distance);

            if(input.eof() || input.get() != ',')
            {
                break;
            }
        }

        for(auto tst: tests)
        {
            cout << "To: " << tst.to << " d: " << tst.distance << endl;
        }
        cout << endl;
    }

    void BusManager::ReadStop(std::istream &input) {
        Stop stop{};

        stop.name = ReadUntil(input, ':');
        input.ignore(1);

        input >> stop.latitude;
        input.ignore(1); //ignore ','
        input >> stop.longitude;

//        std::cout << "Stop " << stop.name << " la: " << stop.latitude << " lo: " << stop.longitude << " was added" <<std::endl;

        cout << endl << stop.name << endl;
        const auto stop_id = AddStop(move(stop));
        ReadStopDistances(input, stop_id);
    }

    size_t BusManager::AddStop(Stop&& stop) {
        static constexpr double kDelimiter = kPi / 180;

        auto stop_ptr = GetOrCreateStop(m_stops_index, std::move(stop.name));

        stop_ptr->latitude = stop.latitude * kDelimiter;
        stop_ptr->longitude = stop.longitude * kDelimiter;

        return stop_ptr->id;
    }

    void BusManager::AddBus(Bus&& bus) {
        m_busses[bus.number] = move(bus);
    }

    void BusManager::ConnectStations()
    {
        for(auto& [bus_id, bus]: m_busses)
        {
            for(const auto& stop: bus.stops)
            {
                m_cache.UpdateUniqueBusesWithStop(stop->id, bus.number);
            }
        }
    }

    BusInfo BusManager::GetBusInfo(const Bus& bus)
    {
        BusInfo info{};
        info.stops_num = bus.cycled ? bus.stops.size() : (bus.stops.size() * 2 - 1);
//        cout << "GetBusInfo: bus: " << bus.number << " stops_num: " << info.stops_num << endl;

        info.unique = GetUniqueStops(bus, m_cache);
//        cout << "GetBusInfo: bus: " << bus.number << " unique_stops: " << info.unique << endl;

        const auto direct_length = GetDirectRouteLength(bus, m_cache);
//        cout << "GetBusInfo: bus: " << bus.number << " direct_length: " << info.direct_length << endl;


        const auto real_length = GetRealRouteLength(bus, m_cache);
        info.length = real_length;
//        cout << "GetBusInfo: bus: " << bus.number << " real_length: " << info.direct_length << endl;

        info.curvature = static_cast<double>(real_length) / direct_length;
//        cout << "GetBusInfo: bus: " << bus.number << " curvature: " << info.curvature << endl;

        return info;
    }


} // bus_manager