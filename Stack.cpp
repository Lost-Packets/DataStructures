// Nathan Ploos Van Amstel

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

using namespace std;

struct Node {
  float data;
  Node *next;
};

class Stack {
private:
  Node *listpointer;

public:
  Stack();
  ~Stack();
  void Push(float newThing);
  void Pop();
  float Top();
  bool isEmpty();
};

Stack::Stack() { listpointer = NULL; }

Stack::~Stack() {
  if (listpointer != NULL) {
    delete listpointer;
  }
}

void Stack::Push(float newThing) {
  Node *temp;
  temp = new Node;
  temp->data = newThing;
  temp->next = listpointer;
  listpointer = temp;
}

void Stack::Pop() {
  Node *p;
  p = listpointer;
  if (listpointer != NULL) {
    listpointer = listpointer->next;
    delete p;
  }
}

float Stack::Top() { return listpointer->data; }

bool Stack::isEmpty() {
  if (listpointer == NULL) {
    return true;
  }
  return false;
}

/* implement your stack here */

int main(int argc, char **argv) { // get arguments from command line, i.e., yourexec filename
  int number, i;
  float result, op1, op2;
  char oper;
  Stack A;
  string expression;
  ifstream input_file;
  if (argc != 2) {
    cout << "needs a filename as argument  " << endl;
    exit(0);
  }
  input_file.open(argv[1]);
  if (!input_file.good()) {
    cout << "cannot read file " << argv[1] << endl;
    exit(0);
  }
  while (!input_file.eof()) {
    getline(input_file, expression);
    if (isdigit(expression[0])) {
      stringstream line(expression);
      line >> number;
      cout << "reading number " << number << endl;
      A.Push(number);
    } else {
      if (expression[0] == '+' || expression[0] == '-' ||
          expression[0] == '/' || expression[0] == '*') {
        stringstream line(expression);
        line >> oper;
        cout << "reading operator " << oper << endl;

        if (A.isEmpty()) {
          cout << "To many operators" << endl;
          exit(0);
        } else {
          op2 = A.Top();
          A.Pop();
        }

        if (A.isEmpty()) {
          cout << "To many operators" << endl;
          exit(0);
        } else {
          op1 = A.Top();
          A.Pop();
        }

        if (oper == '+') {
          result = op2 + op1;
        }
        if (oper == '*') {
          result = op2 * op1;
        }
        if (oper == '-') {
          result = op2 - op1;
        }
        if (oper == '/') {
          result = op1 / op2;
        }

        A.Push(result);
      }
    }
  }

  result = A.Top();
  A.Pop();
  if (A.isEmpty() != true) {
    cout << "To many numbers" << endl;
    exit(0);
  }
  cout << "The result is " << result << endl;
  // A.~Stack();
}
