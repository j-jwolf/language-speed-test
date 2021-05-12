#include <thread>
#include <memory>
using namespace std;

template<typename T> using Ptr = unique_ptr<T>;
template<typename T, typename ... Args> Ptr<T> makePointer(Args&&... args) {return Ptr<T>(new T(forward<Args>(args)...));}
template<typename Func, typename ... Args> thread makeThread(Func&& func, Args&&... args) {return thread(func, forward<Args>(args)...);}
template<typename Func, typename ... Args> thread callThread(Func&& func, int& counter, Args&&... args) {counter++; return thread(funct, forward<Args>(args)...);}
void joinThread(thread& t, int& counter) {counter--; t.join();}

