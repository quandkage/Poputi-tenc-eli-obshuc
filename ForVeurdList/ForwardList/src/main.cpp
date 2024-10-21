/*
The tests are made via header files. When you include the header file the corresponding test starts to execute. Feel free to comment the corresponding "#include <Header.h>" to ensure that it will not compile during your test.

All your code must be in "ForwardList.h"
*/
#include "1BasicConstructorsTest.h"
#include "2PushFrontTest.h"
#include "3PopFrontTest.h"
#include "4DestructorCallTest.h"
#include "5CopyConstructorTest.h"
#include "6AssignmentOperatorTest.h"
#include "7DestructorWithAssignmentTest.h"
#include "8EmplaceFrontTest.h"
#include "9FrontTest.h"
#include "10ClearTest.h"
#include "11BasicIteratorTest.h"
#include "12ConstIteratorTest.h"
#include "13MemberAccessIteratorTest.h"
#include "14InitializerListConstructorTest.h"
//#include "15IteratorConstructibleTest.h"
//#include "16ClassWithNoDefaultConstructorTest.h"
//#include "17InsertTest.h"
//#include "18EraseTest.h"
#include "19StlCompatibilityTest.h"

#include <iostream>
#include <optional>
#include "ForwardList.h"
#include "Functions/Problems.h"


int main()
{
    std::optional<std::string> msg; // just to make sure this works - click "Run".
    msg = "All tests passed";
    std::cout << *msg << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 1" << std::endl;
    ForwardList<int> test1 = {1,0,1,1};
    std::cout << "Decimal -> " << binDec(test1.head_node()) << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 2" << std::endl;
    ForwardList<int> test2 = {4, 3, 10, 1,1,1};
    ListNode<int>* middle = middleNode(test2.head_node());
    if (middle) {
        std::cout << "The middle node value is: " << *(middle->data) << std::endl;
    }
    std::cout << "----------------" << std::endl;
    std::cout << "Test 3" << std::endl;
    ForwardList<int> list1 = {1, 2, 3, 4, 3, 5};
    ListNode<int>* newHead1 = removeElements(list1.head_node(), 3);
    std::cout << "After removing 3: ";
    for (ListNode<int>* curr = newHead1; curr; curr = curr->next) {
        std::cout << *(curr->data) << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 4" << std::endl;
    ForwardList<int> list3 = {1, 1, 2, 3, 3, 4,4,5,5,6,6,7,7,8,8,9,9,10};
    ListNode<int>* newHead3 = removeDuplicates(list3.head_node());
    std::cout << "After removing duplicates : ";
    for (ListNode<int>* curr = newHead3; curr; curr = curr->next) {
        std::cout << *(curr->data) << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 5" << std::endl;
    ForwardList<int> list5 = {1, 2, 3, 2, 1};
    std::cout << "Is {1, 2, 3, 2, 1} a palindrome? -> " << (isPalindrome(list5.head_node()) ? "true" : "false") << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 6" << std::endl;
    ForwardList<int> list6 = {1, 2, 3, 4, 5};
    reorderList(list6.head_node());
    std::cout << "After reordering : ";
    for (ListNode<int>* curr = list6.head_node(); curr; curr = curr->next) {
        std::cout << *(curr->data) << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    return 0;
}
