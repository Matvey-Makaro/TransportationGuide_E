#include "AbstractResponse.h"

AbstractResponse::AbstractResponse(RequestType type) :
  _type(type)
{
}

RequestType AbstractResponse::GetType() const
{
  return _type;
}

int AbstractOutputResponse::GetId() const
{
  return _id;
}

void AbstractOutputResponse::SetId(int id)
{
  _id = id;
}
