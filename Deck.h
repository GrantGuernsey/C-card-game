#ifndef DECK
#define DECK

#include <iostream>
using namespace std;

class Deck {
private:
	//Node Class
	class Node {
	public:
		int data;
		Node* next;

		Node(int data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
	};

	//Helper Attributes
	Node* head = nullptr;
	Node* tail = nullptr;
	class error {};
	int len = 0;

public:
	//Constructors
	Deck() {}
	Deck(int data) {
		head = new Node(data);
		tail = head;
		len += 1;
	}
	Deck(int* data, int size) {
		head = new Node(data[0]);
		tail = head;

		for (int n = 1; n < size; n++) {
			tail->next = new Node(data[n]);
			tail = tail->next;
		}

		len = size;
	}

	//Utility methods
	int length() {
		return len;
	}
	bool isEmpty() {
		return len <= 0;
	}
	void display() {
		Node* temp = head;
		cout << "List: ";
		while (temp != nullptr) {
			cout << temp->data << ' ';
			temp = temp->next;
		}
		cout << endl;
	}

	//Data handling methods
	void enqueue(int data) {
		if (head != nullptr) {
			tail->next = new Node(data);
			tail = tail->next;
			len += 1;
		}
		else {
			head = new Node(data);
			tail = head;
			len += 1;
		}
	}
	int dequeue() {
		if (isEmpty()) throw error();
		
		Node* temp = head;
		int rData = temp->data;
		head = head->next;
		delete temp;

		len -= 1;
		return rData;
	}
	int peek() {
		return head->data;
	}
	void clear() {
		Node* before = head;
		Node* remov = nullptr;

		while (before != nullptr) {
			remov = before;
			before = before->next;
			delete remov;
		}

		head = nullptr;
		tail = nullptr;
		len = 0;
	}
	
};

#endif
