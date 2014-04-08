#pragma once

#include <SFML/System.hpp>
#include <iostream>
#include <ctime>

class Logger
{
public:
	Logger(sf::String name);
	void log(sf::String message);
	void Logger::logWARN(sf::String message);
	~Logger(void);

private:
	sf::String className;
	bool isLoggingEnabled;

};

