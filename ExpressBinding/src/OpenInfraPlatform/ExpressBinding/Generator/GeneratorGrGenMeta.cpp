

#include "GeneratorGrGenMeta.h"
#include <filesystem>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

// namespace fs = std::experimental::filesystem;
namespace fs = std::filesystem;

//std::string toUpper(const std::string& inputString) {
//	std::string str = inputString;
//	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
//	return str;
//}
//
std::string GeneratorGrGenMeta::ToLower(const std::string& inputString) {
	std::string str = inputString;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}


void GeneratorGrGenMeta::generate(std::ostream& out, OpenInfraPlatform::ExpressBinding::Schema& schema) {
	out << "// GrGen meta model for " << schema.getName() << "\n";

	// Types

	out << "// -- enums -- \n";
	auto allTypes = schema.types_;

	for (auto myType : allTypes) {
		if (myType.isEnumeration() == true) {
			
			
		}
		else if (myType.isSimpleType()) {
			
		}
		
	}
	

	// Entities


	// Enums
	



	
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

		auto counterAttributes = entity.getAttributeCount();
		auto counterAttributesQualified = entity.getQualifiedAttributeCount();
		// no attributes defined on this class inheritance level
		if (entity.getAttributeCount() == 0) {
			out << "; \n";
		} else {
			// open parenthesis for node class attributes
			out << "{ \n";

			for (int j = 0; j < counterAttributes; j++) {
				// get attribute name
				auto attrName = entity.getAttribute(j).getName();

				// get datatype
				auto attrDataType = entity.getAttribute(j).type;

				switch (attrDataType->getType()) {
				case eEntityAttributeParamterType::Simple: {
					// std::cout << "simple Datatype \n";
					auto myType = attrDataType->toString();
					myType = ToLower(myType);

					// write to gm file
					out << "\t" << attrName << ": " << myType << "; \n";
					std::cout << "\t " << attrName << ": " << myType << "; \n";
				} break;

				case eEntityAttributeParamterType::TypeNamed: {
					// write to gm file
					auto myType = attrDataType->toString();
					// myType = ToLower(myType);
					out << "\t" << attrName << ": " << myType << "; \n";
					std::cout << "\t " << attrName << ": " << myType << "; \n";
				} break;

				case eEntityAttributeParamterType::eGeneralizedType: {
					auto myType = attrDataType->toString();
					// myType = ToLower(myType);
					out << "\t" << attrName << ": " << myType << "; \n";
					std::cout << "\t " << attrName << ": " << myType << "; \n";
				} break;
				}
			}

			// close parenthesis for node class attributes
			out << "} \n \n";
		}
	}
}



OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END