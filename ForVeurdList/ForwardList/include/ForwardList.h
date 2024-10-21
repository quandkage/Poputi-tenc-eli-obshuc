#pragma once

#include <iostream>
#include <utility>
#include <vector>
template<class T>
class ListNode {
public:
    T *data = nullptr; //std::optional<T> #include <optional>
    ListNode *next = nullptr;
public:
    ListNode() : data(nullptr), next(nullptr) {}

    template<class...Args>
    ListNode(Args &&... args): data{new T(std::forward<Args>(args)...)}, next(nullptr) {} // here forgot (args)

    ~ListNode() {
        delete data;
    }
    friend std::ostream &operator<<(std::ostream &os, const ListNode &node) {
        if(node.data) {
            os << node.data;
        }
        return os;
    }
};

template<class T>
class ForwardList {
private:
    ListNode<T> *head = nullptr;

public:
    ForwardList() : head(nullptr) {}

    // ForwardList<int> l{2};
    explicit ForwardList(size_t size, const T &value = T()) {
        for (size_t i = 0; i < size; ++i) {
            push_front(value);
        }
    }

    void push_front(ListNode<T> *node) {
        if (!node) {
            return;
        }
        if (!head) {
            head = node;
        } else {
            ListNode<T> *tmp = head;
            head = node;
            head->next = tmp;
        }
    }

    void push_front(const T &value) {
        auto newNode = new ListNode<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Pop front method to remove the first element
    void pop_front() {
        if (head == nullptr) return;
        ListNode<T> *tmpHead = head;

        head = head->next;
        delete tmpHead;
    }


    // Copy constructor
    ForwardList(const ForwardList<T> &rhs) : head(nullptr) {
        if (rhs.head) {
            head = new ListNode<T>(*(rhs.head->data));
            ListNode<T>* currNode = head;
            ListNode<T>* thisCurr = rhs.head->next;

            while (thisCurr) {
                currNode->next = new ListNode<T>(*(thisCurr->data));
                currNode = currNode->next;
                thisCurr = thisCurr->next;
            }
        }
    }
    // Equality operator
    friend bool operator==(const ForwardList<T> &lhs, const ForwardList<T> &rhs) {
        ListNode<T> *currLhs = lhs.head;
        ListNode<T> *currRhs = rhs.head;
        while (currLhs && currRhs) {
            if (*(currLhs->data) != *(currRhs->data)) {
                return false;
            }
            currLhs = currLhs->next;
            currRhs = currRhs->next;
        }
        return currLhs == nullptr && currRhs == nullptr;
    }

    // Inequality operator
    friend bool operator!=(const ForwardList<T> &lhs, const ForwardList<T> &rhs) {
        return !(lhs == rhs);
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    bool empty() const {
        return head == nullptr;
    };

    ListNode<T>* head_node() const {
        return head;
    }

    T& front() {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return *(head->data);
    }

    const T& front() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return *(head->data);
    }

    ~ForwardList() {
        clear();
    }

    // Initializer list constructor
    ForwardList(const std::initializer_list<T> &init_list) : head(nullptr) {
        for (const T& value : init_list) {
            push_front(value);
        }
        if (head) {
            ListNode<T>* prev = nullptr;
            ListNode<T>* current = head;
            while (current) {
                ListNode<T>* next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }
    }

    // type alias
    template <typename Iter>
    using IsIterator = typename std::enable_if<
            !std::is_integral<Iter>::value &&
            !std::is_same<typename std::iterator_traits<Iter>::value_type, void>::value
    >::type;

    template <typename Iter, typename = IsIterator<Iter>>
    ForwardList(Iter begin, Iter end) {
        while (begin != end) {
            push_front(*begin);
            ++begin;
        }
    }


    // Emplace front function to construct element in-place
    template<typename... Args>
    T &emplace_front(Args &&... args) {
        auto newNode = new ListNode<T>(std::forward<Args>(args)...);
        newNode->next = head;
        head = newNode;
        return *(newNode->data);
    }

    // Swap function to swap two forward lists
    void swap(ForwardList &other) {
        std::swap(head, other.head);
    }

    // Assignment Operator (hint -> use swap for this)
    ForwardList<T>& operator=(const ForwardList<T>& rhs) {
        if (this != &rhs) {
            ForwardList<T> temp(rhs);
            swap(temp);
        }
        return *this;
    }


    class const_iterator;
    class iterator {
        ListNode<T> *current;

        friend class ForwardList<T>::const_iterator;
        friend class ForwardList<T>;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::forward_iterator_tag;

        iterator(ListNode<T> *node) : current(node) {}

        reference operator*() const {
            return *current->data;
        }
        pointer operator->() const {
            return current->data;
        }
        iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            current = current ? current->next : nullptr;
            return temp;
        }
        friend bool operator==(const iterator &lhs, const iterator &rhs) {
            return lhs.current == rhs.current;
        }
        friend bool operator!=(const iterator &lhs, const iterator &rhs) {
            return !(lhs.current == rhs.current);
        }

    };

    class const_iterator {
        const  ListNode<T> *current;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T *;
        using reference = const T &;
        using iterator_category = std::forward_iterator_tag;

        const_iterator(const iterator &it): current(it.current) {
        }

        const_iterator(const ListNode<T> *node) : current(node) {}


        reference operator*() const {
            return *(current->data);
        }
        pointer operator->() const {
            return current->data;
        }
        const_iterator operator++(int) {
            const_iterator temp = *this;
            current = current ? current->next : nullptr;
            return temp;
        }

        friend bool operator==(const const_iterator &lhs, const const_iterator &rhs) {
            return lhs.current == rhs.current;
        }
        friend bool operator!=(const const_iterator &lhs, const const_iterator &rhs) {
            return !(lhs.current == rhs.current);
        }
    };

    // Begin and end functions for iterators
    iterator begin() {
        return iterator(head);
    }

    iterator before_begin() const {
        return iterator(nullptr);
    }
    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }
    const_iterator cbegin() const {
        return const_iterator(head);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }
};
