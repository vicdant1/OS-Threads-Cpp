#pragma once
#include <vector>
class Matrix
{
public:
	Matrix();
	int GetN();
	int GetM();
	void SetN(int n);
	void SetM(int m);
	std::vector<std::vector<int>> body;
private:
	int n;
	int m;

};