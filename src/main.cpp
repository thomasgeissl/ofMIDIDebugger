#include "ofAppNoWindow.h"
#include "ofApp.h"
#include <iostream>
#include "cxxopts.hpp"

cxxopts::ParseResult
parse(int argc, char *argv[])
{
	try
	{
		cxxopts::Options options(argv[0], " - midi monitor and sender");
		options.add_options()("l,list", "list")("p,port", "port", cxxopts::value<int>())("v,virtualPort", "virtualPort", cxxopts::value<std::string>()->default_value("ofMIDIDebugger"))("i,interactive", "interactive")("m,message", "message", cxxopts::value<std::string>());
		auto result = options.parse(argc, argv);
		return result;
	}
	catch (const cxxopts::OptionException &e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	auto result = parse(argc, argv);
	auto arguments = result.arguments();

	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);

	if (result["list"].as<bool>())
	{
		ofApp();
	}
	if (result.count("message") == 0) // monitor
	{
		if (result.count("port") > 0)
		{
			ofRunApp(new ofApp(result["port"].as<int>()));
		}
		else if (result.count("virtualPort") > 0)
		{
			ofRunApp(new ofApp(result["virtualPort"].as<std::string>()));
		}
	}
	else // sender
	{
		if (result.count("port") > 0)
		{
			ofRunApp(new ofApp(result["port"].as<int>(), result["message"].as<std::string>(), result["interactive"].as<bool>()));
		}
		else if (result.count("virtualPort") > 0)
		{
			ofRunApp(new ofApp(result["virutalPort"].as<std::string>(), result["message"].as<std::string>(), result["interactive"].as<bool>()));
		}
	}
	return 0;
}