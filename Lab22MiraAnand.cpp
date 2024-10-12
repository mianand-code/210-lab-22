// COMSC-210 | Lab 22 | Mira Anand
// Module 7, Lesson: Doubly-Linked Lists & Class Destructors, Assignment: Upgrade the DLL Class
// IDE used: Visual Studio Code for Mac

#include <cstdlib> // needed to generate a random number
#include <ctime> // needed to generate a random number
#include <iostream>
using namespace std;

// declaration and initialization of const int variables
// the values being added to the linked list should be between 10 - 99
// the # of values being added to the linked list should be between 5 - 20
const int MIN_NUMBER = 10; // represents the minimum value to be added to the linked list, will be used to generate a random # in main()
const int MAX_NUMBER = 99; // represents the maximum value to be added to the linked list, will be used to generate a random # in main()
const int MIN_LIST_SIZE = 5; // represents the minimum # of values to be added to the linked list (list size), will be used to generate a random # in main()
const int MAX_LIST_SIZE = 20; // represents the maximum # of values to be added to the linked list (list size), will be used to generate a random # in main()

// creation of DoublyLinkedList Class
class DoublyLinkedList {
// private member variables
private:
    struct Node // struct definition within class
    {
        int data; // holds a int value
        Node* prev; // pointer to previous node
        Node* next; // pointer to next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) // constructor within struct
        {
            data = val;
            prev = p;
            next = n;
        }
    };
    
    // pointers to head and tail
    Node* head;
    Node* tail;

public:
    // constructor that initializes the pointers
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // void push_back(int value) function header
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to the end (tail) of the list
    // ARGUMENTS: int value, which is the number to be added to the list
    // RETURNS: nothing, void function
    void push_back(int value) 
    {
        Node* newNode = new Node(value); // create a new node and set its value

        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else // if the list is NOT empty
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // void push_front(int value) function header
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to the front (head) of the list
    // ARGUMENTS: int value, which is the number to be added to the list
    // RETURNS: nothing, void function
    void push_front(int value) 
    {
        Node* newNode = new Node(value); // create a new node and set its value

        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else // if the list is NOT empty
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // void insert_after(int value, int position) function header
    // DESCRIPTION:
    // ARGUMENTS: int value, which is the number to be added to the list
    // - int position, which represents the position/index where the value should be added
    // RETURNS: nothing, void function
    void insert_after(int value, int position) 
    {
        if (position < 0) 
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) 
        {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        
        if (!temp) 
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) 
    {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;
        
        if (!temp) return; // Value not found

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // Deleting the head

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deleting the tail
    
        delete temp;
    }

    void print() 
    {
        Node* current = head;
        if (!current) return;

        while (current) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() 
    {
        Node* current = tail;
        if (!current) return;

        while (current) 
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() 
    {
        while (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() 
{
    srand(time(0)); // needed as the first line in main() for randomization
    
    DoublyLinkedList list;
    int size = rand() % (MAX_LIST_SIZE - MIN_LIST_SIZE + 1) + MIN_LIST_SIZE;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER);
    
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    
    return 0;
}