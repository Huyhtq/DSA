#include <iostream>

using namespace std;
struct Node {
	int data;
	Node* next;
};

//class stack
class Stack {
private:
	Node* top;
	int count;
public:
	Stack();
	bool isEmpty();
	bool isFull();
	void push(int value);
	void pop();
	void printTop();
	void display();
	~Stack();
};

Stack::Stack() {
	top = nullptr;
	count = 0;
}

bool Stack::isEmpty() {
	return top == nullptr;
}

bool Stack::isFull() {
	int limit;
	cout << "Input limit of Stack to check: ";
	cin >> limit;
	if (count >= limit) {
		return true;
	}
	else return false;
}

void Stack::push(int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = top;
	top = newNode;
	count++;
	cout << value << "Push onto the Stack\n";
}

void Stack::pop() {
	if (isEmpty()) {
		cout << "Empty list!";
		return;
	}
	Node* temp = top;
	cout << top->data << "Popped";
	top = top->next;
	count--;
	delete temp;
}

void Stack::printTop() {
	if (isEmpty()) {
		cout << "Stack empty!";
	}
	else {
		cout << "Top value: " << top->data << endl;
	}
}

void Stack::display() {
	Node* temp;
	temp = top;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
}

Stack::~Stack() {
	while (!isEmpty()) {
		pop();
	}
	count = 0;
}

void displayTowers(Stack& towerA, ) {

}

int main() {
	
}