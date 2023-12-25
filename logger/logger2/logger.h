#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <string>

#include "loggerExeption.h"

class logger final {

	static inline std::string m_prefix{};
	static inline std::stringstream m_buffer{};
	static inline std::ofstream m_outFile{};
	static inline bool m_isFirstInput{};

public:
	static inline logger& getInstance() {
		static logger instance ;
		return instance;
	}

	static inline void logstream(const std::string& prefix = std::string()) {
		m_prefix = prefix;
	}

	static inline void setLogFile(const std::string& name, std::ios::openmode mode = std::ios::app){
		if (m_outFile.is_open()) {
			writeInFile();
			clearBuf();
		}

		m_outFile = std::ofstream(name,mode);
	}

	// А вот зачем здесь friend?? 
	// думаю t можно передавать просто по константой ссылке
	template<typename T>
	friend logger & operator<<(logger & log, T && t) {
		if (!log.m_outFile.is_open()) {
			throw badfile();
		}
		if (log.m_isFirstInput) {
			log.m_buffer << log.m_prefix;
			log.m_isFirstInput = false;
		}
		log.m_buffer << t;
		return log;
	}

	// И тут...
	friend logger& operator<<(logger& log, std::ostream& (*var)(std::ostream&)) {
		if (!log.m_outFile.is_open()) {
			throw badfile();
		}
		log.m_buffer << std::endl;
		log.writeInFile();
		log.clearBuf();
		return log;
	}

private:
	logger() = default;
	logger(const logger&) = delete;
	void operator=(const logger&) = delete;

	~logger() {
		writeInFile();
	}

	static void writeInFile() {
		if (m_outFile.is_open()) {
			m_outFile << m_buffer.str();
			m_outFile.flush();
		}
		else {
			throw badfile();
		}
	}

	static void clearBuf() {
		m_buffer.str("");
		m_isFirstInput = true;
	}
};
