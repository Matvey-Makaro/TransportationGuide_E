#include "AbstractOutputRequest.h"

AbstractOutputRequest::AbstractOutputRequest() :
    _id(-1)
{}

int AbstractOutputRequest::GetId() const
{
    return _id;
}

void AbstractOutputRequest::SetId(int id)
{
    _id = id;
}
