#pragma once
#include <string>
#include <vector>
#include "JsonAbstractRequestParser.h"
#include "Route.h"

using StringVec = std::vector<std::string>;

namespace Json
{
  class OutputBusRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetName(const Node& node) const;
  };
  using OutputBusRequestParserShp = std::shared_ptr<OutputBusRequestParser>;


  class OutputStopRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetName(const Node& node) const;
  };
  using OutputStopRequestParserShp = std::shared_ptr<OutputStopRequestParser>;


  class InputBusRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    std::string GetName(const Node& node) const;
    StringVec GetStops(const Node& node) const;
    Route::Type GetRouteType(const Node& node) const;
  };
  using InputBusRequestParserShp = std::shared_ptr<InputBusRequestParser>;


  class InputStopRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    std::string GetName(const Node& node) const;
    std::unordered_map<std::string, int> GetRoadToDistance(const Node& node) const;
    double GetLongitude(const Node& node) const;
    double GetLatitude(const Node& node) const;
  };
  using InputStopRequestParserShp = std::shared_ptr<InputStopRequestParser>;


  class InputRoutingSettingsParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;
  };
  using InputRoutingSettingsParserShp = std::shared_ptr<InputRoutingSettingsParser>;


  class FindRouteRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetFrom(const Node& node) const;
    std::string GetTo(const Node& node) const;
  };
  using FindRouteRequestParserShp = std::shared_ptr<FindRouteRequestParser>;
}

