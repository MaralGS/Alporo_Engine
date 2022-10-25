#pragma once
#pragma once

#include "Application.h"
#include <string>
#include <vector>

using namespace std;


struct DebugLogs
{
	DebugLogs(string st, string f, LogType ty) : st(st), repts(1), type(ty), file(f) {};

	string st;
	string file;
	int repts;
	LogType type;
};

class Logs
{
public:

	static void PrintDebug();
	static void DebugLog(string format, string file, LogType type = LogType::LOGS);
	static void UnCollapseDebug();


private:

	static vector<DebugLogs> logs;
	static vector<DebugLogs> logsCopy;

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