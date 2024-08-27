#include <sstream>

#include "Tests/test_runner.h"
#include "Database.h"
#include "InputStopCommand.h"
#include "InputBusCommand.h"
#include "OutputBusCommand.h"
#include "OutputStopCommand.h"
#include "RequestHandler.h"
#include "RequestHandlerTests.h"

using namespace std;


//void RequestHandlerTest1()
//{
//  stringstream in;
//  in << "10\n"
//    "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
//    "Stop Marushkino: 55.595884, 37.209755\n"
//    "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
//    "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
//    "Stop Rasskazovka: 55.632761, 37.333324\n"
//    "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
//    "Stop Biryusinka: 55.581065, 37.64839\n"
//    "Stop Universam: 55.587655, 37.645687\n"
//    "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
//    "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
//    "3\n"
//    "Bus 256\n"
//    "Bus 750\n"
//    "Bus 751";
//
//  DatabaseShp db = make_shared<Database>();
//  auto inputBusCommand = make_shared<InputBusCommand>(db);
//  auto inputStopCommand = make_shared<InputStopCommand>(db);
//  auto outputBusCommand = make_shared<OutputBusCommand>(db);
//
//  stringstream out;
//  RequestHandler requestHandler(in, out);
//  requestHandler.RegisterInputCommand(inputBusCommand);
//  requestHandler.RegisterInputCommand(inputStopCommand);
//  requestHandler.RegisterOutputCommand(outputBusCommand);
//  requestHandler.Run();
//
//  string expectedOut = "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\n"
//    "Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length\n"
//    "Bus 751: not found\n";
//  string outStr = out.str();
//  ASSERT_EQUAL(outStr, expectedOut);
//}
//
//void RequestHandlerTest2()
//{
//  stringstream in;
//  in << "4\n"
//    "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
//    "Stop Marushkino: 55.595884, 37.209755\n"
//    "Bus bus a: Tolstopaltsevo - Marushkino - Rasskazovka\n"
//    "Stop Rasskazovka: 55.632761, 37.333324\n"
//    "1\n"
//    "Bus bus a\n";
//
//  DatabaseShp db = make_shared<Database>();
//  auto inputBusCommand = make_shared<InputBusCommand>(db);
//  auto inputStopCommand = make_shared<InputStopCommand>(db);
//  auto outputBusCommand = make_shared<OutputBusCommand>(db);
//
//  stringstream out;
//
//  RequestHandler requestHandler(in, out);
//  requestHandler.RegisterInputCommand(inputBusCommand);
//  requestHandler.RegisterInputCommand(inputStopCommand);
//  requestHandler.RegisterOutputCommand(outputBusCommand);
//  requestHandler.Run();
//
//  string expectedOut = "Bus bus a: 5 stops on route, 3 unique stops, 20939.5 route length\n";
//  string outStr = out.str();
//  ASSERT_EQUAL(outStr, expectedOut);
//}

void RequestHandlerTest3()
{
    stringstream in;
    in << "13\n"
        "Stop Tolstopaltsevo : 55.611087, 37.20829, 3900m to Marushkino\n"
        "Stop Marushkino : 55.595884, 37.209755, 9900m to Rasskazovka\n"
        "Bus 256 : Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
        "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
        "Stop Rasskazovka : 55.632761, 37.333324\n"
        "Stop Biryulyovo Zapadnoye : 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam\n"
        "Stop Biryusinka : 55.581065, 37.64839, 750m to Universam\n"
        "Stop Universam : 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n"
        "Stop Biryulyovo Tovarnaya : 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya\n"
        "Stop Biryulyovo Passazhirskaya : 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye\n"
        "Bus 828 : Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n"
        "Stop Rossoshanskaya ulitsa : 55.595579, 37.605757\n"
        "Stop Prazhskaya : 55.611678, 37.603831\n"
        "6\n"
        "Bus 256\n"
        "Bus 750\n"
        "Bus 751\n"
        "Stop Samara\n"
        "Stop Prazhskaya\n"
        "Stop Biryulyovo Zapadnoye\n";

    DatabaseShp db = make_shared<Database>();
    auto inputBusCommand = make_shared<InputBusCommand>(db);
    auto inputStopCommand = make_shared<InputStopCommand>(db);
    auto outputBusCommand = make_shared<OutputBusCommand>(db);
    auto outputStopCommand = make_shared<OutputStopCommand>(db);

    stringstream out;

    RequestHandler requestHandler(in, out);
    requestHandler.RegisterInputCommand(inputBusCommand);
    requestHandler.RegisterInputCommand(inputStopCommand);
    requestHandler.RegisterOutputCommand(outputBusCommand);
    requestHandler.RegisterOutputCommand(outputStopCommand);
    requestHandler.Run();

    string expectedOut = "Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.361239 curvature\n"
        "Bus 750: 5 stops on route, 3 unique stops, 27600 route length, 1.318084 curvature\n"
        "Bus 751: not found\n"
        "Stop Samara: not found\n"
        "Stop Prazhskaya: no buses\n"
        "Stop Biryulyovo Zapadnoye: buses 256 828\n";
    string outStr = out.str();
    ASSERT_EQUAL(outStr, expectedOut);
}