//STT:22520544
//Full Name: Huynh Tran Quoc Huy
//Session 01 - Exercise 01

#include <iostream>
#include <cstdlib>

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

public:     //Basic function
    LinkList();
    void Insert(int data);
    void InsertNode(Node* newNode);
    void InsertHead(Node* newNode);
    void Display();
    void Clear();
    ~LinkList();

public:     //Part 1 Function
    void FindMiddleNode();
    void DetectCircle();
    void Combine2SortLinkList(LinkList List1, LinkList List2);
    void GetIntersection(LinkList L1);
    void Reverse();
    void DeleteDuplicate();
    void CheckPalindrome();
    void FindNodeLocation();

public:     //Part 2 Function
    void addTwoNumbers();
    LinkList* copyList();
    void swapNodes();
    void removeNthFromEnd();
    void separateOddEven();
    void divideIntoPart();
    void removeZeroSum();
    void insertRandomValues();
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

void LinkList::Display()
{
    cout << "list: ";
    if (pHead != NULL) {
        Node* curr = pHead;
        while (curr->pNext != NULL)
        {
            cout << curr->Data << " ";
            curr = curr->pNext;
        }
        cout << curr->Data << endl;
    }
    else cout << "Empty list!";
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
    Display();
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
    Display();
    
}



void LinkList::addTwoNumbers()
{
    cout << "Input two number: ";
    int x;
    cin >> x;
    Insert(x);
    cin >> x;
    Insert(x);
    Display();
}

LinkList* LinkList::copyList()
{
    if (pHead == NULL)
    {
        cout << "Empty list!";
        return NULL;
    }
    LinkList* temp = new LinkList;
    Node* curr = pHead;
    while (curr != NULL)
    {
        temp->Insert(curr->Data);
        curr = curr->pNext;
    }

    cout << "Your list has been copied!" << "\nFirst node of copy list at: " << temp->pHead << endl;
    return temp;
}

void LinkList::swapNodes()
{
    cout << "Choose the index of node to swap (first node is 0): ";
    int k;
    cin >> k;

    if (k < 0 || k >= count)
    {
        cout << "Please insert valid index!";
        return;
    }
    if (pHead == NULL)
    {
        cout << "Empty list!";
        return;
    }
    if (pHead->pNext == NULL)
    {
        cout << "List only have one node!";
        return;
    }
    if (count - k == 1)
    {
        cout << "Your index is the last node!";
        return;
    }
    Node* prev = NULL;
    Node* curr = pHead;

    // Traverse to the (k-1)-th node
    for (int i = 0; i < k && curr->pNext != NULL; ++i) {
        prev = curr;
        curr = curr->pNext;
    }

    // curr now points to the k-th node, and curr->pNext is the (k+1)-th node
    Node* next = curr->pNext;

    if (next == NULL) return;  // No (k+1)-th node to swap with

    // Perform the swap
    curr->pNext = next->pNext;
    next->pNext = curr;

    if (prev != NULL) {
        prev->pNext = next;
    }
    else {
        pHead = next;  // Update head if swapping the first node
    }

    cout << "After swap "; Display();
}

void LinkList::removeNthFromEnd()
{
    cout << "Choose the Nth number form end to remove: ";
    int n;
    cin >> n;

    if (n >= count || n < 0)
    {
        cout << "Invalid number!";
        return;
    }

    Node* temp = new Node();
    temp->pNext = pHead;
    Node* fast = temp;
    Node* slow = temp;

    for (int i = 0; i <= n; i++) {
        fast = fast->pNext;
    }

    while (fast != NULL) {
        fast = fast->pNext;
        slow = slow->pNext;
    }

    Node* toDelete = slow->pNext;
    slow->pNext = slow->pNext->pNext;
    delete toDelete;

    pHead = temp->pNext;
    delete temp;

    cout << "Delete complete!" << endl;
    Display();
}

void LinkList::separateOddEven()
{
    if (pHead == NULL)
    {
        cout << "Empty list!";
        return;
    }

    Node* odd = pHead;
    Node* even = pHead->pNext;
    LinkList oddL, evenL;

    oddL.Insert(odd->Data);
    evenL.Insert(even->Data);
    while (even != NULL && even->pNext != NULL) {
        odd = even->pNext;
        even = odd->pNext;
        oddL.Insert(odd->Data);
        evenL.Insert(even->Data);
    }

    cout << "Odd node list: "; oddL.Display();
    cout << "Even node list: "; evenL.Display();
    cout << endl;
}

void LinkList::divideIntoPart()
{
    cout << "How many part you want to divide: ";
    int part;
    cin >> part;
    if (pHead == NULL)
    {
        cout << "Empty list!";
        return;
    }
    if (part <= 0 || part > count)
    {
        cout << "Invalid number!";
        return;
    }

    // Step 1: Calculate size of each part and remainder
    int baseSize = count / part;
    int remainder = count % part;

    // Step 2: Split the list
    Node* curr = pHead;
    curr = pHead;
    for (int i = 0; i < part; i++) {
        int currentPartSize = baseSize + (remainder > 0 ? 1 : 0);
        remainder--;

        // Print the current part
        cout << "Part " << i + 1 << ": ";

        // Traverse and display current part
        for (int j = 0; j < currentPartSize && curr != NULL; j++) {
            cout << curr->Data << " ";
            if (j == currentPartSize - 1) {
                // Break the link to form separate parts
                Node* temp = curr;
                curr = curr->pNext;
                temp->pNext = NULL;  // End the current part
            }
            else {
                curr = curr->pNext;
            }
        }
        cout << endl;
    }
}

void LinkList::removeZeroSum() {
    Node* curr = pHead;
    int sum;

    while (curr != NULL) {
        sum = 0;
        Node* runner = curr;

        //Calculate sum from curr to end of list
        while (runner != NULL) {
            sum += runner->Data;

            //If sum ==0 remove all node from curr to runner
            if (sum == 0) {
                Node* temp = curr;
                while (temp != runner->pNext) {
                    Node* toDelete = temp;
                    temp = temp->pNext;
                    delete toDelete;
                }

                if (curr == pHead) {
                    pHead = runner->pNext;
                }


                curr = runner->pNext;
                break;
            }
            runner = runner->pNext;
        }

        //If sum not equal to 0 move to next node
        if (sum != 0) {
            curr = curr->pNext;
        }
    }
    Display();
}

void LinkList::insertRandomValues()
{
    // Randomly choose the number of entries in the range [39, 59]
    int numEntries = (rand() % 21) + 39;

    for (int i = 0; i < numEntries; ++i) {
        // Generate random value in the range [-99, 99]
        int randomValue = (rand() % 199) - 99; // or rand() % 199 - 99
        Insert(randomValue);
    }

    cout << numEntries << " random values inserted into the list." << endl;
    Display();
}

class Menu
{
private:
    LinkList List,l1,l2;
    LinkList* ListPointer;
public:
    void showMenu();
    void ShowPage1();
    void ShowPage2();
    void RunMethod(int x);
};

void Menu::showMenu()
{
    char input;
    do
    {
        system("cls");
        cout << "Main Menu\n";
        cout << "1. Page 1: 8 functions Part 1 \n";
        cout << "2. Page 2: 8 functions Part 2 \n";
        cout << "Q. Quit";
        cout << "Select a page or press 'Q' to quit: ";
        cin >> input;
        switch (input)
        {
        case '1':
            ShowPage1();
            break;
        case '2':
            ShowPage2();
            break;
        case 'Q':
            cout << "Exiting...";
            break;
        default:
            cout <<"Invalid option. Press any key to continue.";
            cin >> input;
            break;
        }
    }
    while (input != 'Q');

}

void Menu::ShowPage1()
{
    char input;
    system("cls");
    cout << "Current "; List.Display();
    cout << "\n\nPage 1: Functions of Part 1\n";
    cout << "0. (Re)input the list\n";
    cout << "1. Q1: Find the Middle Node of a Linked List\n";
    cout << "2. Q2: Detect a Cycle in a Linked List\n";
    cout << "3. Q3: Combine Two Sorted Linked Lists\n";
    cout << "4. Q4: Find the Intersection of Two Linked Lists\n";
    cout << "5. Q5: Reverse a Linked List\n";
    cout << "6. Q6: Eliminate Duplicates from a Sorted Linked List\n";
    cout << "7. Q7: Check if a Linked List is a Palindrome\n";
    cout << "8. Q8: Find the adress of Node have value X\n";
    cout << "B. Back to Main Menu\n";
    cout << "C. Clear screen\n";
    do
    {
        cout << "\nChoose a funtion or press 'B' to go back: ";
        cin >> input;

        if (input >= '0' && input <= '8')
        {
            int methodNum = input - '0';    //Use ascii value of 0 to calculate input
            RunMethod(methodNum);
        }
        else if (input == 'B' || input =='b')
        {
            // Go back to the main menu
            break;
        }
        else if (input == 'C'|| input == 'c')
        {
            system("cls");
            cout << "Current "; List.Display();
            cout << "\n\nPage 1: Functions of Part 1\n";
            cout << "0. (Re)input the list\n";
            cout << "1. Q1: Find the Middle Node of a Linked List\n";
            cout << "2. Q2: Detect a Cycle in a Linked List\n";
            cout << "3. Q3: Combine Two Sorted Linked Lists\n";
            cout << "4. Q4: Find the Intersection of Two Linked Lists\n";
            cout << "5. Q5: Reverse a Linked List\n";
            cout << "6. Q6: Eliminate Duplicates from a Sorted Linked List\n";
            cout << "7. Q7: Check if a Linked List is a Palindrome\n";
            cout << "8. Q8: Find the adress of Node have value X\n";
            cout << "B. Back to Main Menu\n";
            cout << "C. Clear screen\n";
        }
        else
        {
            cout << "Invalid option. Press any key to continue.";
            cin >> input;
        }
    } while (input != 'B');
}

void Menu::ShowPage2()
{
    char input;
    system("cls");
    cout << "Current "; List.Display();
    cout << "\n\nPage 2: Functions of Part 2\n";
    cout << "0. (Re)input the list\n";
    cout << "1. Q1: Add two numbers\n";
    cout << "2. Q2: Copy List with Random Pointers \n";
    cout << "3. Q3: Swap Nodes in a Linked List\n";
    cout << "4. Q4: Remove the N-th Node from the End of a List \n";
    cout << "5. Q5: Separate Odd and Even Nodes in a Linked List \n";
    cout << "6. Q6: Divide a Linked List into Parts\n";
    cout << "7. Q7: Remove Zero-Sum Consecutive Nodes from a Linked List\n";
    cout << "8. Q8: Input random value\n";
    cout << "B. Back to Main Menu\n";
    cout << "C. Clear screen\n";

    do
    {
        cout << "\nChoose a funtion or press 'B' to go back: ";
        cin >> input;

        if (input == '0') RunMethod(0);
        else if (input >= '1' && input <= '8')
        {
            int methodNum = input - '0'+8;    //Use ascii value of 0 to calculate input
            RunMethod(methodNum);
        }
        else if (input == 'B' || input == 'b')
        {
            // Go back to the main menu
            break;
        }
        else if (input == 'C' || input == 'c')
        {
            system("cls");
            cout << "Current "; List.Display();
            cout << "\n\nPage 2: Functions of Part 2\n";
            cout << "0. (Re)input the list\n";
            cout << "1. Q1: Add two numbers\n";
            cout << "2. Q2: Copy List with Random Pointers \n";
            cout << "3. Q3: Swap Nodes in a Linked List\n";
            cout << "4. Q4: Remove the N-th Node from the End of a List \n";
            cout << "5. Q5: Separate Odd and Even Nodes in a Linked List \n";
            cout << "6. Q6: Divide a Linked List into Parts\n";
            cout << "7. Q7: Remove Zero-Sum Consecutive Nodes from a Linked List\n";
            cout << "8. Q8: Input random value\n";
            cout << "B. Back to Main Menu\n";
            cout << "C. Clear screen\n";
        }
        else
        {
            cout << "Invalid option. Press any key to continue.";
            cin >> input;
        }
    } while (input != 'B');
}

void Menu::RunMethod(int x)
{
    if (x == 0)
    {
        List.Clear();
        cout << "Input the List (0 to stop): ";
        int x;
        cin >> x;
        while (x != 0)
        {
            List.Insert(x);
            cin >> x;
        }
        List.Display();
    }
    else if (x == 1)    List.FindMiddleNode();
    else if (x == 2)    List.DetectCircle();
    else if (x == 3)
    {
        l2.Clear();
        cout << "Input the second List (0 to stop): ";
        cin >> x;
        while (x != 0)
        {
            l2.Insert(x);
            cin >> x;
        }
        l1.Combine2SortLinkList(List, l2);
        cout << "After combine "; l1.Display();
        cout << endl;
        l2.Clear();
    }
    else if (x == 4)
    {
        l1.Clear();
        cout << "Input the second List (0 to stop): ";
        cin >> x;
        while (x != 0)
        {
            l1.Insert(x);
            cin >> x;
        }
        List.GetIntersection(l1);
        l1.Clear();
    }
    else if (x == 5)    List.Reverse();
    else if (x == 6)    List.DeleteDuplicate();
    else if (x == 7)    List.CheckPalindrome();
    else if (x == 8)    List.FindNodeLocation();
    else if (x == 9)    List.addTwoNumbers();
    else if (x == 10)
    {
        ListPointer = List.copyList();
    }
    else if (x == 11)   List.swapNodes();
    else if (x == 12)   List.removeNthFromEnd();
    else if (x == 13)   List.separateOddEven();
    else if (x == 14)   List.divideIntoPart();
    else if (x == 15)   List.removeZeroSum();
    else if (x == 16)   List.insertRandomValues();
}

int main()
{
    Menu menu;
    menu.showMenu();
}