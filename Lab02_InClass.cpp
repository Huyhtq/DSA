#include <iostream>
#include <string>

using namespace std;

//Part 1:

//struct node for linklist
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
        cout<< temp->data<<" ";
        temp = temp->next;
    }
}

Stack::~Stack() {
	while (!isEmpty()) {
		pop();
	}
    count = 0;
}

void Part1() {
	Stack stack;
	int choice, value;
    system("cls");
    cout << "\n--- Stack Menu ---\n";
    cout << "1. Input list\n";
    cout << "2. Check if stack is empty\n";
    cout << "3. Check if stack is full\n";
    cout << "4. Push an element\n";
    cout << "5. Pop an element\n";
    cout << "6. Print the top element\n";
    cout << "7. Display Stack\n";
    cout << "8. Clear screen\n";
    cout << "0. Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Input value (0 to stop): ";
            cin >> value;
            while (value != 0) {
                stack.push(value);
                cin >> value;
            }
            stack.display();
            break;
        case 2:
            if (stack.isEmpty())
                cout << "Stack is empty.\n";
            else
                cout << "Stack is not empty.\n";
            break;
        case 3:
            if (stack.isFull())
                cout << "Stack is full.\n";
            else
                cout << "Stack is not full.\n";
            break;
        case 4:
            cout << "Enter the value to push: ";
            cin >> value;
            stack.push(value);
            break;
        case 5:
            stack.pop();
            break;
        case 6:
            stack.printTop();
            break;
        case 7:
            stack.display();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        case 8:
            system("cls");
            cout << "\n--- Stack Menu ---\n";
            cout << "1. Input list\n";
            cout << "2. Check if stack is empty\n";
            cout << "3. Check if stack is full\n";
            cout << "4. Push an element\n";
            cout << "5. Pop an element\n";
            cout << "6. Print the top element\n";
            cout << "7. Display Stack\n";
            cout << "8. Clear screen\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
            break;
        }
    } while (choice != 0);

}

//Part 2:
class Queue {
private:
    Node* front;
    Node* rear;
    int count;
public:
    Queue();
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    void dequeue();
    void printFront();
    void printRear();
    void display();
    ~Queue();
};

Queue::Queue(){
    front = nullptr;
    rear = nullptr;
    count = 0;
}

bool Queue::isEmpty(){
    return front == nullptr;
}

bool Queue::isFull() {
    int limit;
    cout << "Input limit of Queue to check: ";
    cin >> limit;
    if (count >= limit) {
        return true;
    }
    else return false;
}

void Queue::enqueue(int value) {
    Node* newNode =new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << value << " enqueued\n";
}
void Queue::dequeue() {
    if (isEmpty()) {
        cout << "Empty queue!\n";
        return;
    }

    Node* temp = front;
    cout << front->data << " dequeued\n";
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
}
void Queue::printFront() {
    if (isEmpty()) {
        cout << "Empty queue!\n";
    }
    else {
        cout << "Front element: " << front->data << endl;
    }
}
void Queue::printRear() {
    if (isEmpty()) {
        cout << "Empty queue!\n";
    }
    else {
        cout << "Rear element: " << rear->data << endl;
    }
}
void Queue::display() {
    Node* temp;
    temp = front;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Part2() {
    Queue queue;
    int choice, value;
    system("cls");
    cout << "\n--- Queue Menu ---\n";
    cout << "1. Input list\n";
    cout << "2. Check if queue is empty\n";
    cout << "3. Check if queue is full\n";
    cout << "4. Enqueue an element\n";
    cout << "5. Dequeue an element\n";
    cout << "6. Print the front element\n";
    cout << "7. Print the rear element\n";
    cout << "8. Display Stack\n";
    cout << "9. Clear screen\n";
    cout << "0. Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Input value (0 to stop): ";
            cin >> value;
            while (value != 0) {
                queue.enqueue(value);
                cin >> value;
            }
            queue.display();
            break;
        case 2:
            if (queue.isEmpty())
                cout << "Queue is empty.\n";
            else
                cout << "Queue is not empty.\n";
            break;
        case 3:
            if (queue.isFull())
                cout << "Queue is full.\n";
            else
                cout << "Queue is not full.\n";
            break;
        case 4:
            cout << "Enter the value to enqueue: ";
            cin >> value;
            queue.enqueue(value);
            break;
        case 5:
            queue.dequeue();
            break;
        case 6:
            queue.printFront();
            break;
        case 7:
            queue.printRear();
            break;
        case 8:
            queue.display();
            break;
        case 9:
            system("cls");
            cout << "\n--- Queue Menu ---\n";
            cout << "1. Input list\n";
            cout << "2. Check if queue is empty\n";
            cout << "3. Check if queue is full\n";
            cout << "4. Enqueue an element\n";
            cout << "5. Dequeue an element\n";
            cout << "6. Print the front element\n";
            cout << "7. Print the rear element\n";
            cout << "8. Display Stack\n";
            cout << "9. Clear screen\n";
            cout << "0. Exit\n";
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
            break;
        }
    } while (choice != 0);
}
int main() {
    Part2();
}