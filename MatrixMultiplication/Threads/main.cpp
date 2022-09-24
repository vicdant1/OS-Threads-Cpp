#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

class Matrix 
{
public:
  Matrix() {}
  vector<vector<int>> body;
  int n;
  int m;
};

// Global variables
int p = 0;
Matrix *m1 = new Matrix();
Matrix *m2 = new Matrix();
Matrix *mr = new Matrix();

void *ThreadCalc(void *tid) 
{
  int currentRow = (p * (size_t)tid) / mr->n;
  int currentColumn = (p * (size_t)tid) % mr->m;

  for (int i = 0; i < p; i++) 
  {
    for (int j = 0; j < mr->m; j++) 
      mr->body[currentRow][currentColumn] += m1->body[currentRow][j] * m2->body[j][currentColumn];

    cout << "c" << currentRow << currentColumn << " " << mr->body[currentRow][currentColumn] << endl;

    currentColumn++;
    if (currentColumn == mr->m) 
    {
      currentRow++;
      currentColumn = 0;
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
  if (argc < 4) 
  {
    cout << "Quantidade de parâmetros inválida\n";
    exit(0);
  }

  // Creating fake matrix
  m1->n = 100;
  m1->m = 100;

  m2->n = 100;
  m2->m = 100;

  for (int i = 0; i < m1->n; i++) 
  {
    m1->body.push_back(vector<int>());
    for (int j = 0; j < m1->m; j++) 
      m1->body[i].push_back(rand() % 10 + 1);
  }

  for (int i = 0; i < m2->n; i++) 
  {
    m2->body.push_back(vector<int>());
    for (int j = 0; j < m2->m; j++) 
      m2->body[i].push_back(rand() % 10 + 1);
  }

  // feeding result matrix
  mr->n = m1->n;
  mr->m = m2->m;
  for (int i = 0; i < mr->n; i++) 
  {
    mr->body.push_back(vector<int>());
    for (int j = 0; j < mr->m; j++) 
      mr->body[i].push_back(0);
  }

  p = atoi(argv[3]);

  cout << "Valor de p: " << p << endl;
  cout << "Matriz final terá dimensões: " << mr->n << "x" << mr->m << endl;

  int totalElementCounter = mr->n * mr->m;
  int threadsNumber = totalElementCounter / p;

  if (totalElementCounter % p > 0)
    threadsNumber++;

  // Creating threads
  pthread_t threads[threadsNumber];
  int status = 0;

  cout << "Numero de threads criadas: " << threadsNumber << endl;

  for (int i = 0; i < threadsNumber; i++) 
    status = pthread_create(&threads[i], NULL, ThreadCalc, (void *)(size_t)i);

  for (int i = 0; i < threadsNumber; i++) 
    pthread_join(threads[i], NULL);

  return 0;
}