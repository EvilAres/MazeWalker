#include "Logger.h"
#include "cfg.h"
#include <cstdarg>
#include <fstream>
#include <sstream>


namespace MazeWalker {
	
	std::ofstream log_file;

    Logger::Logger() {
		log_file.open(CFG::Instance().getLogFilePath(), std::ios::out | std::ios::app);
		log_file << "\n=============== >> Starting Maze Log << =============\n";
    }

    Logger& Logger::Instance() {
        static Logger logger;
        return logger;
    }

	void Logger::Write(const char* format, ...) {
		char *msg = NULL;
		int msg_len = 0;
		va_list args;
			
		va_start(args, format);
		msg_len = _vscprintf(format, args) + 1;
		if (msg_len > 0) {
			msg = new char[msg_len];
			if (msg) {
				vsprintf_s(msg, msg_len, format, args);
				log_file << msg;
				log_file.flush();
				delete [] msg;
				msg = NULL;
			}
		}
		va_end(args);
    }
}