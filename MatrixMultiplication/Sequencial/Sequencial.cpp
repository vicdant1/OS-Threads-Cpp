#include "Sequencial.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>


namespace Utils
{
	std::string toRemove = " \n\r\t\f\v";

	std::string LeftTrim(const std::string& s)
	{
		auto start = s.find_first_not_of(toRemove);
		return (start == std::string::npos) ? "" : s.substr(start);
	}

	std::string RightTrim(const std::string& s)
	{
		auto end = s.find_last_not_of(toRemove);
		return (end == std::string::npos) ? "" : s.substr(0, end + 1);
	}

	std::string Trim(const std::string& s)
	{
		return RightTrim(LeftTrim(s));
	}

	std::vector<std::string> Split(std::string s, std::string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}
}


namespace fs = std::filesystem;
using namespace std;

Sequencial::Sequencial()
{
	this->m1 = new Matrix();
	this->m2 = new Matrix();
	this->mResult = new Matrix();

}

void Sequencial::ReadFile(string m1FilePath, string m2FilePath)
{
	if (!fs::exists(m1FilePath) || !fs::exists(m2FilePath))
	{
		cout << "Algum arquivo inválido.\n";
		exit(0);
	}

	ifstream m1(m1FilePath);
	string line;
	int lineCounter = 0;
	int columnCounter = 0;
	while (getline(m1, line))
	{
		this->m1->body.push_back(vector<int>());

		line = Utils::Trim(line);
		vector<string> elements = Utils::Split(line, " ");

		for (auto element : elements)
			this->m1->body[lineCounter].push_back(stoi((element)));

		lineCounter++;
	}
	columnCounter = this->m1->body[0].size();
	this->m1->SetN(lineCounter);
	this->m1->SetM(columnCounter);
	m1.close();

	ifstream m2(m2FilePath);
	line = "";
	lineCounter = 0;
	columnCounter = 0;
	while (getline(m2, line))
	{
		this->m2->body.push_back(vector<int>());

		line = Utils::Trim(line);
		vector<string> elements = Utils::Split(line, " ");

		for (auto element : elements)
			this->m2->body[lineCounter].push_back(stoi((element)));

		lineCounter++;
	}
	columnCounter = this->m2->body[0].size();
	this->m2->SetN(lineCounter);
	this->m2->SetM(columnCounter);
	m2.close();
}

void Sequencial::CalculateResult()
{
	if (this->m1->GetM() != this->m2->GetN())
	{
		cout << "Matrizes incompatíveis para realizar multiplicação. N° de colunas de M1 deve ser igual ao N° de linhas de M2\n";
		exit(0);
	}


	int nFinal = this->m1->GetN();
	int mFinal = this->m2->GetM();

	cout << "Matriz resultante terá dimensões " << nFinal << "x" << mFinal << "\n";

	for (int i = 0; i < nFinal; i++)
	{
		this->mResult->body.push_back(vector<int>());
		for (int j = 0; j < mFinal; j++)
		{
			auto mult = 0;
			for (int c = 0; c < mFinal; c++)
			{
				mult += this->m1->body[i][c] * this->m2->body[c][j];
			}

			this->mResult->body[i].push_back(mult);
		}
	}

	
	// printando matrizes para validar

	/*cout << "M1:\n";
	for (auto row : this->m1->body)
	{
		for (auto element : row)
		{
			cout << element << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";

	cout << "M2:\n";
	for (auto row : this->m2->body)
	{
		for (auto element : row)
		{
			cout << element << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";

	cout << "M1:\n";
	for (auto row : this->mResult->body)
	{
		for (auto element : row)
		{
			cout << element << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";*/
}

void Sequencial::SaveFile()
{
}
