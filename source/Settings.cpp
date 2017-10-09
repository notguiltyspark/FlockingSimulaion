#include "Settings.h"

const std::string Settings::acceptStr  = "Y";
const std::string Settings::declineStr = "N";
const std::string Settings::prompt     = ">";

const int Settings::max_WinX = 1000;
const int Settings::max_WinY = 700;


Settings::Settings(){
	win_x_sz = 1200;
	win_y_sz = 1000;
	boidNum = 1000;
	threadNum = 8 * std::thread::hardware_concurrency();
	if (threadNum == 0)
		threadNum = 1;

	boidParams.maxSpeed = 2.9;
	boidParams.maxForce = 0.3;

	boidParams.desiredSeparation = 15;
	boidParams.visionRadius = 26;
	
	boidParams.alignCoef = 0.3;
	boidParams.coheseCoef = 0.10;
	boidParams.separateCoef = 0.2;
}


void Settings::init() {
	std::string answer = "";
	std::string error_msg = "";
	std::string instruction_msg = "";

	// Default or Custom settings
	instruction_msg = std::string("Do you want to change default settings? (") + std::string(acceptStr) 
					+ std::string("/") + std::string(declineStr) + std::string(")\n");
	error_msg       = std::string("Use '") + acceptStr + std::string("' or '") + std::string(declineStr) 
		            + std::string("'!") + std::string(" Try again:");
	inputHandle(answer, instruction_msg, error_msg, [](decltype(answer) val) { return val != acceptStr && val != declineStr; });
	
	if (answer == declineStr)
		return;

	// Window X-size
	instruction_msg = "X-size of simulation area:\n";
	error_msg = std::string("Invalid window size. Y must be in range (0;") + std::to_string(max_WinX)
		      + std::string("], try again:");
	inputHandle(win_x_sz, instruction_msg, error_msg, [](decltype(win_x_sz) val) { return val <= 0 || val > max_WinX; });
	
	// Window Y-size 
	instruction_msg = "Y-size of simulation area:\n";
	error_msg = std::string("Invalid window size. Y must be in range (0;") + std::to_string(max_WinY)
		      + std::string("], try again:");
	inputHandle(win_y_sz, instruction_msg, error_msg, [](decltype(win_y_sz) val) { return val <= 0 || val > max_WinY; });
	
	// Number of boids 
	instruction_msg = "Number of boids:\n";
	error_msg = "Invalid number of boids. It must be non-negative:";
	inputHandle(boidNum, instruction_msg, error_msg, [](decltype(boidNum) val) { return val < 0; });
	
	// Number of threads 
	instruction_msg = "Number of threads:\n";
	error_msg = "Invalid number of threads. It must be non-negative:"; 
	inputHandle(threadNum, instruction_msg, error_msg, [](decltype(threadNum) val) { return val < 0; });
	
	// ------ Boid parameters ------
	// Align coef
	instruction_msg = "Alignment coefficient:\n";
	inputHandle(boidParams.alignCoef, instruction_msg);
	
	// Cohese coef 
	instruction_msg = "Cohesion coefficient:\n";
	inputHandle(boidParams.coheseCoef, instruction_msg);

	// Separate coef
	instruction_msg = "Separation coefficient:\n";
	inputHandle(boidParams.separateCoef, instruction_msg);
	
	// Desired separation 
	instruction_msg = "Desired separation disance:\n";
	error_msg = "Invalid separation distance. Must be non-negative:"; // or ] negative also?
	inputHandle(boidParams.desiredSeparation, instruction_msg, error_msg, 
		[](decltype(boidParams.desiredSeparation) val) { return val < 0; });

	// Maximum force to acquire
	instruction_msg = "Maximum acceleration(force) for entity to acquire:\n";
	error_msg = "Invalid acceleration. Must be non-negative:"; 
	inputHandle(boidParams.maxForce, instruction_msg, error_msg,
		[](decltype(boidParams.maxForce) val) { return val < 0; });

	// Maximum speed to acquire
	instruction_msg = "Maximum velocity for entity to acquire:\n";
	error_msg = "Invalid velocity. Must be non-negative:";
	inputHandle(boidParams.maxSpeed, instruction_msg, error_msg,
		[](decltype(boidParams.maxSpeed) val) { return val < 0; });

	// Radius of vision 
	instruction_msg = "Entity's radius of vision:\n";
	error_msg = "Invalid vision radius. Must be non-negative:"; 
	inputHandle(boidParams.visionRadius, instruction_msg, error_msg,
		[](decltype(boidParams.visionRadius) val) { return val < 0; });
	
	return;
}
