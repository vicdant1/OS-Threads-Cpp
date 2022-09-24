#pragma once
#include <vector>
#include <string>
#include "Matrix.hpp"

#ifndef Sequencial_hpp
#define Sequencial_hpp

class Sequencial
{
public:
	Sequencial();
	void ReadFile(std::string m1FilePath, std::string m2FilePath);
	void CalculateResult();
private:
	Matrix* m1;
	Matrix* m2;
	Matrix* mResult;

};

#endif // !Sequencial_hppequencial_hpp
