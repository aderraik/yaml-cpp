#include "tests.h"
#include "emittertests.h"
#include "parsertests.h"
#include "spectests.h"
#include <fstream>
#include <iostream>

namespace Test
{
	void RunAll()
	{
		bool passed = true;
		if(!RunParserTests())
			passed = false;
			
		if(!RunEmitterTests())
			passed = false;

		if(!RunSpecTests())
			passed = false;
		
		if(passed)
			std::cout << "All tests passed!\n";
	}
}

