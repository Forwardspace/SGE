ParsedXML
=========

This class is a wrapper around the ``rapidxml::xmldocument<>`` class.
As such, it provides a way to parse and, more importantly, access an XML document.

How to use it?
--------------

Construct the object:
::
	ParsedXML::ParsedXML(fs::path sourceFile);
	//or
	ParsedXML::ParsedXML(std::string s);

	//e.g.
	auto myXMLDoc = ParsedXML(fs::path("path/to/file.xml"));

Then, find children of the root node using
::
	auto myNode = myXMLDoc["Settings"]

Find nodes anywhere from root down:
::
	rapidxml::xml_node<>* findNode(std::string s);

	auto myNode = myXMLDoc.findNode("Brightness");

.. note:: For information on accessing and manipulating nodes, see http://rapidxml.sourceforge.net/manual.html