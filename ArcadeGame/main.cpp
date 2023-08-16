#include "MyFramework.h"
#include<string>
#include<iostream>

using namespace std;

std::pair<int, int> window_size = { 1000,800 };
void ReadCMDInfo(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	ReadCMDInfo(argc, argv);

	MyFramework* game = new MyFramework;

	game->SetWindowSize(window_size.first,window_size.second);

	return run(game);
}

void ReadCMDInfo(int argc, char* argv[])
{
	for (size_t i = 0; i < argc; i++)
	{
		std::string command = argv[i];

		if (command == "-window")
		{
			window_size.first = stoi(argv[i + 1]);
			string temp(argv[i + 1]);
			temp.erase(0, to_string(window_size.first).size() + 1);
			window_size.second = stoi(temp);
		}
	}

} 
//I can't work, just can't. 
