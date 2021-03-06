// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

	
class Solution {
public:

	bool hasCycle(ListNode *head) {

		ListNode* fast_ptr = head;
		ListNode* slow_ptr = head;

		int i = 0;
		while (fast_ptr && slow_ptr) {
			if (fast_ptr == NULL) return false;
			fast_ptr = fast_ptr->next;
			if (fast_ptr == slow_ptr) return true;
			i++;
			if (i % 2 == 0)slow_ptr = slow_ptr->next;
		}

		return false;

	}

};

