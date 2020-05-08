#include <iostream>
#include "DebugLog.h"
// ----------------------------------------------------------------------------
void PDebugLog::LogMessage(const PString& message)
{
	std::cout << "[DebugLog] " << message << std::endl;;
}
// ----------------------------------------------------------------------------
void PDebugLog::LogMessage(const char* message)
{
	std::cout << "[DebugLog] " << message << std::endl;;
}
// ----------------------------------------------------------------------------