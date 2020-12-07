/*
    Sebastian Esser, M.Sc.
    TUM Chair of computational Modeling and Simulation
*/

#pragma once

#include "OpenInfraPlatform/ExpressBinding/Generator/Generator.h"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"
#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include <cassert>
#include <iostream>
#include <map>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class GeneratorGrGenMeta : public Generator {
public:
	// Constructor
	GeneratorGrGenMeta(){};
	// Destructor
	virtual ~GeneratorGrGenMeta(){};

	//
	void generate(std::ostream& out, OpenInfraPlatform::ExpressBinding::Schema& schema) {
		for (int i = 0; i < schema.getEntityCount(); i++) {
			auto& entity = schema.getEntityByIndex(i);
			std::cout << i << "\t" << entity.getName() << "\n";

			auto counter = entity.getAttributeCount();

			for (int j = 0; j < counter; j++) {
				auto attrName = entity.getAttribute(j).getName();
				std::cout << "\t" << attrName << " ";
				
				auto attrDataType = entity.getAttribute(j).type;

				switch (attrDataType->getType()) {
				case eEntityAttributeParamterType::Simple: {
					std::cout << "simple Datatype \n";
				} break;

					case eEntityAttributeParamterType::TypeNamed: {
					std::cout << "typeNamed Datatype \n";
				} break;

					case eEntityAttributeParamterType::eGeneralizedType: {
					std::cout << "generalized Type \n";
				} break;
					
				}				
 			}
		}
	}

private:
	std::string my_string = "null";
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

EMBED_INTO_OIP_NAMESPACE(GeneratorGrGenMeta)