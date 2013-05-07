#include "Logger.h"
#include "LockFile.h"

#define BUFFSIZE 25
#define ARCHIVOLOG "log.txt"

Logger::Logger() {
}

Logger::~Logger() {
}

int Logger::debug = 0;

void Logger::log(string mensaje) {
	if (!debug)
		return;
	LockFile lock((char*) ARCHIVOLOG);
	lock.tomarLock();

	//Obtengo la fecha
	time_t timeAux;
	struct tm * timeinfo;
	char buffer[BUFFSIZE];
	time(&timeAux);
	timeinfo = localtime(&timeAux);
	strftime(buffer, BUFFSIZE, "%F %T ", timeinfo);
	string res = string(buffer);
	res.append("[pid: ");

	//Escribo el PID tambien
	string pid = itos(getpid());
	res.append(pid);
	res.append("] ");
	res.append(mensaje);
	res.append("\n");
	lock.escribir((char*) res.c_str(), (int) res.size());
	lock.liberarLock();
	cout << res.c_str();
}

string Logger::itos(int number) {
	stringstream salida;
	salida << number;
	return salida.str();
}

void Logger::setDebug() {
	Logger::debug = 1;
}

void Logger::emptyLog() {
	remove(ARCHIVOLOG);
}
