/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is free
    software; you can redistribute it and/or modify it under the terms
    of the GNU General Public License Version 3 as published by the Free
    Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "Generator/GeneratorGrGenMeta.h"


#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#include "OpenInfraPlatform/ExpressBinding/Parser/node.h"
#include "parser.hpp"

extern int yyparse();
extern FILE *yyin;

#include "OpenInfraPlatform/ExpressBinding/Generator/GeneratorCSharp.Net.h"
#include "OpenInfraPlatform/ExpressBinding/Generator/GeneratorEcho.h"
#include "OpenInfraPlatform/ExpressBinding/Generator/GeneratorOIP.h"
#include "OpenInfraPlatform/ExpressBinding/Generator/GeneratorVB.Net.h"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"

using namespace OpenInfraPlatform::ExpressBinding;

#include "tclap/CmdLine.h"

int main(int argc, char **argv) {
	try {
		buw::CmdLine cmd("oipExpress", ' ', "0.1");

		// get the unlabeled input argument from the command line
		buw::UnlabeledValueArg<std::string> sourceFiles("i", "EXPRESS Schema file.", true, "./rectified", "string");
		cmd.add(sourceFiles);

		// get the labeled input argument '-o' specifying the target for output
		buw::ValueArg<std::string> outputDirectory("o", "outputDir", "The output directory.", false, "", "string");
		cmd.add(outputDirectory);

		// Parse the args.
 		//cmd.parse(argc, argv);	// comment for debug

		// open a file handle to a particular file:

		//const char *filename = sourceFiles.getValue().c_str();	// enable this line when cmd argument is present
		const char *filename = "C://dev//oipExpress_build//Debug//IFC4x3_RC2.exp";
		
		std::string outputDirectoryName = outputDirectory.getValue();
			   
		
		FILE *myfile = fopen(filename, "r");
		// make sure it is valid:
		if (!myfile) {
			cout << "I can't open file!" << endl;
			return -1;
		}
		// set flex to read from it instead of defaulting to STDIN:
		yyin = myfile;

		// parse through the input until there is no more:
		do {
			yyparse();
		} while (!feof(yyin));

		std::ofstream ofs("test.txt", std::ofstream::out);

		std::ostream &out = ofs; // std::cout;

		if (false) {
			std::cout << "---------------------------" << std::endl;
			Entity e = oip::Schema::getInstance().getEntityByName("IfcSIUnit");

			std::vector<EntityAttribute> attributes = oip::Schema::getInstance().getAllEntityAttributes(e);
			for (int i = 0; i < attributes.size(); ++i) {
				const EntityAttribute &attribute = attributes[i];
				std::cout << attribute.getName() << " : " << attribute.type->toString();

				if (e.hasQualifiedAttribute(attribute.getName()))
					std::cout << " (*)";

				std::cout << std::endl;
			}
		}

		enum class eGeneratorType { Echo, OIP, VBNet, CSharp, GrGenMeta };

		// eGeneratorType gt = eGeneratorType::OIP;
		eGeneratorType gt = eGeneratorType::GrGenMeta;

		switch (gt) {
		case eGeneratorType::Echo: {
			GeneratorEcho echo;
			echo.generate(out, oip::Schema::getInstance());
		} break;

		case eGeneratorType::OIP: {
			GeneratorOIP cppgen(outputDirectoryName);
			cppgen.generate(out, oip::Schema::getInstance());
		} break;

		case eGeneratorType::VBNet: {
			GeneratorVBNet vbnetgen;
			vbnetgen.generate(out, oip::Schema::getInstance());
		} break;

		case eGeneratorType::CSharp: {
			GeneratorCSharpNet vbnetgen;
			vbnetgen.generate(out, oip::Schema::getInstance());
		} break;

		case eGeneratorType::GrGenMeta: {
			GeneratorGrGenMeta grgenmetagen;
			grgenmetagen.generate(out, oip::Schema::getInstance());
		} break;
		}

		ofs.close();
	} catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
}

extern int line_num;

void yyerror(const char *s) {
	cout << "Parse error!  Message: " << s << endl;
	cout << "Line number: " << line_num << endl;
	// might as well halt now:
	exit(-1);
}