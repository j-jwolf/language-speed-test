#include <iostream>
#include <cstring>
#include <ctime>
#include <thread>
#include <memory>
#include <stdexcept>
using namespace std;

template<typename Func, typename ... Args> thread makeThread(Func&& func, Args&&... args) {return thread(func, forward<Args>(args)...);}
template<typename T> using Ptr = unique_ptr<T>;
template<typename T, typename ... Args> Ptr<T> makePointer(Args&&... args) {return Ptr<T>(new T(forward<Args>(args)...));}
void runThread(const string& fn, string* args, const int& argc)
{
	string call = fn+".exe";
	for(int i = 0; i < argc; i++) {call += " "+*(args+i)}
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(call.c_str(), "w"), pclose);
}
int main(int argc, char** argv)
{
	string cpp = "main", c = "test", fn = argv[1];
	for(int i = 0; i < 1000; i++)
	{
		//
	}
	return 0;
}



