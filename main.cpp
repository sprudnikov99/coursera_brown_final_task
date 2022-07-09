#include<sstream>

#include "bus_manager.h"


//
//double CalculateTwoStopsDistance2(const StopPtr& p1, const StopPtr& p2)
//{
//
//    double tmp = sin((p2->longitude - p1->longitude)/2);
//    cout << "tmp: " << tmp <<endl;
//    const double under_root_right = cos(p1->latitude) * cos(p2->latitude) * (tmp * tmp);
//
//    tmp = sin((p2->latitude - p1->latitude)/2);
//    const double under_root = tmp * tmp + under_root_right;
//
//    const double d = 2 * kEarthR * asin(sqrt(under_root));
//
//    return d;
//}
//


//std::stringstream test_stream{
//        "4\n"
//        "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
//        "Stop Marushkino: 55.595884, 37.209755   \n"
//        "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
//        "Stop Rasskazovka: 55.632761, 37.333324  \n"
//        "1\n"
//        "Bus 750"
//};


// A
//std::stringstream test_stream{
//        "11\n"
//        "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
//        "Stop Marushkino: 55.595884, 37.209755\n"
//        "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye \n"
//        "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
//        "Bus 758: Tolstopaltsevo - Marushkino - Rasskazovka - Biryulyovo Tovarnaya - Rasskazovka\n"
//        "Stop Rasskazovka: 55.632761, 37.333324\n"
//        "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
//        "Stop Biryusinka: 55.581065, 37.64839\n"
//        "Stop Universam: 55.587655, 37.645687\n"
//        "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
//        "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
//        "5\n"
//        "Bus 256\n"
//        "Bus 750\n"
//        "Bus 750\n"
//        "Bus 758\n"
//        "Bus 751"
//};

// B
std::stringstream test_stream{
        "13\n"
        "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
        "Stop Marushkino: 55.595884, 37.209755\n"
        "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
        "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
        "Stop Rasskazovka: 55.632761, 37.333324\n"
        "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
        "Stop Biryusinka: 55.581065, 37.64839\n"
        "Stop Universam: 55.587655, 37.645687\n"
        "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
        "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
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
    manager.ReadBaseQueries(test_stream, query_num);

    manager.ConnectStations();

    test_stream >> query_num;
    manager.ProcessSearchQueries(test_stream, query_num);
    return 0;
}
