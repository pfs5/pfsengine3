#pragma once
#include "Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
#define DEBUG_LOG(...) \
	PDebugLog::LogMessage(PString::Printf(__VA_ARGS__))
// ----------------------------------------------------------------------------
namespace PDebugLog
{
	/**
	 * Log debug message.
	 */
	void LogMessage(const PString& message);
	void LogMessage(const char* message);
}
// ----------------------------------------------------------------------------