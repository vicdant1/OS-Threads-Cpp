#include "Matrix.hpp"

Matrix::Matrix()
{
	this->n = 0;
	this->m = 0;
}
int Matrix::GetN()
{
	return this->n;
}
int Matrix::GetM()
{
	return this->m;
}
void Matrix::SetN(int n)
{
	this->n = n;
}
void Matrix::SetM(int m)
{
	this->m = m;
}