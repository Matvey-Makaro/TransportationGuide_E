#pragma once

#include <memory>
#include <map>
#include <unordered_map>
#include <string>
#include "IRequest.h"
#include "IResponseStreamFormatter.h"
#include "json.h"

class IResponse;
class OutputBusResponse;
class OutputStopResponse;
class InputBusResponse;
class InputStopResponse;
class FindRouteResponse;
class Route;
using RouteShp = std::shared_ptr<Route>;
class WaitPathElement;

namespace Json
{
  class IResponseFormatter
  {
  public:
    virtual ~IResponseFormatter() = default;

    virtual RequestType GetType() = 0;
    virtual Node Format(const IResponse* response) = 0;
  };
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;

  class OutputBusResponseFormatter : public IResponseFormatter
  {
  public:
    OutputBusResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void FormatIfRouteNotFound(const OutputBusResponse* r);
    void DefaultFormat(const OutputBusResponse* r);
    void FormatCommonPart(const OutputBusResponse* r);
    void ClearPreviousState();

  private:
    std::map<std::string, Node> _responseNode;
  };
  using OutputBusResponseFormatterShp = std::shared_ptr<OutputBusResponseFormatter>;


  class OutputStopResponseFormatter : public IResponseFormatter
  {
  public:
    OutputStopResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void FormatStopNotFound(const OutputStopResponse* response);
    void SuccessFormat(const OutputStopResponse* response);
    void FormatCommonPart(const OutputStopResponse* r);
    Node CreateNodeForRoutes(const std::vector<RouteShp>& routes);
    void ClearPreviousState();

  private:
    std::map<std::string, Node> _responseNode;
  };
  using OutputStopResponseFormatterShp = std::shared_ptr<OutputStopResponseFormatter>;


  class InputBusResponseFormatter : public IResponseFormatter
  {
  public:
    InputBusResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;
  };
  using InputBusResponseFormatterShp = std::shared_ptr<InputBusResponseFormatter>;


  class InputStopResponseFormatter : public IResponseFormatter
  {
  public:
    InputStopResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;
  };
  using InputStopResponseFormatterShp = std::shared_ptr<InputStopResponseFormatter>;


  class FindRouteResponseFormatter : public IResponseFormatter
  {
    struct BusItemData
    {
      std::string BusName;
      int BusSpanCount = 0;
      double BusTotalTime = 0.;
    };
  public:
    FindRouteResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void ClearPreviousState();
    void FormatRouteNotFound(const FindRouteResponse* r);
    void FormatRouteFound(const FindRouteResponse* r);
    void FormatCommonPart(const FindRouteResponse* r);

    Node CreateBusItem(const BusItemData& busItemData) const;
    Node CreateWaitItem(const WaitPathElement& waitElement) const;

  private:
    std::map<std::string, Node> _responseNode;
  };
  using FindRouteResponseFormatterShp = std::shared_ptr<FindRouteResponseFormatter>;


  class ResponseStreamFormatter : public IResponseStreamFormatter
  {
  public:
    ResponseStreamFormatter();
    void Start(std::ostream& out) override;
    void Format(const IResponse& response) override;
    void Finish() override;

    void RegisterResponseFormatter(IResponseFormatterShp formatter);

  protected:
    std::ostream* _out;
    std::vector<Node> _rootNode;
    std::unordered_map<RequestType, IResponseFormatterShp> _formatters;
  };
  using ResponseStreamFormatterShp = std::shared_ptr<ResponseStreamFormatter>;
}

