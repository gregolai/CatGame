#ifndef LOG_H
#define LOG_H

#include <windows.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class Log
{
public:
	void insertStream(std::ostream* stream);
	void removeStream(std::ostream* stream);

	void writeInfo(std::string& message);
	void writeDebug(std::string& message);
	void writeWarning(std::string& message);
	void writeError(std::string& message);

	inline std::vector<std::ostream*>& getStreams() { return mStreams; }

	std::string getDate();
	std::string getTime();

	inline size_t streamCount() { return mStreams.size(); }
private:
	void writeHeader(std::ostream* stream);
	void writeFooter(std::ostream* stream);

	void write(const char* message);

	std::vector<std::ostream*> mStreams;
};

extern Log theLog;

#define STR(msg)		std::string(msg)

#define log_open(ostream_ref)	theLog.insertStream(&(ostream_ref));
#define log_close(ostream_ref)	theLog.removeStream(&(ostream_ref))

#define log_info(msg)			theLog.writeInfo(std::string(msg))
#ifdef _DEBUG
	#define log_debug(msg)		theLog.writeDebug(std::string(msg))
#else
	#define log_debug(msg)		
#endif
#define log_warning(msg)	theLog.writeWarning(std::string(msg))
#define log_error(msg)		theLog.writeError(std::string(msg))

#endif