#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define str(s) #s

void dest(void* ptr)
{
	free(ptr);
	ptr = NULL;
}
char* read(const char* fn)
{
	char* buffer = NULL;
	FILE* file = fopen(fn, "r");
	if(file != NULL)
	{
		if(fseek(file, 0L, SEEK_END) == 0)
		{
			long bufsize = ftell(file);
			assert(bufsize != -1);
			buffer = /*(char*)*/malloc(sizeof(char)*(bufsize+1));
			assert(fseek(file, 0L, SEEK_SET) == 0);
			size_t len = fread(buffer, sizeof(char), bufsize, file);
			if(ferror(file) != 0) {fputs("Error", stderr);}
			else {buffer[len++] = '\0';}
		}
		fclose(file);
	}
	return buffer;
}
void write(const char* fn, const char* data)
{
	FILE* file = fopen(fn, "w");
	fputs(data, file);
	fclose(file);
}
void consoleOut(const char* fn)
{
	char call[100];
	strcpy(call, "IF EXIST ");
	strcat(call, fn);
	strcat(call, " ( rm ");
	strcat(call, fn);
	strcat(call, " )");
	FILE* pipe = popen(call, "w");
	pclose(pipe);
}
int main(int argc, char** argv)
{
	double start = time(0), end;
	char* fn = argv[1], * destination = argv[2];
	int testCount = atoi(argv[3]);
	int /*bool*/ destroyAfter = 0;
	if(argc == 5) {destroyAfter = atoi(argv[4]);}
	printf("new file name: %s\n", destination);
	printf("Starting test, reading file %s %d times\n-----------------------\n", fn, testCount);
	for(int i = 0; i < testCount; i++)
	{
		char* data = read(fn);
		if(data != NULL)
		{
			write(destination, data);
			dest(data);
			if(destroyAfter) {consoleOut(destination);}
		}
		else {puts("Data is null!\n");}
	}
	printf("Deleting %s\n", str(destination));
	dest(destination);
	printf("Deleting %s\n", str(fn));
	dest(fn);
	end = time(0);
	printf("Time elapsed: %f\n", difftime(end, start));
	return 0;
}

