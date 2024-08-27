#include <sstream>
#include <iomanip>

#include "test_runner.h"
#include "CmpUtils.h"
#include "Database.h"
#include "InputBusCommand.h"
#include "InputBusCommandTests.h"

using namespace std;

void InputBusCommandNameTest()
{
  auto db = std::make_shared<Database>();
  InputBusCommand command(db);
  string expectedName = "Bus";
  ASSERT_EQUAL(command.GetName(), expectedName);
}

void InputBusCommandCommonRouteTest()
{
  auto db = std::make_shared<Database>();
  InputBusCommand command(db);
  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  stringstream ss;
  ss << setprecision(6) << "Bus " << busName << ": ";
  string del = "-";
  for (size_t i = 0; i < stops.size(); i++)
  {
    if (i == stops.size() - 1)
      break;
    ss << stops[i] << " " << del << " ";
  }
  ss << stops.back();

  Route::Type expectedType = Route::Type::Common;
  string expectedResult;

  command.Do(ss.str());

  auto route = db->GetRoute(busName);

  ASSERT(route != nullptr);
  if (route == nullptr)
    return;

  ASSERT_EQUAL(route->GetName(), busName);
  ASSERT_EQUAL(route->GetStopNames(), stops);
  ASSERT_EQUAL(route->GetType(), expectedType);
  ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void InputBusCommandCircularRouteTest()
{
  auto db = std::make_shared<Database>();
  InputBusCommand command(db);
  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  stringstream ss;
  ss << setprecision(6) << "Bus " << busName << ": ";
  string del = ">";
  for (size_t i = 0; i < stops.size(); i++)
  {
    if (i == stops.size() - 1)
      break;
    ss << stops[i] << " " << del << " ";
  }
  ss << stops.back();

  Route::Type expectedType = Route::Type::Circular;
  string expectedResult;

  command.Do(ss.str());

  auto route = db->GetRoute(busName);

  ASSERT(route != nullptr);
  if (route == nullptr)
    return;

  ASSERT_EQUAL(route->GetName(), busName);
  ASSERT_EQUAL(route->GetStopNames(), stops);
  ASSERT_EQUAL(route->GetType(), expectedType);
  ASSERT_EQUAL(command.GetResult(), expectedResult);
}