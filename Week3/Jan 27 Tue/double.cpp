#include <iostream>

struct Node {
    int data;
    Node* next;
};

void insertAtHead(Node*& head, int value)
{
    Node* newNode = new Node{value, head};
    head = newNode;
}

void printList(Node* head)
{
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "NULL\n";
}

int main()
{
    Node* head = nullptr;

    insertAtHead(head, 10);
    insertAtHead(head, 20);
    insertAtHead(head, 30);

    printList(head);
}
