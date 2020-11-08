#include "ofAppNoWindow.h"
#include "ofApp.h"
#include <iostream>
#include "ofxCommandLineUtils.h"

std::string getAbsolutePath(std::string path)
{
	filesystem::path exePath = filesystem::current_path();

	if (!ofFilePath::isAbsolute(path))
	{
		path = ofFilePath::join(exePath, path);
	}
	return path;
}

cxxopts::ParseResult parse(int argc, char *argv[])
{
	try
	{
		cxxopts::Options options(argv[0], " - midi monitor and sender");
		options.add_options()("l,list", "list")("p,port", "port", cxxopts::value<int>())("v,virtualPort", "virtualPort", cxxopts::value<std::string>()->default_value("ofMIDIDebugger"))("i,interactive", "interactive")
		("j,input", "input", cxxopts::value<std::string>())
		("o,output", "output", cxxopts::value<std::string>())
		("m,message", "message", cxxopts::value<std::string>());
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

	if (result.count("input") > 0)
	{
		ofLogNotice() << "input from File!";
		// ofRunApp(new ofApp(result["host"].as<std::string>(), result["port"].as<int>(), getAbsolutePath(result["input"].as<std::string>())));
	}
	if (result.count("output") > 0)
	{
		if (result.count("port") > 0)
		{
			auto port = result["port"].as<int>();
			auto outputPath = getAbsolutePath(result["output"].as<std::string>());
			ofRunApp(new ofApp(port, true, outputPath));
		}
		else if (result.count("virtualPort") > 0)
		{
			auto port = result["virtualPort"].as<std::string>();
			auto outputPath = getAbsolutePath(result["output"].as<std::string>());
			ofRunApp(new ofApp(port, true, outputPath));
		}
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
	} else // sender
	{
		if (result.count("port") > 0)
		{
			ofRunApp(new ofApp(result["port"].as<int>(), result["message"].as<std::string>(), result["interactive"].as<bool>()));
		}
		else if (result.count("virtualPort") > 0)
		{
			ofRunApp(new ofApp(result["virtualPort"].as<std::string>(), result["message"].as<std::string>(), result["interactive"].as<bool>()));
		}
	}
	return 0;
}