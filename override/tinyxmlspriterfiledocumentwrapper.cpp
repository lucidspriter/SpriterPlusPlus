#include "tinyxmlspriterfiledocumentwrapper.h"

#include "tinyxmlspriterfileelementwrapper.h"

namespace SpriterEngine
{
	TinyXmlSpriterFileDocumentWrapper::TinyXmlSpriterFileDocumentWrapper(string fileString) :
		fileString(fileString)
	{
	}

	void TinyXmlSpriterFileDocumentWrapper::loadFile(std::string dummyfileName)
	{
		doc.LoadFileFromBuffer(fileString.c_str());
		fileString.clear();
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement());
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement(elementName.c_str()));
	}

}