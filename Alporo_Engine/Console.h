#pragma once
#pragma once

#include "Application.h"
#include <string>
#include <vector>

using namespace std;


struct DebugConsole
{
	DebugConsole(string st, string f, LogType ty) : st(st), repts(1), type(ty), file(f) {};

	string st;
	string file;
	int repts;
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

	static float colorEdit[3];

	static int countWarn;
	static int countSyst;
	static int countDebug;

	static bool isCollapsed;
	static bool showPath;

	static bool warnignDebug;
	static bool systemDebug;
	static bool msgDebug;
};