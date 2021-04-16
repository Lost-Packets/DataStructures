// Nathan Ploos Van Amstel

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

template <class T>
class List {
private:
    struct Node {
        T data;
        Node *next;
    };
    Node *front, *current;

public:
    List();
    ~List();
    void AddtoFront(T newthing);
    void Reverse();
    bool FirstItem(T &item);
    bool NextItem(T &item);
};

template <class T>
List<T>::List() {
    front = NULL;
    current = NULL;
}

template <class T>
List<T>::~List() {

}

template <class T>
void List<T>::AddtoFront(T newThing) {
    Node *temp;
    temp = new Node;
    temp->data = newThing;
    temp->next = front;
    front = temp;
}

template <class T>
void List<T>::Reverse() {
    Node *temp1, *temp2;
    current = front->next;
    temp2 = front;
    while(current != NULL){
        temp1 = current->next;
        current->next = front;
        front = current;
        current = temp1;
    }
    temp2->next = NULL;
}

template <class T>
bool List<T>::FirstItem(T &item) {
    if(front == NULL) {return false;}
    item = front->data;
    current = front;
    return true;
}

template <class T>
bool List<T>::NextItem(T &item) {
    if (current == NULL || current->next == NULL) return false;
    current = current->next;
    item = current->data;
    return true;
}

class BigNumber {
private:
    List<int> L1;
public: 
    BigNumber();
    ~BigNumber();
    void ReadFromString(string decstring);
    void PrintBigNumber();
    void AddBigNumbers(BigNumber B1, BigNumber B2);
    void Reverse();
};

BigNumber::BigNumber() { }

BigNumber::~BigNumber() { }

void BigNumber::ReadFromString (string decstring ) {
  for(int i = 0; i < decstring.size(); i++) {
    if(decstring[i]!='\n' && decstring[i]!='\r') {
      int temp=decstring[i]-48;
      L1.AddtoFront(temp);
    }
  }
}

void BigNumber::PrintBigNumber() {
    bool ok;
    int temp;
    L1.Reverse();
    ok = L1.FirstItem(temp);
    while(ok == true){
        printf("%d", temp);
        ok = L1.NextItem(temp);
    }
}

void BigNumber::AddBigNumbers(BigNumber B1,BigNumber B2) {
  B1.Reverse();
  B2.Reverse();

  int carry = 0, temp, temp2, res;
  bool digit1 = B1.L1.FirstItem(temp);
  bool digit2 = B2.L1.FirstItem(temp2);

  while (digit1 == true || digit2 == true) {
    if (digit1 == false) temp = 0;
    if (digit2 == false) temp2 = 0;
    res = temp + temp2 + carry;
    
    L1.AddtoFront(res % 10);
    carry = res / 10;
    digit1 = B1.L1.NextItem(temp);
    digit2 = B2.L1.NextItem(temp2);
  }

  if(carry != 0) {L1.AddtoFront(carry);}
  L1.Reverse();
}

void BigNumber::Reverse()
{
    this->L1.Reverse();
}

BigNumber B1,B2,RES;

int main (int argc, char ** argv) {
  string numberstring;
  int stringseq=0;
  ifstream input_file;
  if(argc==2) input_file.open(argv[1]);
  else { cout<< "cannot read the file " << argv[1] << endl; exit(0);}
  while(!input_file.eof()) {
    getline(input_file,numberstring);
    if(!input_file.eof()) {
      if(stringseq==0) {
        B1.ReadFromString(numberstring);
        stringseq=1;
      }
      else B2.ReadFromString(numberstring);
    }
  }

  //print
  B1.PrintBigNumber();
  cout << "+" << endl;
  B2.PrintBigNumber();
  cout << "=" << endl;
  //compute the addition
  RES.AddBigNumbers(B1,B2);
  //print the result
  RES.PrintBigNumber();
}
