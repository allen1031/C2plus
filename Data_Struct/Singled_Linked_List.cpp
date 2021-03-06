// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
#include<iostream>

class MyLinkedList {
private:
	struct Node {
		int val;
		Node* next;
	};
	Node* head;
	Node* cur;
	int length;

public:
	/** Initialize your data structure here. */
	MyLinkedList() {
		head = NULL;
		length = 0;
	}



	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	int get(int index) {
		cur = head;
		if (length == 0 or index >= length)return -1;
		for (int i = 0; i<index; i++) {
			cur = cur->next;
			if (cur == NULL) {
				return -1;
			}
		}
		std::cout <<index<<"th in the list is "<< cur->val <<std::endl;
		return cur->val;
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {
		Node* newNode = new Node();
		if (newNode == NULL)return;
		newNode->val = val;
		newNode->next = this->head;
		this->head = newNode;
		length++;

	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {
		Node* newNode = new Node();
		if (newNode == NULL)return;
		newNode->val = val;

		if (length == 0) {
			head = newNode;
		}
		else {
			cur = head;
			for (int i = 0; i<length - 1; i++) { // Get pre-index Node
				cur = cur->next;
				if (cur == NULL)return;
			}
			cur->next = newNode;
		}
		length++;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {
		Node* newNode = new Node();
		if (newNode == NULL)return;
		newNode->val = val;

		if (index > length) {
			delete newNode;
			return;
		}
		else if (index == 0) // Index at the beginning of the list
		{
			addAtHead(val);
		}
		else if (index == length) {
			addAtTail(val);
		}
		else {
			Node* pre = head;
			for (int i = 0; i<index - 1; ++i) { // Get pre-index Node
				pre = pre->next;
				if (pre == NULL)return;
			}
			cur = pre->next;
			newNode->next = cur;
			pre->next = newNode;
			length++;
		}

	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {   // Index at the beginning of the list


		if (index >= length || length == 0) {
			return;
		}
		else if (index == 0) {
			if (length > 1)head = head->next;
			else head = NULL;
		}
		else if (index == length - 1) {

			Node *pre = head;
			for (int i = 0; i<index - 1; ++i) { // Get pre-index Node
				pre = pre->next;
				if (pre == NULL)return;
			}
			pre->next = NULL;

		}
		else {

			Node* pre = head;
			for (int i = 0; i<index - 1; ++i) {
				pre = pre->next;
				if (pre == NULL)return;
			}
			cur = pre->next;
			if (cur->next == NULL)return;
			pre->next = cur->next;
			delete cur;
		}
		length--;

	}


	void print() {
		Node* head = this->head;
		int i = 1;
		while (head) {
			std::cout << head->val << " -> ";
			head = head->next;
			i++;
		}
		cout << endl;
	}
};

int main() {

	MyLinkedList* linkedList = new MyLinkedList();
	linkedList->addAtHead(1);
	linkedList->print();
	linkedList->addAtTail(3);
	linkedList->print();
	linkedList->addAtIndex(1, 2);  // linked list becomes 1->2->3
	linkedList->print();
	linkedList->get(1);            // returns 2
	linkedList->deleteAtIndex(1);  // now the linked list is 1->3
	linkedList->print();
	linkedList->get(1);            // returns 3
	while (1);
}

