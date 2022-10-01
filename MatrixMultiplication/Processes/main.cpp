#include <chrono>
#include <unistd.h>
#include <experimental/filesystem>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix() {}
  vector<vector<int>> body;
  int n;
  int m;
};

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

// Global variables
int p = 0;
Matrix *m1 = new Matrix();
Matrix *m2 = new Matrix();
Matrix *mr = new Matrix();

// Evaluation function
namespace fs = experimental::filesystem;
void * ProcessCalc(int pid, int exec) 
{
  fs::path workingDir(fs::current_path());
  auto targetPath = workingDir.parent_path().parent_path();
  string targetFilePath = fs::absolute(targetPath).string() +
                          "/ProjectAssets/Results/Processes/" + to_string(mr->n) + "x" +
                          to_string(mr->m) + "/exec_" + to_string(exec) + "/";
  string targetFileName = targetFilePath + to_string(mr->n) + "x" +
                          to_string(mr->m) + "_process_" +
                          to_string((size_t)pid) + ".txt";

  if (!fs::exists(targetFilePath))
    fs::create_directories(targetFilePath);
  ofstream outFile(targetFileName);

  cout << "executing process " << (int) pid << endl;

  int currentRow = (p * pid) / mr->n;
  int currentColumn = (p * pid) % mr->m;

  for (int i = 0; i < p; i++) {
    int sum = 0;

    // begins timecouting
    auto begin = chrono::system_clock::now();
    for(int j = 0; j < mr->m; j++)
        sum += m1->body[currentRow][j] * m2->body[j][currentColumn];
  
    // ends timecounting
    // sleep(3); debuging
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    // inserting data on file
    outFile << "c" << currentRow + 1 << currentColumn + 1 << " "
            << sum << " " << duration << endl;

    currentColumn++;
    if (currentColumn == mr->m) 
    {
      currentRow++;
      currentColumn = 0;
    }
  }

  outFile.close();  
}

int main(int argc, char *argv[]) {
  if (argc < 4) 
  {
    cout << "Quantidade de parâmetros inválida\n";
    exit(0);
  }

  // Reading files
  string m1Path = argv[1];
  string m2Path = argv[2];

  ifstream m1File(m1Path);
  string line;
  int lineCounter = 0;
  int columnCounter = 0;
  while (getline(m1File, line)) {
    m1->body.push_back(vector<int>());

    line = Utils::Trim(line);
    vector<string> elements = Utils::Split(line, " ");

    for (auto element : elements)
      m1->body[lineCounter].push_back(stoi((element)));

    lineCounter++;
  }
  columnCounter = m1->body[0].size();
  m1->n = lineCounter;
  m1->m = columnCounter;
  m1File.close();

  ifstream m2File(m2Path);
  line = "";
  lineCounter = 0;
  columnCounter = 0;
  while (getline(m2File, line)) {
    m2->body.push_back(vector<int>());

    line = Utils::Trim(line);
    vector<string> elements = Utils::Split(line, " ");

    for (auto element : elements)
      m2->body[lineCounter].push_back(stoi((element)));

    lineCounter++;
  }
  columnCounter = m2->body[0].size();
  m2->n = lineCounter;
  m2->m = columnCounter;
  m2File.close();

  // feeding result matrix
  mr->n = m1->n;
  mr->m = m2->m;
  for (int i = 0; i < mr->n; i++) {
    mr->body.push_back(vector<int>());
    for (int j = 0; j < mr->m; j++)
      mr->body[i].push_back(0);
  }

  p = atoi(argv[3]);

  cout << "Valor de p: " << p << endl;
  cout << "Matriz final terá dimensões: " << mr->n << "x" << mr->m << endl;

  int totalElementCounter = mr->n * mr->m;
  int processesNumber = totalElementCounter / p;

  if (totalElementCounter % p > 0)
    processesNumber++;

  cout << "Numero de processos criadas: " << processesNumber << endl;

  int exec = atoi(argv[4]);
  pid_t processes[processesNumber];
  for(int i = 0; i < processesNumber; i++)
  {
    processes[i] = fork();

    if(processes[i] < 0)
    {
        cout << "Não foi possível criar o processo " << i << "." << endl;
        exit(-1);
    }
    else if(processes[i] == 0)
    {
        ProcessCalc(i, exec);
        exit(0);
    }
  }

  for(int i = 0; i < processesNumber; i++)
    wait(NULL);

  return 0;
}