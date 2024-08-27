#pragma once
#include "IResponse.h"

class AbstractResponse : public IResponse
{
public:
  AbstractResponse(RequestType type);
  RequestType GetType() const override;

protected:
  RequestType _type;
};
using AbstractResponseShp = std::shared_ptr<AbstractResponse>;

class AbstractOutputResponse : public AbstractResponse
{
public:
  using AbstractResponse::AbstractResponse;

  int GetId() const;
  void SetId(int id);

protected:
  int _id = 0;
};
using AbstractOutputResponseShp = std::shared_ptr<AbstractOutputResponse>;
