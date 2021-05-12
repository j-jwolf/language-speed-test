#include <iostream>
#include <ctime>
#include <memory>
#include <fstream>
#include <stdexcept>
using namespace std;

string read(const string& fn)
{
	fstream file(fn, ios::in);
	if(!file) {file.close(); throw runtime_error(fn+" was not found");}
	string input, data = "";
	while(getline(file, input)) {data += input+"\n";}
	file.close();
	return data;
}
void write(const string& fn, const string& data)
{
	fstream file(fn, ios::out);
	file << data;
	file.close();
}
void consoleOut(const string& fn)
{
	string call = "IF EXIST "+fn+" ( rm "+fn+" )";
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(call.c_str(), "w"), pclose);
}
int main(int argc, char** argv)
{
	double start = time(0), end;
	string fn = argv[1], destination = argv[2];
	int testCount;
	bool destroyAfter;
	try
	{
		testCount = stoi(argv[3]);
		destroyAfter = stoi(argv[4]);
	} catch(invalid_argument& ia) {throw;}
	cout << "new file name: " << destination << endl;
	cout << "Starting test, reading file " << fn << " " << testCount << " times\n-----------------------" << endl;
	for(int i = 0; i < testCount; i++)
	{
		string data = read(fn);
		if(data != "")
		{
			write(destination, data);
			if(destroyAfter) {consoleOut(destination);}
		}
		else {cout << "Data is null!" << endl;}
	}
	end = time(0);
	cout << "Time elapsed: " << difftime(end, start) << endl;
	return 0;
}

