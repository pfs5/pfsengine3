#include "DebugLog.h"
#include <iostream>
// ----------------------------------------------------------------------------
void PDebugLog::LogMessage(const PString& message, ELogType logType/* = ELogType::Log*/)
{
	std::cout << "[DebugLog]" << LogTypeToString(logType) << " " << message << std::endl;
}
// ----------------------------------------------------------------------------
void PDebugLog::LogMessage(const char* message, ELogType logType/* = ELogType::Log*/)
{
	std::cout << "[DebugLog]" << LogTypeToString(logType) << " " << message << std::endl;
}
// ----------------------------------------------------------------------------