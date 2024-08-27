#pragma once

#include <unordered_map>
#include <list>
#include <tuple>
#include <functional>
#include "IRequestStreamParser.h"
#include "json.h"

namespace Json
{
	class IRequestParser;
	using IRequestParserShp = std::shared_ptr<IRequestParser>;

	class Section
	{
	public:
		Section(std::string name, Node node);
		Section(std::string name, std::vector<Node> nodes);

		bool IsEnd() const;
		void ToNextNode();
		const Node& GetCurrNode() const;

		const std::string& GetName() const;

	private:
		std::vector<Node> _nodes;
		size_t _currNodeIndex;
		std::string _name;
	};

	class RequestStreamParser : public IRequestStreamParser
	{
		using ParsersMap = std::unordered_map<std::string, IRequestParserShp>;
		using ParseNodeFunc = std::function<IRequestShp(const Node& node)>;
	public:
		using OnBaseRequestsParsedCb = std::function<void()>;

		RequestStreamParser();
		virtual ~RequestStreamParser() = default;

		void SetRequestStream(std::istream& in) override;
		bool HasRequest() const override;
		IRequestShp GetNextRequest() override;

		void RegisterRoutingSettingsParser(IRequestParserShp parser);
		void RegisterInputRequestsParser(IRequestParserShp parser);
		void RegisterOutputRequestsParser(IRequestParserShp parser);

		void AddOnBaseRequestsParsedCb(OnBaseRequestsParsedCb cb);

	private:
		void ToStartState();
		void AddRoutingSettingsSection(const Node& rootNode);
		void AddBaseRequestsSection(const Node& rootNode);
		void AddStatRequestsSection(const Node& rootNode);
		void RemoveEmptySections();
		std::vector<Node> GetArrByName(const Node& rootNode, const std::string& name) const;
		Node GetObjByName(const Node& rootNode, const std::string& name) const;

		IRequestShp GetNextRequest(
			const Node& node,
			const std::unordered_map<std::string, IRequestParserShp>& parsers) const;
		IRequestShp GetNextRequest(
			const Node& node,
			const IRequestParserShp& parser) const;
		std::string GetType(const Node& node) const;
		void OnBaseRequestsParsed();


	private:
		std::list<std::pair<Section, ParseNodeFunc>> _sections;
		IRequestParserShp _routingSettingsParser;
		ParsersMap _baseParsers;
		ParsersMap _statParsers;

		std::vector<OnBaseRequestsParsedCb> _onBaseRequestsParsedCbs;
	};
	using RequestStreamParserShp = std::shared_ptr<RequestStreamParser>;
}

