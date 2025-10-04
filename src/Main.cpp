

#include <iostream>
#include "Clock.hpp"

const std::string HELP_MESSAGE(
	"Usage:\
\n\t1. clock --help\
\n\t2. clock [--update] [diameter]\
\nDescription:\
\n\tDraws an analog clock depicting the actual time.\
\n\tIf the \"update\" flag is passed, clock will be redrawn every second until\
\n\tthe program is terminated. You can specify diameter of a clock (in characters)\
\n\tby passing \"diameter\" argument which is an integer in range 1-120."
);

const uint8_t DEFAULT_CLOCK_DIAMETER = 25;

int main(int argc, char** argv)
{
	/********* PROCESS PASSED ARGUMENTS *********/

	bool updateFlag = false;
	uint8_t clockDiameter = DEFAULT_CLOCK_DIAMETER;
	if(argc > 1)
	{
		std::string firstArg(argv[1]);
		std::string diameterArg;

		if(firstArg == "--help")
		{
			std::cout << HELP_MESSAGE << std::endl;
			return 0;
		}
		else if(firstArg == "--update")
		{
			updateFlag = true;

			if(argc > 2) diameterArg = std::string(argv[2]);
		}
		else diameterArg = std::string(firstArg);

		if(diameterArg.length())
		{
			try
			{
				clockDiameter = std::stoi(diameterArg);
			}
			catch(const std::invalid_argument& exception)
			{
				std::cerr << "Diameter must be an integer" << std::endl;
				return 1;
			}
			
			if(clockDiameter == 0 || clockDiameter > 120)
			{
				std::cerr << "Diameter is out of acceptable range (1-120)" << std::endl;
				return 2;
			}
		}
	}

	/********* DRAW A CLOCK *********/

	Clock clock(clockDiameter);

	time_t lastTime = 0;
	while(updateFlag)
	{
		time_t currentTime = Clock::getEpochTime();
		if(lastTime != currentTime)
		{
			std::system("clear");
			clock.update();
			clock.show();
			lastTime = currentTime;
		}
	}
	
	if(!updateFlag) clock.show();

	return 0;
}
