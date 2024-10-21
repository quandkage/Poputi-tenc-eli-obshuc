#pragma once
#include "ForwardList.h"

int binDec(ListNode<int>* head) {
    int res = 0;
    ListNode<int>* current = head;
    while (current) {
        res = res * 2 + *(current->data);
        current = current->next;
    }
    return res;
}


ListNode<int>* middleNode(ListNode<int>* head) {
    if(!head){ return nullptr; }
    ListNode<int>* current = head;
    size_t count  = 0;
    while(current) {
        current = current->next;
        count++;
    }
    size_t middle = count / 2;
    current = head;
    for(int i = 0; i < middle; i++) {
        current = current->next;
    }
    return current;
}

ListNode<int>* removeElements(ListNode<int>* head, int k) {
    ListNode<int>* dummy = new ListNode<int>(0);
    dummy->next = head;
    ListNode<int>* current = dummy;

    while (current->next) {
        if (*(current->next->data) == k) {
            ListNode<int>* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    ListNode<int>* newHead = dummy->next;
    delete dummy;
    return newHead;
}

ListNode<int>* removeDuplicates(ListNode<int>* head) {
    if (!head) return nullptr;
    ListNode<int>* current = head;
    while (current && current->next) {
        if (*(current->data) == *(current->next->data)) {
            ListNode<int>* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    return head;
}


ListNode<int>* reverseList(ListNode<int>* head) {
    ListNode<int>* prev = nullptr;
    ListNode<int>* current = head;

    while (current) {
        ListNode<int>* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

bool isPalindrome(ListNode<int>* head) {
    if (!head || !head->next) {
        return true;
    }

    ListNode<int>* slow = head;
    ListNode<int>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode<int>* secondHalf = reverseList(slow);
    ListNode<int>* firstHalf = head;
    bool isPalin = true;
    while (secondHalf) {
        if (firstHalf->data != secondHalf->data) {
            isPalin = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    return isPalin;
}

void reorderList(ListNode<int>* head) {
    if (!head || !head->next) return;

    ListNode<int>* current = head;
    size_t count = 0;
    while (current) {
        current = current->next;
        count++;
    }
    size_t middle = count / 2;

    ListNode<int>* middleNode = head;
    for (size_t i = 0; i < middle; i++) {
        middleNode = middleNode->next;
    }
    ListNode<int>* secondHalf = reverseList(middleNode);
    ListNode<int>* firstHalf = head;

    while (secondHalf) {
        ListNode<int>* temp1 = firstHalf->next;
        ListNode<int>* temp2 = secondHalf->next;

        firstHalf->next = secondHalf;
        secondHalf->next = temp1;

        firstHalf = temp1;
        secondHalf = temp2;
    }
}





