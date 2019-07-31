#pragma once
#include "stdheaders.h"
#include "IOManager.h"

#include <cstdio>
#include <cstring>

namespace sge {
	class ParsedXML {
	public:
		ParsedXML(fs::path source);
		ParsedXML(std::string s);
		~ParsedXML();

		void init(std::string s);

		inline rapidxml::xml_document<>* doc() { return doc_; }
		inline rapidxml::xml_node<>* root() { return doc_->first_node(); }

		//Find any node named "s" in the root node
		rapidxml::xml_node<>* operator[](std::string s) { return doc_->first_node(s.c_str()); }
		//Find any node named "s"
		//rapidxml::xml_node<>* findNodeFrom(std::string s, rapidxml::xml_node<>* target);
		//rapidxml::xml_node<>* findNode(std::string s) { return findNodeFrom(s, doc_->first_node()); }

	private:
		rapidxml::xml_document<>* doc_;
		char* src_ = nullptr;
	};
}