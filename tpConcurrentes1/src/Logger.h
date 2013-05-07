#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <sstream>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
/* El logeo debe ser activado mediante la variable debug
 */
class Logger {
public:
	Logger();
	~Logger();
	static void log(string mensaje);
	static void setDebug();

private:
	static int debug;
	static string itos(int num);

};

#endif /* LOGGER_H_ */
