#include <cassert>
#include "CmpUtils.h"
#include "Path.h"

AbstractPathElement::AbstractPathElement(double time) :
  _time(time)
{}

double AbstractPathElement::GetTime() const
{
  return _time;
}

WaitPathElement::WaitPathElement(std::string stopName, double waitTime) :
  AbstractPathElement(waitTime),
  _stopName(std::move(stopName))
{}

IPathElement::Type WaitPathElement::GetType() const
{
  return Type::Wait;
}

const std::string& WaitPathElement::GetStopName() const
{
  return _stopName;
}

BusPathElement::BusPathElement(std::string busName, std::string fromStopName, std::string toStopName, double time)
  : AbstractPathElement(time),
  _busName(std::move(busName)),
  _fromStopName(std::move(fromStopName)),
  _toStopName(std::move(toStopName))
{}

IPathElement::Type BusPathElement::GetType() const
{
  return Type::Bus;
}

const std::string& BusPathElement::GetBusName() const
{
  return _busName;
}

const std::string& BusPathElement::FromStopName() const
{
  return _fromStopName;
}

const std::string& BusPathElement::ToStopName() const
{
  return _toStopName;
}

Path::Path(double totalTime, std::vector<IPathElementShp> elements) :
  _totalTime(totalTime),
  _elements(std::move(elements))
{}

double Path::GetTotalTime() const
{
  return _totalTime;
}

const std::vector<IPathElementShp>& Path::GetElements() const
{
  return _elements;
}

void Path::AddElement(IPathElementShp element)
{
  _elements.push_back(std::move(element));
}

bool operator==(const IPathElement& lhs, const IPathElement& rhs)
{
  return lhs.GetType() == rhs.GetType() &&
    IsEqual(lhs.GetTime(), rhs.GetTime());
}

bool operator!=(const IPathElement& lhs, const IPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const WaitPathElement& lhs, const WaitPathElement& rhs)
{
  return static_cast<const IPathElement&>(lhs) == static_cast<const IPathElement&>(rhs) &&
    lhs.GetStopName() == rhs.GetStopName();
}

bool operator!=(const WaitPathElement& lhs, const WaitPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const BusPathElement& lhs, const BusPathElement& rhs)
{
  return static_cast<const IPathElement&>(lhs) == static_cast<const IPathElement&>(rhs) &&
    lhs.GetBusName() == rhs.GetBusName() &&
    lhs.FromStopName() == rhs.FromStopName() &&
    lhs.ToStopName() == rhs.ToStopName();
}

bool operator!=(const BusPathElement& lhs, const BusPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const Path& lhs, const Path& rhs)
{
  if (!IsEqual(lhs.GetTotalTime(), rhs.GetTotalTime()))
    return false;
  const auto& lhsElements = lhs.GetElements();
  const auto& rhsElements = rhs.GetElements();
  if (lhsElements.size() != rhsElements.size())
    return false;
  auto size = lhsElements.size();
  for (int i = 0; i < size; i++)
  {
    const auto& lhsElement = lhsElements[i];
    const auto& rhsElement = rhsElements[i];
    if (lhsElement->GetType() != rhsElement->GetType())
      return false;
    if (lhsElement->GetType() == IPathElement::Wait)
    {
      return static_cast<const WaitPathElement&>(*lhsElement) == static_cast<const WaitPathElement&>(*rhsElement);
    }
    else if(lhsElement->GetType() == IPathElement::Bus)
    {
      return static_cast<const BusPathElement&>(*lhsElement) == static_cast<const BusPathElement&>(*rhsElement);
    }
    else
    {
      assert(false);
    }
  }
  return true;
}

bool operator!=(const Path& lhs, const Path& rhs)
{
  return !(lhs == rhs);
}