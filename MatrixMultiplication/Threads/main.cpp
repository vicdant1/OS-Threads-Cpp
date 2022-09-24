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
  if (argc < 4)
    cout << "Quantidade de parâmetros inválida\n";

  // Creating fake matrix
  Matrix *m1 = new Matrix();
  Matrix *m2 = new Matrix();

  m1->n = 3;
  m1->m = 3;

  m2->n = 3;
  m2->m = 3;

  for(int i = 0; i < m1->n; i++)
  {
    m1->body.push_back(vector<int>());
    for(int j = 0; j < m1->m; j++)
    {
      m1->body[i].push_back(rand()%10 +1);
    }
  }

  for(int i = 0; i < m2->n; i++)
  {
    m2->body.push_back(vector<int>());
    for(int j = 0; j < m2->m; j++)
    {
      m2->body[i].push_back(rand()%10 +1);
    }
  }

  for(int i = 0; i < m1->n; i++)
  {
    for(int j = 0; j < m1->m; j++)
    {
      cout << m1->body[i][j] << " ";
    }
    cout << endl;
  }
  
  cout << endl;

  for(int i = 0; i < m2->n; i++)
  {
    for(int j = 0; j < m2->m; j++)
    {
      cout << m2->body[i][j] << " ";
    }
    cout << endl;
  }

  
  
  return 0;
}