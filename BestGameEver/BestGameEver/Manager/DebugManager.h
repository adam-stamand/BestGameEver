#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>


#undef SendMessage 


class DebugManager
{
public:
	 
	static void LogActivity(std::string message) { 
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
		std::cout << "ACTIVITY: " + message << std::endl;
	};



	static void LogError(std::string message) { 
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 4);
		std::cout << "ERROR: " + message << std::endl;
	}
};



