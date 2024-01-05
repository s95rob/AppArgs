// Given shell arguments: a b c d

#include "AppArgs.h"

int main(int argc, char** argv) {
	AppArgs::Args args(argc, argv);
	
	// Print all arguments
	for (int i = 0; i < args.Size(); i++) {
		std::cout << "args[" << i << "]: " << args[i] << '\n';
	}

	// Find argument "a" and print argument "b"
	auto* foundArg = args.Find("a");
	if (foundArg && foundArg->Next()) {
		std::cout << "Found next arg after 'a': " << foundArg->Next() << '\n';
	}

	return 0;
}