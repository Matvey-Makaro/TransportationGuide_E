#include <iostream>
#include <fstream>
#include "Database.h"
#include "LineRequestStreamHandlerBuilder.h"
#include "JsonRequestStreamHandlerBuilder.h"
#include "Tests/TestModule.h"

//#define DEBUG
//#define Line
#define JsonCfg

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef DEBUG
  auto db = make_shared<Database>();

#ifdef Line
  LineRequestStreamHandlerBuilder requestHandlerBuilder(cin, cout, db);
#endif

#ifdef JsonCfg

  /*string outFileName = "Output.txt";
  ofstream out(outFileName, std::ios_base::out | std::ios_base::trunc);
  if (!out.is_open())
  {
    cerr << outFileName << " doesn't open!";
    return -1;
  }


  string inFileName = "Input.txt";
  fstream in(inFileName, std::ios_base::in);
  if (!in.is_open())
  {
    cerr << inFileName << " doesn't open!";
    return -1;
  }

  Json::RequestStreamHandlerBuilder requestHandlerBuilder(in, out, db);*/
    Json::RequestStreamHandlerBuilder requestHandlerBuilder(cin, cout, db);
#endif

  auto requestHandler = requestHandlerBuilder.Build();
  requestHandler->Handle();

#else
  TestModule testModule;
  testModule.Run();
#endif // !DEBUG

  // Test


  return 0;
}
