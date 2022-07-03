#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) :
        value(data) {
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() :
        size_(0) {
    head_ = nullptr;
    tail_ = nullptr;
}


DoublyLinkedList::~DoublyLinkedList() {

    // There are many different strategies for deleting.
    while (head_) {
        Node *tmp = head_;
        head_ = head_->next;
        delete tmp;
    }

    // Alternative approach. If you've written it once, reuse it.
    /*
    while (!this->empty()) {
        this->remove_front();
    }
    */
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    return size_ == 0;
}


bool DoublyLinkedList::full() const {
    return size_ >= CAPACITY ;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {

    // If the list is empty, just return something.
    if (this->empty()) {
        return 0;
    }

    // Get the node at the needed index.
    Node *nd = getNode(index);

    // Check if we were given a bad index to grab.
    // If yes, return the last elements value.
    if (nd == nullptr) {
        return tail_->value;
    }

    // Node at index is good, return it's value.
    return nd->value;
}


unsigned int DoublyLinkedList::search(DataType value) const {

    // Get a reference to the head node.
    Node *cur = head_;
    unsigned int index = 0;

    // Loop through until we find the index of the value
    // that we're looking for, or until we hit the end
    // of the list.
    while (cur) {

        if (cur->value == value) {
            return index;
        }

        ++index;
        cur = cur->next;
    }

    // If the value was not found in the list, we return index = size
    return index;
}


void DoublyLinkedList::print() const {

    std::cout << "number of Data = " << size() << std::endl;
    Node *cur = head_;
    while (cur) {
        std::cout << cur->value << " ";
        cur = cur->next;
    }

    std::cout << std::endl;
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {

    // Get a reference to the head node.
    Node *cur = head_;
    unsigned int count = 0;

    // Iterate through until the current node is the
    // node that corresponds to the desired index.
    while (count < index && cur != nullptr) {
        cur = cur->next;
        ++count;
    }

    // It is possible for cur to be nullptr if we gave an
    // index larger than size. Check appropriately.
    return cur;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {

    // Check that index is within an appropriate range.
    if (index > size() || index < 0 || full()) {
        return false;
    }

    // Check for front/back special cases.
    if (index == 0) {
        return insert_front(value);
    } else if (index == size()) {
        return insert_back(value);
    }

    // General case.
    Node *at_node  = getNode(index);
    Node *new_node = new Node(value);
    if (at_node == nullptr || new_node == nullptr) {
        return false; // something went wrong.
    }

    // Result should look like this.
    // [nodes_before] <-> [new_node] <-> [at_node] <-> [nodes_after]
    Node *nodes_before = at_node->prev;

    new_node->prev = nodes_before;
    nodes_before->next = new_node;

    new_node->next = at_node;
    at_node->prev = new_node;

    ++size_;
    return true;

}


bool DoublyLinkedList::insert_front(DataType value) {

    // Do a quick error check for bad states.
    if (full()) {
        return false;
    }

    // Create a new node.
    Node *new_node = new Node(value);

    if (!head_) {
        // Special case: empty list (head is null).
        head_ = new_node;
        tail_ = new_node;
    } else {
        // General case.
        head_->prev = new_node;
        new_node->next = head_;
        head_ = new_node;
    }
    ++size_;
    return true;

}


bool DoublyLinkedList::insert_back(DataType value) {

    // Do a quick error check for bad states.
    if (full()) {
        return false;
    }

    // Create a new node.
    Node *new_node = new Node(value);

    if (!head_) {
        // Special case: empty list (head is null).
        head_ = new_node;
        tail_ = new_node;
    } else {
        // General case.
        new_node->prev = tail_;
        tail_->next = new_node;
        tail_ = new_node;
    }
    ++size_;
    return true;
}


bool DoublyLinkedList::remove(unsigned int index) {

    // Check that index is within an appropriate range.
    if (index >= size() || index < 0 || empty()) {
        return false;
    }

    // Check for front/back special cases.
    if (index == 0) {
        return remove_front();
    }
    if (index == size() - 1) {
        return remove_back();
    }

    // General case.
    Node *at_node = getNode(index);
    if (at_node == nullptr) {
        return false; // something went wrong.
    }

    // Result should look like this.
    // [nodes_before] <-> [nodes_after]
    Node *nodes_before = at_node->prev;
    Node *nodes_after  = at_node->next;

    nodes_before->next = nodes_after;
    nodes_after->prev = nodes_before;

    // Now safe to remove.
    delete at_node;
    --size_;

    return true;
}


bool DoublyLinkedList::remove_front() {

    // Do a quick error check for bad states.
    if (empty()) {
        return false;
    }

    // Get a reference to the front node.
    Node *at_node = head_;

    // Update the head pointer.
    head_ = head_->next;

    // Safe to delete the front node.
    delete at_node;
    --size_;

    // Update the new heads pointers appropriately (prevent dangling pointers).
    if (head_) {
        head_->prev = NULL;
    } else {
        // Special case: the list is now empty (head_ is null).
        tail_ = NULL;
    }

    return true;
}


bool DoublyLinkedList::remove_back() {

    // Do a quick error check for bad states.
    if (empty()) {
        return false;
    }

    // Get a reference to the back node.
    Node *at_node = tail_;

    // Update the tail pointer.
    tail_ = tail_->prev;

    // Safe to delete the back node.
    delete at_node;
    --size_;

    // Update the new tails pointers appropriately (prevent dangling pointers).
    if (tail_) {
        tail_->next = NULL;
    } else {
        // Special case: the list is now empty (tail_ is null).
        head_ = NULL;
    }

    return true;
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {

    // Get a reference to the node.
    Node *at_node = getNode(index);
    if (at_node == nullptr) {
        return false; // something went wrong.
    }

    // Change this nodes value
    at_node->value = value;

    return true;
}