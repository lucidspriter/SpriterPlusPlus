#ifndef TINYXMLSPRITERFILEDOCUMENTWRAPPER_H
#define TINYXMLSPRITERFILEDOCUMENTWRAPPER_H

#include "../tinyxml2/tinyxml2.h"

#include "spriterengine/override/spriterfiledocumentwrapper.h"

#include "Common.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileDocumentWrapper : public SpriterFileDocumentWrapper
	{
	public:
		TinyXmlSpriterFileDocumentWrapper(string fileString);

		// trick to avoid changing anything in the spriter c++ template, 
		// the whole file as a string is coming from the run data, the file name is a dummy name to choose between scml and scon format
		void loadFile(std::string dummyfileName) override;

	private:
		SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

		tinyxml2::XMLDocument doc;
		string fileString;
	};

}

#endif // TINYXMLSPRITERFILEDOCUMENTWRAPPER_H