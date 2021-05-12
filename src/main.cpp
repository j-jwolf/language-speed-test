#include <cstdio>
#include <fstream>
#include <cstring>
#include <memory>
#include <array>
#include <stdexcept>
#include <thread>
#include <iostream>
using namespace std;

#define fl(i, e) for(i = 0; i < e; i++)

class Timer
{
	double _start;
	double _end;
public:
	Timer() {}
	~Timer() {}
	void start() {_start = time(0);}
	void stop() {_end = time(0);}
	double getTime() {return difftime(_end, _start);}
};
template<typename Func, typename ... Args> thread makeThread(Func&& func, Args&&... args) {return thread(func, forward<Args>(args)...);}
string line()
{
	string s = "";
	int i;
	fl(i, 40) {s += "=";}
	return s+"\n";
}
string consoleIn(const string& command)
{
	array<char, 256> buffer;
	string out;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
	if(!pipe) {throw runtime_error("Pipe failed to open");}
	while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {out += buffer.data();}
	return out;
}
string readFile(const string& fn)
{
	fstream file(fn, ios::in);
	string input, data = "";
	while(getline(file, input)) {data += input+"\n";}
	return data;
}
void runThread(const string& command, const string& fn)
{
	fstream file;
	Timer t;
	t.start();
	string results = consoleIn(command);
	t.stop();
	file.open(fn, ios::out);
	file << results << "TIME FROM MAIN: " << t.getTime() << endl;
	file.close();
}
int main(int argc, char** argv)
{
	string resultfn = ((argc > 1) ? argv[1] : "test_results.txt");
	string c = "c_test.exe c_mb.txt c_mb2.txt 1000 0", cpp = "cpp_test.exe cpp_mb.txt cpp_mb2.txt 1000 0", java = "java Test java_mb.txt java_mb2.txt 1000 0", py = "python test.py py_mb.txt py_mb2.txt 1000 0";
	string cresults = "", cppresults = "", javaresults = "", pyresults = "";
	string cpp_out = "cpp_output.txt", c_out = "c_output.txt", java_out = "java_output.txt", py_out = "py_output.txt";
	thread cthread = makeThread(runThread, c, c_out);
	thread cppthread = makeThread(runThread, cpp, cpp_out);
	thread javathread = makeThread(runThread, java, java_out);
	thread pythread = makeThread(runThread, py, py_out);
	cthread.join();
	cppthread.join();
	javathread.join();
	pythread.join();
	fstream file;
	cresults += readFile(c_out);
	cppresults += readFile(cpp_out);
	javaresults += readFile(java_out);
	pyresults += readFile(py_out);
	string data = "C RESULTS\n"+line()+cresults+"\nC++ RESULTS\n"+line()+cppresults+"\nJAVA RESULTS\n"+line()+javaresults+"\nPYTHON RESULTS\n"+line()+pyresults;
	file.open(resultfn, ios::out);
	file << data << endl;
	file.close();
	cout << "End of test, results written to " << resultfn << endl;
	return 0;
}

