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
        string_view RemoveBoundarySpaces(string_view& view)
        {
            const auto first_pos = view.find_first_not_of(' ');
            const auto last_pos = view.find_last_not_of(' ');

            return view.substr(first_pos, last_pos - first_pos + 1);
        }

        std::vector<string> RetrieveStationsByDelim(string_view&& view, const char delim)
        {
            std::vector<string> result;

            auto pos = view.find(delim);
            while(pos != string::npos)
            {
                auto item = view.substr(0, pos);
                item = RemoveBoundarySpaces(item);
                result.emplace_back(string(item));

                view.remove_prefix(pos + 1);
                pos = view.find(delim);
            }

            auto item = RemoveBoundarySpaces(view);
            result.emplace_back(string(item));

            return result;
        }

        void ParseBusValue(Bus& bus, string&& value)
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
            bus.stop_names = RetrieveStationsByDelim(string_view(value), delim);
        }

        std::string ReadUntil(std::istream &input, const char delim) {
            int security_counter = 30'000;

            auto result = std::string{};

            char ch;
            while (security_counter) {
                ch = input.get();
                if (ch == delim || input.eof()) {
                    break;
                } else {
                    result.push_back(ch);
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

        double CalculateRouteLength(const vector<StopPtr>& stops, cache::Cache& cache)
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
                const auto cache_distance = cache.GetTwoStopsDistance(from->id, to->id);

                if(cache_distance.has_value())
                {
                    total_distance += cache_distance.value();
//                    cout << "Get distance from "<< from->id <<": " << from->name << " <-> " << to->id <<": " << to->name << " from cache : " << cache_distance.value() << endl;
                    continue;
                }

                const auto calculated_distance = CalculateTwoStopsDistance(from, to);

//                cout << "Calculate distance from "<< from->id <<": " << from->name << " <-> " << to->id <<": " << to->name << "  distanse " << calculated_distance << endl;

                cache.UpdateTwoStopsDistance(from->id, to->id, calculated_distance);

                total_distance += calculated_distance;
            }

            return total_distance;
        }

        double GetRouteLength(const Bus& bus, cache::Cache& cache)
        {
            const auto cache_value = cache.GetBusRouteLength(bus.number);
            if(cache_value.has_value())
            {
//                cout << "GetRouteLength: Bus: " << bus.number << " Get value from cache: " << *cache_value << endl;
                return cache_value.value();
            }

//            cout << "bus stops num: " << bus.stops.size() << endl;
            auto calculated_value = CalculateRouteLength(bus.stops, cache);
            if(!bus.cycled)
            {
                calculated_value *= 2.0;
            }

//            cout << "GetRouteLength: Bus: " << bus.number << " calculate value: " << *cache_value << endl;

            cache.UpdateBusRouteLength(bus.number, calculated_value);

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
        << bus_info.length << " route length\n";
    }

    void BusManager::ReadBaseQueries(std::istream &input, size_t query_num) {
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


    void BusManager::ReadStop(std::istream &input) {
        Stop stop{};

        stop.name = ReadUntil(input, ':');

        input >> stop.latitude;
        input.ignore(1); //ignore ','
        input >> stop.longitude;

//        std::cout << "Stop " << stop.name << " la: " << stop.latitude << " lo: " << stop.longitude << " was added" <<std::endl;

        ReadUntil(input, '\n').size();

        AddStop(move(stop));
    }

    void BusManager::AddStop(Stop&& stop) {
        stop.id = m_stops_index.size();
        stop.latitude *= kPi / 180;
        stop.longitude *= kPi / 180;

        auto stop_ptr = make_shared<const Stop>(move(stop));
        auto name = stop_ptr->name;

        m_stops_index[std::move(name)] = std::move(stop_ptr);
    }

    void BusManager::AddBus(Bus&& bus) {
        m_busses[bus.number] = move(bus);
    }

    void BusManager::ReadBus(std::istream &input) {
        Bus bus;
        input >> bus.number;
        input.ignore(2); // ignore ':' and space
        string value = ReadUntil(input, '\n');
        // now bus filled with stop names and cycled
        ParseBusValue(bus, std::move(value));

//        string bus_stations{};
//        for(auto& station: bus.stop_names)
//        {
//            bus_stations += station;
//            bus_stations += ", ";
//        }
//        std::cout << "Bus " << bus.number << " stations: " << bus_stations << std::endl;

        AddBus(std::move(bus));
    }

    void BusManager::ConnectStations()
    {
        for(auto& [bus_id, bus]: m_busses)
        {
            bus.stops.reserve(bus.stop_names.size());
            for(const auto& stop_name: bus.stop_names)
            {
                const auto it = m_stops_index.find(stop_name);
                if(it != m_stops_index.end())
                {
                    bus.stops.push_back(it->second);
                }
                else
                {
                    throw std::runtime_error("Unknown in stops_index stop_name: " + stop_name);
                }
            }

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

        info.length = GetRouteLength(bus, m_cache);
//        cout << "GetBusInfo: bus: " << bus.number << " route_length: " << info.length << endl;

        info.unique = GetUniqueStops(bus, m_cache);
//        cout << "GetBusInfo: bus: " << bus.number << " unique_stops: " << info.unique << endl;

        return info;
    }


} // bus_manager