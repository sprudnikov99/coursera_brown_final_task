#include<sstream>

#include "bus_manager.h"

std::stringstream test_stream{
        "13\n"
        "Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino\n"
        "Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka\n"
        "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
        "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
        "Stop Rasskazovka: 55.632761, 37.333324\n"
        "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam\n"
        "Stop Biryusinka: 55.581065, 37.64839, 750m to Universam\n"
        "Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n"
        "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya\n"
        "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye\n"
        "Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n"
        "Stop Rossoshanskaya ulitsa: 55.595579, 37.605757\n"
        "Stop Prazhskaya: 55.611678, 37.603831\n"
        "6\n"
        "Bus 256\n"
        "Bus 750\n"
        "Bus 751\n"
        "Stop Samara\n"
        "Stop Prazhskaya\n"
        "Stop Biryulyovo Zapadnoye"
};
int main() {

    auto manager = bus_manager::BusManager();

    size_t query_num;
    test_stream >> query_num;
//    cout << "query_num " << query_num << endl;
    manager.ReadAddQueries(test_stream, query_num);

    manager.ConnectStations();

    test_stream >> query_num;
    manager.ProcessSearchQueries(test_stream, query_num);
    return 0;
}
