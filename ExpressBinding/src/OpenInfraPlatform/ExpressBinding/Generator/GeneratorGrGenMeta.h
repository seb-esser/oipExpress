/*
	Sebastian Esser, M.Sc.
	TUM Chair of computational Modeling and Simulation
*/

#pragma once

#include "OpenInfraPlatform/ExpressBinding/Generator/Generator.h"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"
#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include <iostream>
#include <map>
#include <cassert>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class GeneratorGrGenMeta : public Generator {
public:
	// Constructor
	GeneratorGrGenMeta() {};
	// Destructor
	virtual ~GeneratorGrGenMeta() {};

	// 
	void generate(std::ostream& out, OpenInfraPlatform::ExpressBinding::Schema& schema) {
		for (int i = 0; i < schema.getEntityCount(); i++)
		{
			auto& entity = schema.getEntityByIndex(i);			
			std::cout << i << "\t" << entity.getName() << "\n";

			auto counter = entity.getAttributeCount();

			for (int j = 0; j < counter; j++)
			{
				auto attrName = entity.getAttribute(j).getName();
				auto attrDataType = entity.getAttribute(j).type.get();
				
				std::cout << "\t" << attrName << ": " << attrDataType << "\n";				
			}
			
			
		}
	}

private:
	std::string my_string = "null";
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

EMBED_INTO_OIP_NAMESPACE(GeneratorGrGenMeta)