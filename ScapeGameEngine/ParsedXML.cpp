#include "ParsedXML.h"

namespace sge {
	ParsedXML::ParsedXML(fs::path sourceFile) {
		//Get the string from the filename and copy it into a non - const char*
		auto str = IOManager::stringFromFile(sourceFile);
		init(str);
	}

	ParsedXML::ParsedXML(std::string s) {
		init(s);
	}

	ParsedXML::~ParsedXML() {
		delete src_;
		delete doc_;
	}

	void ParsedXML::init(std::string s) {
		//Copy s to src_ to have a mutable copy
		src_ = new char[s.length() + 1];
		strcpy_s(src_, s.length() + 1, s.c_str());

		doc_ = new rapidxml::xml_document<>();

		doc_->parse<0>(src_);
	}
	
	////Find node named "s" from "target" downwards
	//rapidxml::xml_node<>* ParsedXML::findNodeFrom(std::string s, rapidxml::xml_node<>* target) {
	//	static auto n = target->first_node(s.c_str());

	//	if (n) {
	//		//It's in target
	//		return n;
	//	}
	//	else {
	//		//It is (maybe) somwhere deeper
	//		auto currNode = target->first_node();
	//		while (currNode) {
	//			auto res = findNodeFrom(s, currNode);

	//			if (res) {
	//				return res;
	//			}
	//		}

	//		//Nothing found
	//		return nullptr;
	//	}
	//}
}