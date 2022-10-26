#pragma once
#pragma once

#include "Application.h"
#include <string>
#include <vector>

using namespace std;


struct DebugConsole
{
	DebugConsole(string msg, string f, LogType ty) : msg(msg), type(ty), file(f) {};
	string msg;
	string file;
	LogType type;
};

class Console
{
public:

	static void PrintDebug();
	static void DebugConsole(string format, string file, LogType type);


private:

	static vector<struct DebugConsole> logs;
	static vector<struct DebugConsole> logsCopy;
};