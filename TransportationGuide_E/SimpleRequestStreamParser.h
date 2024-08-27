#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <string_view>
#include "ILineRequestParser.h"
#include "Utiils.h"
#include "IRequestStreamParser.h"

namespace Line
{
  class SimpleRequestStreamParser : public IRequestStreamParser
  {
  public:
    SimpleRequestStreamParser();

    void SetRequestStream(std::istream& in) override;
    bool HasRequest() const override;
    IRequestShp GetNextRequest() override;
    void RegisterRequestsParser(Line::IRequestParserShp parser);

  private:
    std::string GetNextRequestStr();
    std::string_view GetRequestName(std::string_view requestStr) const;
    int GetNumOfRequests();
      



  private:
    mutable InputStreamWrapper _in;
    int _numOfRequests;
    std::unordered_map<std::string, IRequestParserShp> _parsers;
  };
  using SimpleRequestStreamParserShp = std::shared_ptr<SimpleRequestStreamParser>;
}

