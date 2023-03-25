#pragma once
#include <exception>
#include <string>
#include "../../ECS/Components.h"

/**
 * @brief Error handler class
*/
class ErrorHandler : public std::exception
{
public:
	/**
	 * @brief Constructor for the error when the entity don't have all the needed components
	 * @param baseclass - the component class
	 * @param refclass - the component class that is needed
	*/
	template<typename T>
	ErrorHandler(T baseclass, T refclass)
	{
		cout << std::string(baseclass) + " - entity has no " + std::string(refclass) << endl;
	}
	/**
	 * @brief Constructor for the error when the entity don't have all the needed components
	 * @param T1 - the component class
	 * @param T2 - the component class that is needed
	*/
	template<typename T1, typename T2>
	ErrorHandler()
	{
		cout << std::string(typeid(T1).name()) + " - entity has no " + std::string(typeid(T2).name()) << endl;
	}
};

