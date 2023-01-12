#pragma once
#include <exception>
#include <string>
#include "../../ECS/Components.h"

class ErrorHandler : public std::exception
{
public:
	template<typename T>
	ErrorHandler(T baseclass, T refclass)
	{
		cout << std::string(baseclass) + " - entity has no " + std::string(refclass) << endl;
	}
	template<typename T1, typename T2>
	ErrorHandler()
	{
		cout << std::string(typeid(T1).name()) + " - entity has no " + std::string(typeid(T2).name()) << endl;
	}
};

