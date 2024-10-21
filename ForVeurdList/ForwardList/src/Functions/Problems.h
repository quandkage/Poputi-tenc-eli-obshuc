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

bool isPalindrome(ListNode<int>* head) {
    if (!head || !head->next) {
        return true;
    }

    ListNode<int>* current = head;
    size_t count = 0;
    while (current) {
        current = current->next;
        count++;
    }

    size_t middle = count / 2;
    current = head;
    for (size_t i = 0; i < middle; i++) {
        current = current->next;
    }

    ListNode<int>* secondHalf = (count % 2 == 0) ? current : current->next;
    ListNode<int>* prev = nullptr;

    while (secondHalf) {
        ListNode<int>* nextNode = secondHalf->next;
        secondHalf->next = prev;
        prev = secondHalf;
        secondHalf = nextNode;
    }

    ListNode<int>* firstHalf = head;
    ListNode<int>* secondHalfRev = prev;

    while (secondHalfRev && firstHalf) {
        if (firstHalf->data != secondHalfRev->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalfRev = secondHalfRev->next;
    }

    return true;
}




