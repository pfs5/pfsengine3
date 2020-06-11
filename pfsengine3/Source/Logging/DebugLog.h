#pragma once
#include "Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
#define DEBUG_LOG(...) \
	PDebugLog::LogMessage(PString::Printf(__VA_ARGS__))
// ----------------------------------------------------------------------------
namespace PDebugLog
{
	enum class ELogType
	{
		Log,
		Warning,
		Error
	};

	/**
	 * Log debug message.
	 */
	void LogMessage(const PString& message, ELogType logType = ELogType::Log);
	void LogMessage(const char* message, ELogType logType = ELogType::Log);

	// Private
	namespace
	{
		PString LogTypeToString(ELogType logType)
		{
			switch (logType)
			{
				case ELogType::Log:
					return "[Log]";
				case ELogType::Warning:
					return "[Warning]";
				case ELogType::Error:
					return "[Error]";
				default:
					return "[None]";
			}
		}
	}
}
// ----------------------------------------------------------------------------