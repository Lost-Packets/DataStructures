// Nathan Ploos Van Amstel

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>
using namespace std;

struct Node{ 
	int row;
	int column;
	int value;
	Node *next;
};
Node *A, *B;

struct Matrix{
	int value;
	int row;
	Matrix *next;
};
Matrix *matrix_one, *matrix_two , *matrix_result, *matrix_out;

void add_node_end(Node *&first, int value, int row){
	Node *temp = new Node;
	temp->value = value;
	temp->row = row;
	temp->next = NULL;

	if(!first){
		first = temp;
		return;
	}else{
		Node *last = first;
		while(last->next) last = last->next;
		last->next=temp;
	}
}

bool isEmpty(Node *head){
    if(head == NULL){
        return true;
    }else{
        return false;
    }
}

bool isEmptyMatrix(Matrix *head){
    if(head == NULL){
        return true;
    }else{
        return false;
    }
}

void get_matrix(Matrix *&matrix_pointer, int value, int row){
	Matrix *temp;
	temp = new Matrix;
	temp->value = value;
	temp->row = row;
	temp->next = NULL;

	if(!matrix_pointer){
		matrix_pointer = temp;
		return;
	}else{
		Matrix *last = matrix_pointer;
		while(last->next) last = last->next;
		last->next=temp;
	}
}

void print_matrix(Matrix *current, Node *row){
    int counter = 0;
    if(isEmptyMatrix(current)){
        cout << "list is empty" << endl;
    }else{
        while(counter != row->row && current != NULL){
            counter++;
            cout << current->value << " ";
            current = current->next;
            if(counter == row->row){
                cout << endl;
                counter = 0;
            }
        } 
    }
}

void printLL(Node *current){
	if(isEmpty(current)){
        cout<< "List is Empty" << endl;
    }else{
        while(current != NULL){
            cout << current->value << " ";
            current = current->next;
        }
    }
}

void matrix_printLL(Matrix *current){
	if(isEmptyMatrix(current)){
        cout << "List is Empty" << endl;
    }else{
        while(current != NULL){
            cout << current->value << " ";
            current = current->next;
        }
    }
}

void add_matrix(Matrix *&matrix_one, Matrix *&matrix_two, Matrix *&matrix_result){
    matrix_result = new Matrix();
    Matrix *temp = matrix_result;
    while(matrix_one != NULL && matrix_two != NULL){
        matrix_result->value = matrix_one->value + matrix_two->value;
        matrix_one = matrix_one->next;
        matrix_two = matrix_two->next;
        matrix_result->next = new Matrix();
        matrix_result = matrix_result->next;
    }
    matrix_result = temp; // restore head of matrix
    while (temp->next->next != NULL){
        temp = temp->next;
    }
    delete temp->next;
    temp->next = NULL;
}

int remove_counter(Matrix *&matrix_pointer,int x){
    Matrix *current = matrix_pointer;
    int count = 0;
    while(current != NULL){
        if(current->value == x)count++;
        current = current->next;
    }
    return count;
}

void remove_zero(Matrix *&matrix_pointer, int x){
    Matrix *temp = matrix_pointer, *temp2, *prev = NULL;
    while (temp != NULL){
        if (temp->value == x){
            if (prev == NULL){
                matrix_pointer = temp->next;
            }else{
                prev->next = temp->next;
            }
            temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
        else{
            prev = temp;
            temp = temp->next;
        }
    }
}

void read_matrix(Node* &a, Matrix *&b ,char *file_name){ 
    //reads a matrix from a file
    int col = 0, row = 0, value = 0; 
	string line;
    ifstream input;
    input.open(file_name);
    if(!input.good()){
        cout << "Cannot open file " << file_name << endl;
        exit(0);
    }
    //reads the first line to get dimensions
    if(input.good()){
	    getline(input,line);
	    stringstream sline(line);
	    sline >> row >> col;
	    //cout << "Matrix dimensions " << row << " " << col << endl;
    }
    //read matrix 
    for(int i = 0; i < row; ++i){
        if(input.good()){
			getline(input,line);
			stringstream sline(line);
        	for(int j = 0; j < col; ++j){
		    	sline >> value;
				get_matrix(b, value, row);
				//cout<<value<<" ";	
	        	if(value == 0) continue;
				//add_node(a, i, j, value);
				add_node_end(a, value, row);
          	}
	    }
    }
    //cout << endl;
    input.close();
}

void copy_matrix(Matrix *&matrix_result, Matrix *&matrix_copy){
    if(isEmptyMatrix(matrix_result)){
        cout << "Matrix is empty" << endl;
        matrix_copy = NULL;
    }else{
        Matrix *temp = matrix_result;
        Matrix *temp2 = NULL;
        
        while(temp != NULL){
            Matrix *newMatrix = new Matrix; 
            newMatrix->value = temp->value;
            newMatrix->next = NULL;
            if(temp2 == NULL){
                temp2 = newMatrix;
                matrix_copy = temp2;
            }else{
                temp2->next = newMatrix;
                temp2 = temp2->next;
            }
            temp = temp->next; 
        }
    }
}

int main(int argc, char** argv){
   if(argc!=3) {printf("needs two matrices \n"); exit(0);}
   Node *A=NULL;
   Node *B=NULL;
   Matrix *matrix_one=NULL;
   Matrix *matrix_two=NULL;
   Matrix *matrix_result=NULL;
   Matrix *matrix_out=NULL;

    read_matrix(A, matrix_one, argv[1]);
    cout<<"Matrix 1: ";
    printLL(A);
    cout<<endl;
    print_matrix(matrix_one, A);

    read_matrix(B, matrix_two, argv[2]);
    cout<<"Matrix 2: ";
    printLL(B);
    cout<<endl;
    print_matrix(matrix_two, B);

    add_matrix(matrix_one,matrix_two,matrix_result);
    copy_matrix(matrix_result, matrix_out); // Need to copy matrix result into new list as Matrix result gets altered.

    int counter = 0;
    while(counter <= remove_counter(matrix_result, 0)){
        remove_zero(matrix_result, 0);
        counter++;
    }
    
    cout<<"Matrix Result: ";
    matrix_printLL(matrix_result);
    cout<<endl;
    print_matrix(matrix_out,A);
 
}
