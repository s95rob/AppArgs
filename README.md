# AppArgs

Lightweight C++17 command line argument helper class. Turns application arguments into a linked list and allows searching of arguments by string. 

`Example: Logic for loading a file from a "file" flag and succeeding filepath argument string`
```c++
#include "AppArgs.h"

int main(int argc, char** argv) {
	AppArgs::Args args(argc, argv);

	auto* flag = args.Find("-f");
	if (flag) {
		if (!flag->Next()) {
			std::cout << "Filepath unspecified\n";
			return -1;
		}
		else {
			LoadFileFunctionThatTakesAFilepathString(flag->Next());
		}
	}

	return 0;
}
```