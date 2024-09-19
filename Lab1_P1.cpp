//STT:22520544
//Full Name: Huynh Tran Quoc Huy
//Session 01 - Exercise 01

#include <iostream>

using namespace std;

struct Node
{
    int Data = 0;
    Node* pNext = NULL;
};

class LinkList
{
public:
    Node* pHead;
    Node* pTail;
    int count;
public:
    LinkList();
    void Insert(int data);
    void InsertNode(Node* newNode);
    void InsertHead(Node* newNode);
    void InsertMid();
    void Display();
    void FindMiddleNode();
    void DetectCircle();
    void Combine2SortLinkList(LinkList List1, LinkList List2);
    void GetIntersection(LinkList L1);
    void Reverse();
    void DeleteDuplicate();
    void CheckPalindrome();
    void FindNodeLocation();
    void Clear();
    ~LinkList();
};

LinkList::LinkList() 
{
    pHead = NULL;
    pTail = NULL;
    count = 0;
}
LinkList::~LinkList()
{
    Node* current = pHead;
    while (current != NULL) {
        Node* next = current->pNext;  
        delete current;               
        current = next;               
    }
    pHead = NULL;
    pTail = NULL;
    count = 0;
}

void LinkList::Clear()
{
    Node* current = pHead;
    while (current != NULL) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
    pHead = NULL;
    pTail = NULL;
    count = 0;
}
void LinkList::Insert(int data)
{
    Node* newNode = new Node{data, NULL};
    if (pHead == NULL)
    {
        pHead = newNode;
        pTail = newNode;
    }
    else
    {
        Node* current = pHead;
        while (current->pNext != NULL)
        {
            current = current->pNext;
        }
        current->pNext = newNode;
        pTail = newNode;
    }
    count++;
}   

void LinkList::InsertNode(Node* newNode)
{

    if (pHead == NULL)
    {
        pHead = newNode;
        pTail = newNode;
    }
    else
    {
        Node* current = pHead;
        while (current->pNext != NULL)
        {
            current = current->pNext;
        }
        current->pNext = newNode;
        pTail = newNode;
    }
    count++;
}

void LinkList::InsertHead(Node* newNode)
{
    if (pHead == NULL)
    {
        pHead = newNode;
        pTail = newNode;
    }
    else
    {
        Node* current = newNode;
        current->pNext = pHead;
        pHead = newNode;
    }
}

void LinkList::InsertMid()
{
    int data,x;
    cout << "Nhap so ban muon chen them: ";
    cin >> x;
    cout << "Nhap gia tri ban muon chen: ";
    cin >> data;

    Node* NewNode = new Node{ data, NULL };
    Node *Temp;
    Temp = pHead;
    if (pHead == NULL)
    {
        pHead = NewNode;
        pTail = NewNode;
    }
    for (int i = pHead->Data; i != x && Temp->pNext != NULL; )
    {
        Temp = Temp->pNext;
        i = Temp->Data;
    }
    NewNode->pNext = Temp->pNext;
    Temp->pNext = NewNode;
    count++;
}

void LinkList::Display()
{
    Node* curr = pHead;
    cout << "list: ";
    while (curr->pNext != NULL)
    {
        cout << curr->Data << " ";
        curr = curr->pNext;
    }
    cout << curr->Data << endl;
}

void LinkList::FindMiddleNode()
{
    Node* onejump = pHead;
    Node* doublejump = pHead;
    if (count % 2 == 0)
        doublejump = doublejump->pNext;

    while (doublejump != NULL && doublejump->pNext != NULL)
    {
        onejump = onejump->pNext;
        doublejump = doublejump->pNext->pNext;
    }
    if (count % 2 == 0) 
    {
        cout << "Middle node: " << onejump->Data << ", " << onejump->pNext->Data;
    }
    else
    {
        cout << "Middle node: " << onejump->Data;
    }
    cout << endl;
}

void LinkList::DetectCircle()
{
    if (pHead == NULL)
    {
        cout << "Empty list!";
    }
    else
    {
        if (pTail->pNext == pHead)
            cout << "This is Cycle LinkList!";
        else
            cout << "Not a Cycle LinkList!";
    }
    cout << endl;
}

void LinkList::Combine2SortLinkList(LinkList L1, LinkList L2) 
{
    Node* p1 = L1.pHead;
    Node* p2 = L2.pHead;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->Data < p2->Data)
        {
            Insert(p1->Data);
            p1 = p1->pNext;
        }
        else
        {
            Insert(p2->Data);
            p2 = p2->pNext;
        }
    }

    while (p1 != NULL)
    {
        Insert(p1->Data);
        p1 = p1->pNext;
    }

    while (p2 != NULL)
    {
        Insert(p2->Data);
        p2 = p2->pNext;
    }
}

void LinkList::GetIntersection(LinkList L1)
{
    Node* Cur = pHead;
    int c = 0;
    cout << "Intersection: ";
    while ( Cur != NULL)
    {
        Node* Cur1 = L1.pHead;
        while (Cur1 != NULL)
        {
            if (Cur->Data == Cur1->Data)
            {
                cout << Cur->Data<< " ";
                Cur = Cur->pNext;
                c++;
            }
            Cur1 = Cur1->pNext;
        }
        Cur = Cur->pNext;
    }
    if (c == 0) cout << "No intersection";
    cout << endl;
}

void LinkList::Reverse() 
{
    LinkList List;
    Node* Curr = pHead;
    cout << "Revese ";
    while (Curr != NULL)
    {
        Node* NewNode = new Node;
        NewNode->Data = Curr->Data;
        NewNode->pNext = NULL;
        List.InsertHead(NewNode);
        Curr = Curr->pNext;
    }
    List.Display();

}

void LinkList::DeleteDuplicate() {
    if (pHead == NULL) return;

    Node* current = pHead;

    while (current != NULL && current->pNext != NULL) {
        if (current->Data == current->pNext->Data) {
            Node* temp = current->pNext;
            current->pNext = temp->pNext;  
            delete temp;
        }
        else {
            current = current->pNext;
        }
    }
}

void LinkList::CheckPalindrome()
{
    Node* onejump = pHead;
    Node* doublejump = pHead;
    LinkList List;
    Node* Temp;
    while (doublejump != NULL && doublejump->pNext != NULL)
    {
        Temp = new Node;
        Temp->Data = onejump->Data;
        List.InsertHead(Temp);
        onejump = onejump->pNext;
        doublejump = doublejump->pNext->pNext;
    }
    Temp = List.pHead;
    if (count % 2 == 1)
        onejump = onejump->pNext;
    while (Temp != NULL && onejump != NULL)
    {
        if (Temp->Data == onejump->Data)
        {
            Temp = Temp->pNext;
            onejump = onejump->pNext;
        }
        else
            break;
    }
    if (Temp == NULL)
        cout << "List is Palindrome!";
    else cout << "Not a Palindrome list!";
}

void LinkList::FindNodeLocation()
{
    int data;
    cout << "Enter valuue you want to find: ";
    cin >> data;

    Node* Temp = pHead;
    if (pHead == NULL)
    {
        cout << "Empty List!";
    }
    else
    {
        for(int i = pHead->Data; Temp != NULL ; )
        {
            if (i == data)
            {
                cout << Temp << " ";
            }
            Temp = Temp->pNext;
            i = Temp->Data;
        }
    }

    
}

void Menu()
{   
    LinkList l1, l2 ,l3;
    int choice,x;
    cout << "Input the List (-1 to stop): ";
    cin >> x;
    while (x != -1)
    {
        l1.Insert(x);
        cin >> x;
    }
    cout << "\n--- Menu ---\n";
    cout << "0. (Re)input the list\n";
    cout << "1. Q1: Find the Middle Node of a Linked List\n";
    cout << "2. Q2: Detect a Cycle in a Linked List\n";
    cout << "3. Q3: Combine Two Sorted Linked Lists\n";
    cout << "4. Q4: Find the Intersection of Two Linked Lists\n";
    cout << "5. Q5: Reverse a Linked List\n";
    cout << "6. Q6: Eliminate Duplicates from a Sorted Linked List\n";
    cout << "7. Q7: Check if a Linked List is a Palindrome\n";
    cout << "8. Q8: Find the adress of Node have value X\n";
    cout << "9. Exit\n";
    cout << "10. Display menu\n";
    do
    {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            l1.Clear();
            cout << "Input the List (-1 to stop):  ";
            cin >> x;
            while (x != -1)
            {
                l1.Insert(x);
                cin >> x;
            }
            cout << "Your "; l1.Display();
            cout << endl;
            break;
        case 1:
            l1.FindMiddleNode();
            cout << endl;
            break;
        case 2:
            l1.DetectCircle();
            cout << endl;
            break;
        case 3:
            l2.Clear();
            cout << "Input the second List (-1 to stop): ";
            cin >> x;
            while (x != -1)
            {
                l2.Insert(x);
                cin >> x;
            }
            l3.Combine2SortLinkList(l1, l2);
            cout << "After combine "; l3.Display();
            cout << endl;
            break;
        case 4:
            l2.Clear();
            cout << "Input the second List (-1 to stop): ";
            cin >> x;
            while (x != -1)
            {
                l2.Insert(x);
                cin >> x;
            }
            cout << "First "; l1.Display();
            cout << "Second "; l2.Display();
            l1.GetIntersection(l2);
            break;
        case 5:
            l1.Reverse();
            cout << endl;
            break;
        case 6:
            l1.DeleteDuplicate();
            cout << "Removed "; l1.Display();
            cout << endl;
            break;
        case 7:
            l1.CheckPalindrome();
            cout << endl;
            break;
        case 8:
            l1.FindNodeLocation();
            break;
        case 10:
            cout << "\n--- Menu ---\n";
            cout << "0. (Re)input the list\n";
            cout << "1. Q1: Find the Middle Node of a Linked List\n";
            cout << "2. Q2: Detect a Cycle in a Linked List\n";
            cout << "3. Q3: Combine Two Sorted Linked Lists\n";
            cout << "4. Q4: Find the Intersection of Two Linked Lists\n";
            cout << "5. Q5: Reverse a Linked List\n";
            cout << "6. Q6: Eliminate Duplicates from a Sorted Linked List\n";
            cout << "7. Q7: Check if a Linked List is a Palindrome\n";
            cout << "8. Q8: Find the adress of Node have value X\n";
            cout << "9. Exit\n";
            cout << "10. Display menu\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 9);
}

int main()
{
    Menu();

}

