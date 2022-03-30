#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    if (obj.head == NULL)
    {
        head = NULL;
    }
    else
    {
        head = new Node<T>(obj.head->data);
        Node<T> *curr = head;
        Node<T> *prevHolder;
        Node<T> *otherCurr = obj.head->next;
        while (otherCurr != obj.head)
        {
            curr->next = new Node<T>(otherCurr->data);
            prevHolder = curr;
            curr = curr->next;
            curr->prev = prevHolder;
            otherCurr = otherCurr->next;
        }
        //curr is now at the tail
        curr->next = head;
        head->prev = curr;
        size = obj.size;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    if (isEmpty())
    {
        return;
    }
    if (head->next == head)
    {
        delete head;
    }
    else
    {
        Node<T> *tail = head->prev;
        tail->next = NULL;
        Node<T> *tmp;
        while (head->next != NULL)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        delete head;
    }
    head = NULL;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    return head == NULL;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if(curr == node && curr->next == node->next && curr->prev == node->prev)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
     return isEmpty() ? NULL : head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    return isEmpty() ? NULL : head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if (curr->data == data)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
     if ((index < 0) || (index >= size))
    {
        return NULL;
    }
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if (i == index)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    if (isEmpty())
    {
        this->head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node<T> *tail = head->prev;
        Node<T> *newNode = new Node<T>(data);
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    if (isEmpty())
    {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node<T> *tail = head->prev;
        Node<T> *newNode = new Node<T>(data);
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    if (!contains(node))
    {
        return;
    }
    if (node == head->prev)
    {
        insertAtTheEnd(data);
    }
    else
    {
        Node<T> *newNode = new Node<T>(data);
        newNode->prev = node;
        newNode->next = node->next;
        node->next->prev = newNode;
        node->next = newNode;
        size++;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    if (k < 2 || k > size)
    {
        return;
    }
    Node<T> *tail = head->prev;
    Node<T> *tmp, *curr = head;
    int count = 0;
    while (curr != tail)
    {
        count++;
        if (count == k - 1)
        {
            tmp = curr->next;
            insertAfterNode(data, curr);
            curr = tmp;
            count = 0;
        }
        else
        {
            curr = curr->next;
        }
    }
    count++;
    if (count == k - 1)
    {
        insertAfterNode(data, curr);
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    if (!contains(node))
    {
        return;
    }

    Node<T> *prevNode = node->prev;
    Node<T> *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    if (node == head)
    {
        head = nextNode;
    }
    delete node;
    size--;
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    if (!getNode(data))
    {
        return;
    }

    if (head->next == head)
    {
        delete head;
        head = NULL;
        size--;
    }
    else
    {
        while (getNode(data))
        {
            Node<T> *node = getNode(data);
            Node<T> *prevNode = node->prev;

            Node<T> *nextNode = node->next;

            prevNode->next = nextNode;

            nextNode->prev = prevNode;
            if(node == head){
                head = nextNode;
            }
            delete node;

            size--;
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    if (isEmpty())
    {
        return;
    }
    if (head->next == head)
    {
        delete head;
        head = NULL;
    }
    else
    {
        Node<T> *tail = head->prev;
        tail->next = NULL;
        Node<T> *tmp;
        while (head->next != NULL)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        delete head;
        size = 0;
        head = NULL;
    }
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    if (k < 2 || k > size)
    {
        return;
    }
    int count = 0;
    Node<T> *tail = head->prev;
    Node<T> *curr = head;
    Node<T> *tmp;
    while (curr != tail)
    {
        count++;
        if (count == k)
        {
            tmp = curr->next;
            removeNode(curr);
            curr = tmp;
            count = 0;
        }
        else
        {
            curr = curr->next;
        }
    }
    count++;
    if (count == k)
    {
        removeNode(curr);
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    if (!contains(node1) || !contains(node2) || node1 == node2)
    {
        return;
    }
    if (node1 == head)
    {
        head = node2;
    }
    else if (node2 == head)
    {
        head = node1;
    }
    // adjecent nodes
    if (node1->next == node2)
    {
        // if (node1 == head)
        // {
        //     head = node2;
        // }
        // else if (node2 == head)
        // {
        //     head = node1;
        // }
        node1->next = node2->next;
        node1->prev->next = node2;
        node2->prev = node1->prev;
        node2->next->prev = node1;
        node2->next = node1;
        node1->prev = node2;
    }
    else if (node2->next == node1)
    {

        node2->next = node1->next;
        node2->prev->next = node1;
        node1->prev = node2->prev;
        node1->next->prev = node2;
        node1->next = node2;
        node2->prev = node1;
    }
    else
    {
        // not adjecent
        Node<T> *prev1 = node1->prev;
        Node<T> *prev2 = node2->prev;
        Node<T> *next1 = node1->next;
        Node<T> *next2 = node2->next;
        //swap node1
        node1->prev = prev2;
        node1->next = next2;
        prev2->next = node1;
        next2->prev = node1;
        //swap node2
        node2->prev = prev1;
        node2->next = next1;
        next1->prev = node2;
        prev1->next = node2;
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    for (int i = 0; i <= (size - 1); i++)
    {
        // std::
        swap(getNodeAtIndex(i), getNodeAtIndex((i * i + seed) % size));
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if (rhs.head == NULL)
    {
        head = NULL;
    }
    else
    {
        removeAllNodes();
        head = new Node<T>(rhs.head->data);
        Node<T> *curr = head;
        Node<T> *prevHolder;
        Node<T> *otherCurr = rhs.head->next;
        while (otherCurr != rhs.head)
        {
            curr->next = new Node<T>(otherCurr->data);
            prevHolder = curr;
            curr = curr->next;
            curr->prev = prevHolder;
            otherCurr = otherCurr->next;
        }
        //curr is now at the tail
        curr->next = head;
        head->prev = curr;
        size = rhs.size;
    }

    return *this;
}

#endif //LINKEDLIST_H
