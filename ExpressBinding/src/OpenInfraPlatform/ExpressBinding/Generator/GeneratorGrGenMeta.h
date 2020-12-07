/*
    Sebastian Esser, M.Sc.
    TUM Chair of computational Modeling and Simulation
*/

#pragma once

#include "OpenInfraPlatform/ExpressBinding/Generator/Generator.h"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"
#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <boost/algorithm/string.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class GeneratorGrGenMeta : public Generator {
public:
	// Constructor
	GeneratorGrGenMeta(){};
	// Destructor
	virtual ~GeneratorGrGenMeta(){};

	//
	void generate(std::ostream& out, OpenInfraPlatform::ExpressBinding::Schema& schema) {

		out << "// GrGen meta model for " << schema.getName() << "\n";

		for (int i = 0; i < schema.getEntityCount(); i++) {
			auto& entity = schema.getEntityByIndex(i);

			// is abstract entity?
			// auto isAbstract = entity
			
			std::cout << i << "\t" << entity.getName() << "\n";
			auto entityName = entity.getName();
			auto parentEntity = entity.getSupertype();
			
			out << "node class " << entity.getName(); 

			if (parentEntity != "") {
				out << " extends " << entity.getSupertype();
			}
						
			auto counter = entity.getAttributeCount();

			// no attributes defined on this class inheritance level
			if (entity.getAttributeCount() == 0) {
				out << "; \n";
			}
			else {
				// open parenthesis for node class attributes
				out << "{ \n";
				
				for (int j = 0; j < counter; j++) {
					// get attribute name
					auto attrName = entity.getAttribute(j).getName();				

					// get datatype
					auto attrDataType = entity.getAttribute(j).type;							
					
					switch (attrDataType->getType()) {
						
					case eEntityAttributeParamterType::Simple: {
						//std::cout << "simple Datatype \n";
						auto myType= attrDataType->toString();
						myType = ToLower(myType);
						
						// write to gm file
						out << "\t" << attrName << ": "<< myType << "; \n";
						std::cout << "\t " << attrName << ": " << myType << "; \n";
					} break;

						case eEntityAttributeParamterType::TypeNamed: {
						//std::cout << "\t typeNamed Datatype \n";
					} break;

						case eEntityAttributeParamterType::eGeneralizedType: {
						//std::cout << "\t generalized Type \n";
					} break;
						
					}
				}

				
				// close parenthesis for node class attributes
				out << "} \n \n";
 			}
			
		}
	}

private:
	

	std::string ToLower(std::string text) {
		boost::algorithm::to_lower(text);
		return text;
	}
	
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

EMBED_INTO_OIP_NAMESPACE(GeneratorGrGenMeta)