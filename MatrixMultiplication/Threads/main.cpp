#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix() {}
  vector<vector<int>> body;
  int n;
  int m;
};

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Quantidade de parâmetros inválida\n";
    exit(0);
  }

  // Creating fake matrix
  Matrix *m1 = new Matrix();
  Matrix *m2 = new Matrix();
  Matrix *mr = new Matrix();

  m1->n = 3;
  m1->m = 3;

  m2->n = 3;
  m2->m = 3;

  for (int i = 0; i < m1->n; i++) {
    m1->body.push_back(vector<int>());
    for (int j = 0; j < m1->m; j++) {
      m1->body[i].push_back(rand() % 10 + 1);
    }
  }

  for (int i = 0; i < m2->n; i++) {
    m2->body.push_back(vector<int>());
    for (int j = 0; j < m2->m; j++) {
      m2->body[i].push_back(rand() % 10 + 1);
    }
  }

  // printing fake matrix
  for (int i = 0; i < m1->n; i++) {
    for (int j = 0; j < m1->m; j++) {
      cout << m1->body[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;

  for (int i = 0; i < m2->n; i++) {
    for (int j = 0; j < m2->m; j++) {
      cout << m2->body[i][j] << " ";
    }
    cout << endl;
  }

  // feeding result matrix

  mr->n = m1->n;
  mr->m =  m2->m;
  for(int i = 0; i < mr->n; i++)
  {
    mr->body.push_back(vector<int>());
    for(int j = 0; j < mr->m; i++)
    {
      mr->body[i].push_back(0);
    }
  }

  int p = atoi(argv[3]);
  cout << "Valor de p: " << p << endl;

  cout << "Matriz final terá dimensões: " << mr->n << "x" << mr->m << endl;

  int totalElementCounter = mr->n * mr->m;
  int threadsNumber = totalElementCounter / p;
  
  if(totalElementCounter % p > 0) 
    threadsNumber++;

  cout << "Numero de threads criadas: " << threadsNumber << endl;

  
  
  return 0;
}