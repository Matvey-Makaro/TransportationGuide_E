#include <string>
#include "test_runner.h"
#include "CmpUtils.h"
#include "Utiils.h"
#include "PathSearcherTests.h"
#include "PathSearcher.h"
#include "Database.h"
#include "Stop.h"
#include "Route.h"
#include "RoutingSettings.h"


void PathSearcherEmptyGraphTest()
{
  auto db = std::make_shared<Database>();
  constexpr int32_t busWaitTime = 5;
  constexpr double busVelocity = 33.3;
  RoutingSettings settings{ busWaitTime, busVelocity };
  PathSearcher pathSearcher;
  pathSearcher.Initialize(*db, settings);

  std::string fromStop("From stop");
  std::string toStop("To stop");
  auto path = pathSearcher.FindPath(fromStop, toStop);
  ASSERT(path == std::nullopt);
}

void PathSearcherTheSameBusStopTest()
{
  std::string biryulovoZapadnoyeName = "Biryulovo Zapadnoye";
  auto biryulovoZapadnoyeStop = std::make_shared<Stop>();
  {
    double latitude = 55.61108;
    double longitude = 37.20829;
    biryulovoZapadnoyeStop->name = biryulovoZapadnoyeName;
    biryulovoZapadnoyeStop->location = GeoPoint{ latitude, longitude };
  }
  
  std::string biryulovoTovarnayaName = "Biryulovo Tovarnaya";
  auto biryulovoTovarnayaStop = std::make_shared<Stop>();
  {
    double latitude = 54.61108;
    double longitude = 36.20829;
    biryulovoTovarnayaStop->name = biryulovoTovarnayaName;
    biryulovoTovarnayaStop->location = GeoPoint{ latitude, longitude };
  }
  
  std::string universamName = "Universam";
  auto universamStop = std::make_shared<Stop>();
  {
    double latitude = 53.61108;
    double longitude = 35.20829;
    universamStop->name = universamName;
    universamStop->location = GeoPoint{ latitude, longitude };
  }

  std::string prazskajaName = "Prazskaja";
  auto prazskajaStop = std::make_shared<Stop>();
  {
    double latitude = 52.61108;
    double longitude = 34.20829;
    prazskajaStop->name = prazskajaName;
    prazskajaStop->location = GeoPoint{ latitude, longitude };
  }

  double biryulovoZapadnoyeToBiryulovoTovarnayaDistance = 2600.;
  double biryulovoTovarnayaToUniversamDistance = 890.;
  double universamToBiryulovoTovarnayaDistance = 1380.;
  double universamToBiryulovoZapadnoyeDistance = 2500.;
  double universamToPrazskajaDistance = 4650.;

  std::string bus297Name = "297";
  auto bus297 = std::make_shared<Route>(bus297Name,
    StopNames{ biryulovoZapadnoyeName, biryulovoTovarnayaName, universamName, biryulovoZapadnoyeName },
    Route::Circular);

  std::string bus635Name("635");
  auto bus635 = std::make_shared<Route>(bus635Name,
    StopNames{ biryulovoTovarnayaName, universamName, prazskajaName },
    Route::Common);

  auto db = std::make_shared<Database>();
  db->AddStop(biryulovoZapadnoyeStop);
  db->AddStop(biryulovoTovarnayaStop);
  db->AddStop(universamStop);
  db->AddStop(prazskajaStop);
  db->SetRoadLength(biryulovoZapadnoyeName, biryulovoTovarnayaName, biryulovoZapadnoyeToBiryulovoTovarnayaDistance);
  db->SetRoadLength(biryulovoTovarnayaName, universamName, biryulovoTovarnayaToUniversamDistance);
  db->SetRoadLength(universamName, biryulovoTovarnayaName, universamToBiryulovoTovarnayaDistance);
  db->SetRoadLength(universamName, biryulovoZapadnoyeName, universamToBiryulovoZapadnoyeDistance);
  db->SetRoadLength(universamName, prazskajaName, universamToPrazskajaDistance);
  db->AddRoute(bus297);
  db->AddRoute(bus635);

  constexpr int32_t busWaitTime = 5;
  constexpr double busVelocity = 33.3;
  RoutingSettings settings{ busWaitTime, busVelocity };
  PathSearcher pathSearcher;
  pathSearcher.Initialize(*db, settings);

  auto path = pathSearcher.FindPath(universamName, universamName);
  double expectedTotalTime = 0.;
  std::vector<IPathElementShp> expectedElements = {};
  Path expectedPath(expectedTotalTime, expectedElements);
  ASSERT(path == expectedPath);
}

void PathSearcherTest1()
{
  std::string biryulovoZapadnoyeName = "Biryulovo Zapadnoye";
  auto biryulovoZapadnoyeStop = std::make_shared<Stop>();
  {
    double latitude = 55.61108;
    double longitude = 37.20829;
    biryulovoZapadnoyeStop->name = biryulovoZapadnoyeName;
    biryulovoZapadnoyeStop->location = GeoPoint{ latitude, longitude };
  }

  std::string biryulovoTovarnayaName = "Biryulovo Tovarnaya";
  auto biryulovoTovarnayaStop = std::make_shared<Stop>();
  {
    double latitude = 54.61108;
    double longitude = 36.20829;
    biryulovoTovarnayaStop->name = biryulovoTovarnayaName;
    biryulovoTovarnayaStop->location = GeoPoint{ latitude, longitude };
  }

  std::string universamName = "Universam";
  auto universamStop = std::make_shared<Stop>();
  {
    double latitude = 53.61108;
    double longitude = 35.20829;
    universamStop->name = universamName;
    universamStop->location = GeoPoint{ latitude, longitude };
  }

  std::string prazskajaName = "Prazskaja";
  auto prazskajaStop = std::make_shared<Stop>();
  {
    double latitude = 52.61108;
    double longitude = 34.20829;
    prazskajaStop->name = prazskajaName;
    prazskajaStop->location = GeoPoint{ latitude, longitude };
  }

  int biryulovoZapadnoyeToBiryulovoTovarnayaDistance = 2600;
  int biryulovoTovarnayaToUniversamDistance = 890;
  int universamToBiryulovoTovarnayaDistance = 1380;
  int universamToBiryulovoZapadnoyeDistance = 2500;
  int universamToPrazskajaDistance = 4650;

  std::string bus297Name = "297";
  auto bus297 = std::make_shared<Route>(bus297Name,
    StopNames{ biryulovoZapadnoyeName, biryulovoTovarnayaName, universamName, biryulovoZapadnoyeName },
    Route::Circular);

  std::string bus635Name("635");
  auto bus635 = std::make_shared<Route>(bus635Name,
    StopNames{ biryulovoTovarnayaName, universamName, prazskajaName },
    Route::Common);

  auto db = std::make_shared<Database>();
  db->AddStop(biryulovoZapadnoyeStop);
  db->AddStop(biryulovoTovarnayaStop);
  db->AddStop(universamStop);
  db->AddStop(prazskajaStop);
  db->SetRoadLength(biryulovoZapadnoyeName, biryulovoTovarnayaName, biryulovoZapadnoyeToBiryulovoTovarnayaDistance);
  db->SetRoadLength(biryulovoTovarnayaName, universamName, biryulovoTovarnayaToUniversamDistance);
  db->SetRoadLength(universamName, biryulovoTovarnayaName, universamToBiryulovoTovarnayaDistance);
  db->SetRoadLength(universamName, biryulovoZapadnoyeName, universamToBiryulovoZapadnoyeDistance);
  db->SetRoadLength(universamName, prazskajaName, universamToPrazskajaDistance);
  db->AddRoute(bus297);
  db->AddRoute(bus635);

  constexpr int32_t busWaitTime = 6;
  constexpr double busVelocity = 29.799;
  RoutingSettings settings{ busWaitTime, busVelocity };
  PathSearcher pathSearcher;
  pathSearcher.Initialize(*db, settings);

  auto path = pathSearcher.FindPath(biryulovoZapadnoyeName, biryulovoTovarnayaName);
  double expectedTotalTime = 11.235;
  std::vector<IPathElementShp> expectedElements = {
    std::make_shared<WaitPathElement>(biryulovoZapadnoyeName, busWaitTime),
    std::make_shared<BusPathElement>(bus297Name, biryulovoZapadnoyeName, biryulovoTovarnayaName, 5.235),
  };
  Path expectedPath(expectedTotalTime, expectedElements);
  ASSERT(path == expectedPath);
}

void PathSearcherTest2()
{
  std::string biryulovoZapadnoyeName = "Biryulovo Zapadnoye";
  auto biryulovoZapadnoyeStop = std::make_shared<Stop>();
  {
    double latitude = 55.61108;
    double longitude = 37.20829;
    biryulovoZapadnoyeStop->name = biryulovoZapadnoyeName;
    biryulovoZapadnoyeStop->location = GeoPoint{ latitude, longitude };
  }

  std::string biryulovoTovarnayaName = "Biryulovo Tovarnaya";
  auto biryulovoTovarnayaStop = std::make_shared<Stop>();
  {
    double latitude = 54.61108;
    double longitude = 36.20829;
    biryulovoTovarnayaStop->name = biryulovoTovarnayaName;
    biryulovoTovarnayaStop->location = GeoPoint{ latitude, longitude };
  }

  std::string universamName = "Universam";
  auto universamStop = std::make_shared<Stop>();
  {
    double latitude = 53.61108;
    double longitude = 35.20829;
    universamStop->name = universamName;
    universamStop->location = GeoPoint{ latitude, longitude };
  }

  std::string prazskajaName = "Prazskaja";
  auto prazskajaStop = std::make_shared<Stop>();
  {
    double latitude = 52.61108;
    double longitude = 34.20829;
    prazskajaStop->name = prazskajaName;
    prazskajaStop->location = GeoPoint{ latitude, longitude };
  }

  double biryulovoZapadnoyeToBiryulovoTovarnayaDistance = 2600.;
  double biryulovoTovarnayaToUniversamDistance = 890.;
  double universamToBiryulovoTovarnayaDistance = 1380.;
  double universamToBiryulovoZapadnoyeDistance = 2500.;
  double universamToPrazskajaDistance = 4650.;

  std::string bus297Name = "297";
  auto bus297 = std::make_shared<Route>(bus297Name,
    StopNames{ biryulovoZapadnoyeName, biryulovoTovarnayaName, universamName, biryulovoZapadnoyeName },
    Route::Circular);

  std::string bus635Name("635");
  auto bus635 = std::make_shared<Route>(bus635Name,
    StopNames{ biryulovoTovarnayaName, universamName, prazskajaName },
    Route::Common);

  auto db = std::make_shared<Database>();
  db->AddStop(biryulovoZapadnoyeStop);
  db->AddStop(biryulovoTovarnayaStop);
  db->AddStop(universamStop);
  db->AddStop(prazskajaStop);
  db->SetRoadLength(biryulovoZapadnoyeName, biryulovoTovarnayaName, biryulovoZapadnoyeToBiryulovoTovarnayaDistance);
  db->SetRoadLength(biryulovoTovarnayaName, universamName, biryulovoTovarnayaToUniversamDistance);
  db->SetRoadLength(universamName, biryulovoTovarnayaName, universamToBiryulovoTovarnayaDistance);
  db->SetRoadLength(universamName, biryulovoZapadnoyeName, universamToBiryulovoZapadnoyeDistance);
  db->SetRoadLength(universamName, prazskajaName, universamToPrazskajaDistance);
  db->AddRoute(bus297);
  db->AddRoute(bus635);

  constexpr int32_t busWaitTime = 6;
  constexpr double busVelocity = 40.;
  constexpr double busVelocityMMin = KmHToMMin(busVelocity);
  RoutingSettings settings{ busWaitTime, busVelocity };
  PathSearcher pathSearcher;
  pathSearcher.Initialize(*db, settings);

  auto path = pathSearcher.FindPath(biryulovoZapadnoyeName, prazskajaName);
  double expectedTotalTime = 24.21;
  std::vector<IPathElementShp> expectedElements = {
    std::make_shared<WaitPathElement>(biryulovoZapadnoyeName, busWaitTime),
    std::make_shared<BusPathElement>(bus297Name, biryulovoZapadnoyeName, biryulovoTovarnayaName, 
    biryulovoZapadnoyeToBiryulovoTovarnayaDistance / busVelocityMMin),
    std::make_shared<BusPathElement>(bus297Name, biryulovoTovarnayaName, universamName,
    biryulovoTovarnayaToUniversamDistance / busVelocityMMin),
    std::make_shared<WaitPathElement>(universamName, busWaitTime),
    std::make_shared<BusPathElement>(bus297Name, universamName, prazskajaName,
    universamToPrazskajaDistance / busVelocityMMin),
  };
  Path expectedPath(expectedTotalTime, expectedElements);
  ASSERT(path == expectedPath);
}
