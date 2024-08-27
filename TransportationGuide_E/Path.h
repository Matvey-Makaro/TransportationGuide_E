#pragma once

#include <string>
#include <vector>
#include <memory>

class IPathElement
{
public:
  enum Type
  {
    Wait,
    Bus,
  };

  virtual ~IPathElement() = default;
  virtual Type GetType() const = 0;
  virtual double GetTime() const = 0;
};
using IPathElementShp = std::shared_ptr<IPathElement>;

bool operator==(const IPathElement& lhs, const IPathElement& rhs);
bool operator!=(const IPathElement& lhs, const IPathElement& rhs);


class AbstractPathElement : public IPathElement
{
public:
  AbstractPathElement(double time);
  double GetTime() const override;

protected:
  double _time;
};

class WaitPathElement : public AbstractPathElement
{
public:
  WaitPathElement(std::string stopName, double waitTime);
  Type GetType() const override;
  const std::string& GetStopName() const;

private:
  std::string _stopName;
};
using WaitPathElementShp = std::shared_ptr<WaitPathElement>;
bool operator==(const WaitPathElement& lhs, const WaitPathElement& rhs);
bool operator!=(const WaitPathElement& lhs, const WaitPathElement& rhs);

class BusPathElement : public AbstractPathElement
{
public:
  BusPathElement(std::string busName,
    std::string fromStopName,
    std::string toStopName,
    double time);
  Type GetType() const override;
  const std::string& GetBusName() const;
  const std::string& FromStopName() const;
  const std::string& ToStopName() const;

private:
  std::string _busName;
  std::string _fromStopName;
  std::string _toStopName;
};
using BusPathElementShp = std::shared_ptr<BusPathElement>;
bool operator==(const BusPathElement& lhs, const BusPathElement& rhs);
bool operator!=(const BusPathElement& lhs, const BusPathElement& rhs);


class Path
{
public:
  Path(double totalTime, std::vector<IPathElementShp> elements = {});
  double GetTotalTime() const;
  const std::vector<IPathElementShp>& GetElements() const;
  void AddElement(IPathElementShp element);

private:
  double _totalTime;
  std::vector<IPathElementShp> _elements;
};
bool operator==(const Path& lhs, const Path& rhs);
bool operator!=(const Path& lhs, const Path& rhs);
