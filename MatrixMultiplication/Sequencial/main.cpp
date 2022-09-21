#include <iostream>
#include "Sequencial.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Par�metros inv�lidos. Revise e tente novamente\n";
		exit(0);
	}

	Sequencial* sequencialManager = new Sequencial();

	string m1Path = argv[1];
	string m2Path = argv[2];

	sequencialManager->ReadFile(m1Path, m2Path);
	sequencialManager->CalculateResult();
}