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
	logger & operator<<(const T& t) {
		if (!this->m_outFile.is_open()) {
			throw badfile();
		}
		if (this->m_isFirstInput) {
			this->m_buffer << this->m_prefix;
			this->m_isFirstInput = false;
		}
		this->m_buffer << t;
		return *this;
	}

	// И тут...
	logger& operator<<(std::ostream& (*var)(std::ostream&)) {
		if (!this->m_outFile.is_open()) {
			throw badfile();
		}
		this->m_buffer << std::endl;
		this->writeInFile();
		this->clearBuf();
		return *this;
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
