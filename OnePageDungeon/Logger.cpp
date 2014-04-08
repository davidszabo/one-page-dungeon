#include <windows.h>
#include "Logger.h"


Logger::Logger(sf::String name)
{
	className = name;
	isLoggingEnabled = false;
#ifdef _DEBUG
	isLoggingEnabled = true;
#endif

}

void Logger::log(sf::String message)
{
	if (isLoggingEnabled)
	{
		time_t now = time(0);
		tm *localTime = localtime(&now);
		std::clog << 1900 + localTime->tm_year << ".";
		std::clog << 1 + localTime->tm_mon << ".";
		std::clog << localTime->tm_mday << ". ";
		std::clog << localTime->tm_hour << ":";
		std::clog << localTime->tm_min << ":";
		std::clog << localTime->tm_sec << " [";
		std::clog << className.toAnsiString() << "] ";
		std::clog << message.toAnsiString();
		std::clog << std::endl;
	}
}

void Logger::logWARN(sf::String message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
	this->log(message);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
}

Logger::~Logger(void)
{
}
