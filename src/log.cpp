#include "log.h"

//DECLARATION
Log theLog;

void Log::insertStream(std::ostream* stream)
{
	if(stream) {
		std::vector<std::ostream*>::iterator it = std::find(mStreams.begin(), mStreams.end(), stream);
		if(it == mStreams.end()) {
			mStreams.push_back(stream);
			writeHeader(stream);
		}
	}
}

void Log::removeStream(std::ostream* stream)
{
	std::vector<std::ostream*>::iterator it = std::find(mStreams.begin(), mStreams.end(), stream);
	if(it != mStreams.end()) {
		writeFooter(stream);
		mStreams.erase(it);
	}
}

void Log::writeInfo(std::string& message)
{
	std::string m;
	m = getTime() + ": " + message;
	write(m.c_str());
}

void Log::writeDebug(std::string& message)
{
	std::string m;
	m = getTime() + ": DEBUG - " + message;
	write(m.c_str());
}

void Log::writeWarning(std::string& message)
{
	std::string m;
	m = getTime() + ": WARNING - " + message;
	write(m.c_str());
}

void Log::writeError(std::string& message)
{
	std::string m;
	m = getTime() + ": ERROR!!! - " + message;
	write(m.c_str());
}

std::string Log::getDate()
{
    std::stringstream wss;

    SYSTEMTIME sysTime;
    ::GetLocalTime(&sysTime);

    wss << std::setfill('0');
    wss << sysTime.wYear << "-" << std::setw(2)
        << sysTime.wMonth << "-" << std::setw(2)
        << sysTime.wDay;

    return wss.str();
}

std::string Log::getTime()
{
    std::stringstream wss;

    SYSTEMTIME sysTime;
    ::GetLocalTime(&sysTime);

    wss << std::setfill('0');
    wss << sysTime.wHour << ":" << std::setw(2)
        << sysTime.wMinute << ":" << std::setw(2)
        << sysTime.wSecond;

    return wss.str();
}

void Log::writeHeader(std::ostream* stream)
{
	std::string m;
	m = "[ Log stream opened on " + getDate() + " at " + getTime() + " ]";
	write(m.c_str());
}

void Log::writeFooter(std::ostream* stream)
{
	std::string m;
	m = "[ Log stream closed on " + getDate() + " at " + getTime() + " ]";
	write(m.c_str());
}

void Log::write(const char* message)
{
	size_t sz = mStreams.size();
	std::ostream* stream;
	for(size_t i=0; i<sz; ++i) {
		stream = mStreams[i];
		if(stream) {
			(*stream) << message << std::endl;
		}
	}
}