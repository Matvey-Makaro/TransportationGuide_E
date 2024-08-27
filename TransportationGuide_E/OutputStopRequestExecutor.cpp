#include "OutputStopRequest.h"
#include "OutputStopResponse.h"
#include "Database.h"
#include "OutputStopRequestExecutor.h"

OutputStopRequestExecutor::OutputStopRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType OutputStopRequestExecutor::GetRequestType() const
{
  return RequestType::OutputStop;
}

IResponseShp OutputStopRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToOutputStopRequest(request);
	auto response = std::make_shared<OutputStopResponse>();
	response->SetId(r->GetId());

	const auto& stopName = r->GetName();
	response->SetStopName(stopName);
	response->SetStop(_db->GetStop(stopName));
	if (response->IsStopExist())
		response->SetRoutes(_db->GetRoutesByStop(stopName));
	
  return response;
}

const OutputStopRequest* OutputStopRequestExecutor::ToOutputStopRequest(const IRequest* request) const
{
  return dynamic_cast<const OutputStopRequest*>(request);
}
