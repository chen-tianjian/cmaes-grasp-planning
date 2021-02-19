#include "tinyxml.h"
#include "gtest/gtest.h"
#include <QString>


TEST(TestTinyXML, test_load)
{
    TiXmlDocument doc("../tests/test.xml");
	ASSERT_TRUE(doc.LoadFile());
    const TiXmlElement * root = doc.RootElement();
    const TiXmlElement * child = root->FirstChildElement();
    while (child != NULL) 
    {
        QString elementType = child->Value();
        if (elementType == "circle")
        {
            QString elementName = child->GetText();
            ASSERT_EQ(elementName, "50");
        }
        
        if (elementType == "point")
        {
            QString elementName = child->GetText();
            ASSERT_EQ(elementName, "30");
        }

        child = child->NextSiblingElement();
    }
}