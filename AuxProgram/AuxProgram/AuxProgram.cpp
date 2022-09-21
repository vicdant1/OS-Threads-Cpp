#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#endif

#include "Utilities.h"

int matrixCounter = 0;

std::vector<std::vector<int>> GenerateMatrix(int n, int m)
{
	std::vector<std::vector<int>> matriz;
	for (int i = 0; i < n; i++)
	{
		matriz.push_back(std::vector<int>());
		for (int j = 0; j < m; j++)
		{
			matriz[i].push_back(rand()%10 + 1);
		}
	}

	Sleep(1000);

	return matriz;
}

namespace fs = std::filesystem;
void CreateFile(std::vector<std::vector<int>> matrix, int n, int m)
{
	matrixCounter++;

	fs::path workingDir(fs::current_path());
	fs::current_path(workingDir);
	auto currentpath = workingDir.parent_path().parent_path();
	std::string targetPathString = fs::absolute(currentpath).string() + "\\ProjectAssets\\";
	std::string targetFileName = targetPathString+ "M" + std::to_string(matrixCounter) + ".txt";

	std::ofstream file(targetFileName);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			file << matrix[i][j] << " ";
		}

		file << "\n";
	}

	Sleep(1000);

	file.close();
}

int main(int argc, char* argv[])
{
	if (argc <= 4)
	{
		std::cout << "Numero de parâmetros inválido\n";
		exit(0);
	}

	int n1 = atoi(argv[1]);
	int m1 = atoi(argv[1]);
	int n2 = atoi(argv[1]);
	int m2 = atoi(argv[1]);

	unsigned seed = time(0);
	srand(seed);

	auto matrix1 = GenerateMatrix(n1, m1);
	auto matrix2 = GenerateMatrix(n2,m2);

	CreateFile(matrix1, n1, m1);
	CreateFile(matrix2, n2, m2);
}