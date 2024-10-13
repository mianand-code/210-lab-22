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
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to a certain position within the linked list
    // - ensures that the position is valid before proceeding with deletion
    // ARGUMENTS: int value, which is the number to be added to the list
    // - int position, which represents the position/index where the value should be added
    // RETURNS: nothing, void function
    void insert_after(int value, int position) 
    {
        // ensures that position is greater than or equal to 0 before proceeding
        if (position < 0) 
        {
            cout << "Position must be >= 0. Insertion by position cannot be performed." << endl;
            return; // exit the function
        }

        Node* newNode = new Node(value); // create a new node and set its value

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
            return; // exit the function
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // void delete_val(int value) function header
    // DESCRIPTION: this function will traverse the list to find a value to delete and then delete that value from the list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // - deletion will also not be performed if the value was not found in the list
    // ARGUMENTS: int value, which is the number to be added to the list
    // RETURNS: nothing, void function
    void delete_val(int value) // changing name from delete_node() to delete_val(), as per assignment instructions
    {
        if (!head) // list is empty
        {
            cout << "The linked list is empty. Deletion by value cannot be performed." << endl;
            return; // exit the function
        }

        Node* temp = head; // set temp to head
        while (temp && temp->data != value) // traverse list to find value to be deleted
            temp = temp->next;
        
        if (!temp) // value not found
        {
            cout << "The value was not found in the linked list. Deletion by value cannot be performed." << endl;
            return; // exit the function
        }

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // Deleting the head, keep this functionality for purposes of class completeness

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deleting the tail
    
        delete temp; // perform deletion
    }

    // void delete_pos(int position) function header
    // DESCRIPTION: this function will traverse the list to find the position (index) of a value to delete and then delete that value from the list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // - deletion will also not be performed if the position is not within the bounds of the linked list
    // ARGUMENTS: int position, which is the position/index of the value to be deleted from the list
    // RETURNS: nothing, void function
    void delete_pos(int position) // creating a new method to upgrade the class, as per assignment instructions
    {
        if (position < 0) // ensures that position is greater than or equal to 0 before proceeding
        {
            cout << "Position must be >= 0. Deletion by position cannot be performed." << endl;
            return; // exit the function
        }

        if (!head) // list is empty
        {
            cout << "The linked list is empty. Deletion by position cannot be performed." << endl;
            return; // exit the function
        }

        Node* temp = head; // set temp to head
        for (int i = 0; i < position && temp; i++) // traverse list to find the position of the value to be deleted
            temp = temp->next;
        
        if (!temp) // position is not within bounds of the linked list
        {
            cout << "The position is not within the bounds of the linked list. Deletion by position cannot be performed." << endl;
            return; // exit the function
        }

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // Deleting the head

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deleting the tail
    
        delete temp; // perform deletion
    }

    // void pop_front() function header
    // DESCRIPTION: this function will delete the head node from the linked list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void pop_front() // creating a new method to upgrade the class, as per assignment instructions
    {
        if (!head) // list is empty
        {
            cout << "The linked list is empty. Head deletion cannot be performed." << endl;
            return; // exit the function
        }

        Node* temp = head; // set temp to head
        head = head->next; // update head to point to the next node

        if (head) // if head does not equal nullptr
            head->prev = nullptr; // previous node should be equal to nullptr
        else // if head equals nullptr
            tail = nullptr; // tail should also be equal to nullptr
        
        delete temp; // perform deletion
    }

    // void pop_back() function header
    // DESCRIPTION: this function will delete the tail node from the linked list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void pop_back() // creating a new method to upgrade the class, as per assignment instructions
    {
        if (!tail) // list is empty
        {
            cout << "The linked list is empty. Tail deletion cannot be performed." << endl;
            return; // exit the function
        }

        Node* temp = tail; // set temp to tail
        tail = tail->prev; // update tail to point to the previous node

        if (tail) // if tail does not equal nullptr
            tail->next = nullptr; // next node should be equal to nullptr
        else // if tail equals nullptr
            head = nullptr; // head should also be equal to nullptr
        
        delete temp; // perform deletion
    }

    // void print() function header
    // DESCRIPTION: this function will check if the linked list is empty or not before outputting the contents of the list to the console
    // - if there are no contents, the user will be notified with a console message
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void print() 
    {
        Node* current = head; // set current to head, to start at the beginning of the list

        if (!current) // list is empty
        {
            cout << "The linked list is empty. No data can be displayed." << endl;
            return; // exit the function
        }

        while (current) // traverse the list and display its contents
        {
            cout << current->data << " ";
            current = current->next; // progress to next node
        }
        cout << endl;
    }

    // void print_reverse() function header
    // DESCRIPTION: this function will check if the linked list is empty or not before outputting the contents of the list to the console IN REVERSE
    // - if there are no contents, the user will be notified with a console message
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void print_reverse() 
    {
        Node* current = tail; // set current to tail, to start at the end of the list
        
        if (!current) // list is empty
        {
            cout << "The linked list is empty. No data can be displayed." << endl;
            return; // exit function
        }

        while (current) // traverse the list and display its contents
        {
            cout << current->data << " ";
            current = current->prev; // progress to previous node, to print in reverse
        }
        cout << endl;
    }

    // class destructor, to delete all nodes
    ~DoublyLinkedList() 
    {
        while (head) // traverse list, while head does not hit nullptr
        {
            Node* temp = head; // set temp to head to traverse list
            head = head->next; // set head to the node after the one to be deleted
            delete temp; // perform deletion
        }
    }
};

// Driver program
int main() 
{
    srand(time(0)); // needed as the first line in main() for randomization
    
    DoublyLinkedList list; // creation of a DoublyLinkedList object

    // declaration and initialization of a int variable "size", that will generate a random # between 5 - 20
    // this will be the number of values being added to the linked list
    int size = rand() % (MAX_LIST_SIZE - MIN_LIST_SIZE + 1) + MIN_LIST_SIZE;

    for (int i = 0; i < size; ++i) // loop that continues until it hits "size"
        // push_back() function call, adds random values between 10 - 99 to the end of the linked list
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