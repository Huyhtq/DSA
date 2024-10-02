#include <iostream>
#include <string>

using namespace std;


//Homework 6.1 Music player
struct songNode
{
	string songName;
	songNode* prevSong;
	songNode* nextSong;
	songNode(const string& song);
	void displaySong();
};

songNode::songNode(const string& song)
{
	songName = song;
	prevSong = nullptr;
	nextSong = nullptr;
}

void songNode::displaySong()
{
	cout << "Now playing: " << songName << endl;
}

class songList
{
private:
	songNode* head;
	songNode* tail;
	songNode* curr;
public:
	songList(); //Constructor
	void addSong(const string& name);	//Add new song to end of list
	void playNext();
	void playPrev();
	void removeSong(const string& name);	//remove song from list 
	void display();
};

songList::songList()
{
	head = tail = curr = nullptr;
}

void songList::addSong(const string& name)
{
	songNode* newSong = new songNode(name);
	if (head == nullptr)	//empty list
	{
		head = tail = curr = newSong;
	}
	else
	{
		tail->nextSong = newSong;
		newSong->prevSong = tail;
		tail = newSong;
	}
}

//play nexxt song
void songList::playNext()
{
	if (curr == nullptr)
	{
		cout << "The list is empty!"; 
		return;
	}
	else
	{
		if (curr->nextSong != nullptr)
		{
			curr = curr->nextSong;
		}
		else
		{
			curr = head;
		}
	}
}

//play the previous song
void songList::playPrev()
{
	if (curr == nullptr)
	{
		cout << "The list is empty!";
		return;
	}
	else
	{
		if (curr->prevSong != nullptr)
		{
			curr = curr->prevSong;
		}
		else
		{
			curr = tail;
		}
	}
}

//Remove Song by name
void songList::removeSong(const string& name)
{
	//Empty list
	if (head == nullptr) {
		cout << "List is empty!";
	}
	
	//find the node contain that song
	songNode* temp = head;
	while (temp != nullptr && temp->songName != name)
	{
		temp = temp->nextSong;
	}
	
	//Song not found
	if (temp == nullptr)
	{
		cout << "There is no song name " << name << " in list1";
		return;
	}

	//remove song is the first node
	if (temp == head){
		head = temp->nextSong;
	}

	//remove song is the last node
	if (temp == tail) {
		tail = temp->prevSong;
	}

	//remove node in the list
	if (temp->nextSong != nullptr)
	{
		temp->nextSong->prevSong = temp->prevSong;
	}

	if (temp->prevSong != nullptr)
	{
		temp->prevSong->nextSong = temp->nextSong;
	}

	if (curr == temp)
	{
		if (temp->nextSong == nullptr)
		{
			curr = temp->nextSong;
		}
		else curr = head;
	}
}

//Display current list
void songList::display() {
	if (head == nullptr)
	{
		cout << "List is empty!" << endl;
		return;
	}

	songNode* temp = tail;
	while (temp!=nullptr) {
		cout << temp->songName << " ";
		temp = temp->prevSong;
	}
	cout << endl;
}

void musicPlayer() {
	int n;
	cin >> n;
	songList player;

	while (n--) {
		string command;
		cin >> command;
		if (command == "ADD") {
			string songName;
			cin >> songName;
			player.addSong(songName);
		}
		else if (command == "NEXT") {
			player.playNext();
		}
		else if (command == "PREV") {
			player.playPrev();
		}
		else if (command == "REMOVE") {
			string songName;
			cin >> songName;
			player.removeSong(songName);
		}
		else if (command == "DISPLAY") {
			player.display();
		}
	}
}

//Homework 6.2: Browser back and next
class Node {
public:
	string url;
	Node* prevPage;
	Node* nextPage;
	Node(const string& Url);
};

Node::Node(const string& Url) {
	url = Url;
	prevPage = nullptr;
	nextPage = nullptr;
}

class browserHistory {
public:
	Node* head;
	Node* current;
public:
	browserHistory(string homePage);
	~browserHistory();
	void deleteHistory();
	void visit(string url);
	string forward(int steps);
	string back(int steps);
	void display();
};

browserHistory::browserHistory(string homePage) {
	head = new Node(homePage);
	current = head;
}

void browserHistory::deleteHistory() {
	Node* temp;
	temp = head;
	head = head->nextPage;
	delete temp;
}

browserHistory::~browserHistory() {
	while (head != nullptr) {
		deleteHistory();
	}
}

//visit a new page = add a new node to list
void browserHistory::visit(string url) {

	Node* temp = current->nextPage;
	while (temp != nullptr) {
		Node* next = temp->nextPage;
		delete temp;
		temp = next;
	}

	current->nextPage = nullptr;

	Node* newNode = new Node(url);
	current->nextPage = newNode;
	newNode->prevPage = current;
	current = newNode;
}

//go to n node
string browserHistory::forward(int steps) {
	while (steps > 0 && current->nextPage != nullptr) {
		current = current->nextPage;
		steps--;
	}
	return current->url;
}

//go back n node
string browserHistory::back(int steps) {
	while (steps > 0 && current->prevPage != nullptr) {
		//if no more node before it
		if (current->prevPage == head) {
			current = head;
			break;
		}
		current = current->prevPage;
		steps--;
	}
	//return url off the page
	return current->url;
}

//Display list of page
void browserHistory::display() {
	if (head == NULL) {
		cout << "Empty!";
		return;
	}
	Node* temp = head;
	while (head) {
		cout << temp->url << endl;
		temp = temp->nextPage;
	}
}

void displayMenu() {
	cout << "\n--- Command Menu ---\n";
	cout << "1. Visit a new page (visit)\n";
	cout << "2. Go back n pages (back)\n";
	cout << "3. Go forward n pages (forward)\n";
	cout << "4. Show browsing history (history)\n";
	cout << "5. Exit (exit)\n";
	cout << "Enter your choice: \n";
}

void Browser() {
	string homePage;
	cout << "Enter your  homepage URL: ";
	cin >> homePage;

	browserHistory* browser = new browserHistory(homePage);
	string command;

	displayMenu();

	while (true) {
		cin >> command;
		if (command == "visit") {
			string url;
			cin >> url;
			browser->visit(url);
			cout << "You are at " << browser->current->url << endl;
		}
		else if (command == "back") {
			int steps;
			cin >> steps;
			cout << "You are at " << browser->back(steps) << endl;			
		}
		else if (command == "forward") {
			int steps;
			cin >> steps;
			cout << "You are at " << browser->forward(steps) << endl;
		}
		else if (command == "history") {
			cout << "\n--- Browsing History ---\n";
			browser->display();
		}
		else if (command == "exit") {
			cout << "Exiting browser history...\n";
			break;
		}
		else {
			cout << "Invalid command! Please try again.\n";
		}

	}
	delete browser;

}

//Part 3: 
class Token {
public:
	string tokenId;
	int expiryTime;
	Token* next;

	Token(string id, int time) : tokenId(id), expiryTime(time), next(nullptr) {}
};

class AuthenticationManager {
private:
	int timeToLive;
	Token* head; 

public:
	// Constructor 
	AuthenticationManager(int timeToLive) {
		this->timeToLive = timeToLive;
		head = nullptr;
	}

	// add token to list
	void generate(string tokenId, int currentTime) {
		Token* newToken = new Token(tokenId, currentTime + timeToLive);
		newToken->next = head;
		head = newToken;
		cout << "Token " << tokenId << " generated at time " << currentTime << endl;
	}

	// add more time if not expired
	void renew(string tokenId, int currentTime) {
		Token* current = head;
		while (current != nullptr) {
			if (current->tokenId == tokenId && current->expiryTime > currentTime) {
				current->expiryTime = currentTime + timeToLive; // extend time
				cout << "Token " << tokenId << " renewed at time " << currentTime << endl;
				return;
			}
			current = current->next;
		}
		cout << "Token " << tokenId << " could not be renewed (expired or not found)" << endl;
	}

	// count and delete expired token
	int countUnexpiredTokens(int currentTime) {
		int count = 0;
		Token* current = head;
		Token* prev = nullptr;

		while (current != nullptr) {
			if (current->expiryTime > currentTime) {
				count++; 
				prev = current;
				current = current->next;
			}
			else {
				// token expire
				if (prev == nullptr) {
					// token at head
					Token* temp = head;
					head = head->next;
					delete temp;
					current = head;
				}
				else {
					// delete token at mid or end
					prev->next = current->next;
					delete current;
					current = prev->next;
				}
			}
		}
		cout << "Unexpired tokens at time " << currentTime << ": " << count << endl;
		return count;
	}

	// display all token
	void displayTokens() {
		if (head == nullptr) {
			cout << "No tokens available." << endl;
			return;
		}
		Token* current = head;
		cout << "Current Tokens:" << endl;
		while (current != nullptr) {
			cout << "Token ID: " << current->tokenId << ", Expiry Time: " << current->expiryTime << endl;
			current = current->next;
		}
	}

	// Destructor
	~AuthenticationManager() {
		while (head != nullptr) {
			Token* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

void tokensMenu() {
	int timeToLive;
	cout << "Enter the time to live for each token (in seconds): ";
	cin >> timeToLive;

	AuthenticationManager authManager(timeToLive);
	int currentTime = 0;
	int choice;
	cout << "\nMenu:\n";
	cout << "1. Generate token\n";
	cout << "2. Renew token\n";
	cout << "3. Count unexpired tokens\n";
	cout << "4. Display all tokens\n";
	cout << "5. Exit\n";

	while (true) {
		cout << "Enter command: ";
		cin >> choice;

		if (choice == 1) {
			string tokenId;
			cout << "Enter token ID: ";
			cin >> tokenId;
			cout << "Enter current time: ";
			cin >> currentTime;
			authManager.generate(tokenId, currentTime);
		}
		else if (choice == 2) {
			string tokenId;
			cout << "Enter token ID to renew: ";
			cin >> tokenId;
			cout << "Enter current time: ";
			cin >> currentTime;
			authManager.renew(tokenId, currentTime);
		}
		else if (choice == 3) {
			cout << "Enter current time: ";
			cin >> currentTime;
			authManager.countUnexpiredTokens(currentTime);
		}
		else if (choice == 4) {
			authManager.displayTokens();
		}
		else if (choice == 5) {
			break; // Exit
		}
		else {
			cout << "Invalid choice, please try again." << endl;
		}
	}
}



int main() {
	//musicPlayer();
	//Browser();
	tokensMenu();
}

