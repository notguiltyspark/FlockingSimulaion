#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include "BoidParameters.h"
#include <thread>
#include <iostream>
#include <string>
#include <limits>
//#include <cassert>
 


/* To do:
+ Usage of predicate functions? lambda maybe
+ Repetition of input checking
- Builder for string?;
- (IMPORTANT!) How to getline() for int ? Whitespaces may pass val, and stuck buffer as result(is it tho ? )
- How to incorporate getline() in inputHandle()?
- reference in lambda's [] for max_WinY ?
+ lambda to template function maybe or functor?
- max cap for threads?
- max caps in general?
+ boid params: need for caps or negtive ok, just warnings? -> overload of inputHandle
- decltype reference?
- (!) persistence manager?
+ is there a way to use prompt as Settings::prompt?
- maybe put every section into the set_PARAM_NAME()-like functions?. This way somewhat extentible.
  Or maybe let set_ functions o for know and add them later as addition
- header file check includes
- (!) desiredSeparation < visionRadius
+ there is a way to ignore line through <limits>::stream_size
- keyboard commands assignments?
*/
class Settings {
private:


	int win_x_sz;
	int win_y_sz;
	int boidNum;
	int threadNum;

	BoidParameters boidParams;

	static const std::string acceptStr;
	static const std::string declineStr;
	static const int max_WinX;
	static const int max_WinY;
public:

	static const std::string prompt;

	// default settings
	Settings();

	// custom
	void init();

	int getWinX() const { return win_x_sz;  };
	int getWinY() const { return win_y_sz;  };
	int getBoidsNumber()   const { return boidNum; };
	int getThreadsNumber() const { return threadNum; };
	BoidParameters getBoidParameters() const { return boidParams; };

	int setWinX();
	int setWinY();
	int setBoidsNumber();
	int setThreadsNumber();
	BoidParameters setBoidParameters();

	~Settings() {}; // ? + copy? + move? 
	
};


template<typename T, typename UnaryPredicate>
void inputHandle(T& val, const std::string& instruction_msg, const std::string& error_msg, UnaryPredicate predicate) {

	std::cout << instruction_msg << Settings::prompt;
	std::cin >> val;
	while (true) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			
			std::cout << "Invalid input. Try again:\n" << Settings::prompt;
			std::cin >> val;
		}
		else if (predicate(val)) {
			std::cout << error_msg << std::endl << Settings::prompt;
			std::cin >> val;
		}
		else
			break;
	}
}


template<typename T>
void inputHandle(T& val, const std::string& instruction_msg) {
	std::cout << instruction_msg << Settings::prompt;
	std::cin >> val;
	while (true) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			
			std::cout << "Invalid input. Try again:\n" << Settings::prompt;
			std::cin >> val;
		}
		else {
			break;
		}
	}
}

#endif
