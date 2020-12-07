/*
    Sebastian Esser, M.Sc.
    TUM Chair of computational Modeling and Simulation
*/

#pragma once

#include "OpenInfraPlatform/ExpressBinding/Generator/Generator.h"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"
#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <iostream>
#include <map>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class GeneratorGrGenMeta : public Generator {
public:
	// Constructor
	GeneratorGrGenMeta(){}
	// Destructor
	virtual ~GeneratorGrGenMeta(){}

	//
	void generate(std::ostream& out, OpenInfraPlatform::ExpressBinding::Schema& schema);

private:
	std::string ToLower(const std::string& text);
//	/*{
//		boost::algorithm::to_lower(text);
//		return text;
//	}*/
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

EMBED_INTO_OIP_NAMESPACE(GeneratorGrGenMeta)