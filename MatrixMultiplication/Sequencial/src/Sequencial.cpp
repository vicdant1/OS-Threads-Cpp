#include "Sequencial.hpp"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Utils {
std::string toRemove = " \n\r\t\f\v";

std::string LeftTrim(const std::string &s) {
  auto start = s.find_first_not_of(toRemove);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string RightTrim(const std::string &s) {
  auto end = s.find_last_not_of(toRemove);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string Trim(const std::string &s) { return RightTrim(LeftTrim(s)); }

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

} // namespace Utils

namespace fs = std::filesystem;
using namespace std;

Sequencial::Sequencial() {
  this->m1 = new Matrix();
  this->m2 = new Matrix();
  this->mResult = new Matrix();
}

void Sequencial::ReadFile(string m1FilePath, string m2FilePath) {
  if (!fs::exists(m1FilePath) || !fs::exists(m2FilePath)) {
    cout << "Algum arquivo inválido.\n";
    exit(0);
  }

  ifstream m1(m1FilePath);
  string line;
  int lineCounter = 0;
  int columnCounter = 0;
  while (getline(m1, line)) {
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
  while (getline(m2, line)) {
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

void Sequencial::CalculateResult() {
  if (this->m1->GetM() != this->m2->GetN()) {
    cout << "Matrizes incompatíveis para realizar multiplicação. N° de colunas "
            "de M1 deve ser igual ao N° de linhas de M2\n";
    exit(0);
  }

  int nFinal = this->m1->GetN();
  int mFinal = this->m2->GetM();

  // Creating filename
  fs::path workingDir(fs::current_path());
  auto targetPath = workingDir.parent_path().parent_path().parent_path();
  auto now = chrono::system_clock::now();
  auto UTC =
      chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
  string targetFilePath = fs::absolute(targetPath).string() +
                          "/ProjectAssets/Results/Sequencial/" + to_string(nFinal) + "x" +
                          to_string(mFinal) + "/";
  string targetFileName = targetFilePath + to_string(UTC) + ".txt";

  if (!fs::exists(targetFilePath))
    fs::create_directories(targetFilePath);

  // Calculating matrix
  auto begin = chrono::system_clock::now();
  for (int i = 0; i < nFinal; i++) {
    this->mResult->body.push_back(vector<int>());
    for (int j = 0; j < mFinal; j++) {
      auto mult = 0;
      for (int c = 0; c < mFinal; c++) {
        mult += this->m1->body[i][c] * this->m2->body[c][j];
      }
      this->mResult->body[i].push_back(mult);
    }
  }
  auto end = chrono::system_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - begin).count();

  ofstream file(targetFileName);
  // Inserting data into file
  file << nFinal << " " << mFinal << endl;
  for (int i = 0; i < nFinal; i++) {
    for (int j = 0; j < mFinal; j++) {
      file << "c" << i + 1 << j + 1 << " " << this->mResult->body[i][j] << endl;
    }
  }
  file << duration;

  file.close();
}