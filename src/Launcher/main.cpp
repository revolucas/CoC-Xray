#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <string>

int main(int argc, char* argv[])
{
	std::string argv_str(argv[0]);
	std::string workingDir = argv_str.substr(0, argv_str.find_last_of("\\"));
	std::string pathToExe = workingDir + "\\bin\\xrEngine.exe";

	// combine the rest of the arguments into a single string
	std::string command_line;
	for (int i = 1; i < argc; i++)
		command_line += argv[i];

	// additional information
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcessA
	(
		pathToExe.c_str(),   // the path
		(LPSTR)command_line.c_str(),                // Command line
		NULL,                   // Process handle not inheritable
		NULL,                   // Thread handle not inheritable
		FALSE,                  // Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE,     // Opens file in a separate console
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi           // Pointer to PROCESS_INFORMATION structure
	);
	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}