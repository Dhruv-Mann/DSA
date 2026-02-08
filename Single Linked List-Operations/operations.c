#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Global head pointer
struct Node* head = NULL;

// Function prototypes
void createList();
void traverseList();
void insertAtBeginning();
void insertAtEnd();
void insertAtPosition();
void deleteAtBeginning();
void deleteAtEnd();
void deleteAtPosition();
void deleteByValue();
void searchElement();
void countNodes();
void reverseList();
void sortList();
void displayMenu();

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create initial list
void createList() {
    int n, value;
    struct Node* temp;
    
    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);
        
        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;
        
        if (head == NULL) {
            head = newNode;
            temp = head;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }
    printf("\nList created successfully!\n");
}

// Function to traverse and display the list
void traverseList() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    struct Node* temp = head;
    printf("\nLinked List: ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

// Function to insert at the beginning
void insertAtBeginning() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    newNode->next = head;
    head = newNode;
    printf("\nNode inserted at the beginning successfully!\n");
}

// Function to insert at the end
void insertAtEnd() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("\nNode inserted at the end successfully!\n");
}

// Function to insert at a specific position
void insertAtPosition() {
    int value, position;
    printf("\nEnter the position (1-based): ");
    scanf("%d", &position);
    
    if (position < 1) {
        printf("\nInvalid position!\n");
        return;
    }
    
    printf("Enter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    if (position == 1) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Node* temp = head;
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }
        
        if (temp == NULL) {
            printf("\nPosition out of range!\n");
            free(newNode);
            return;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
    }
    printf("\nNode inserted at position %d successfully!\n", position);
}

// Function to delete from the beginning
void deleteAtBeginning() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    struct Node* temp = head;
    head = head->next;
    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

// Function to delete from the end
void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    if (head->next == NULL) {
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }
    
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    printf("\nDeleted node with value: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

// Function to delete from a specific position
void deleteAtPosition() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    int position;
    printf("\nEnter the position to delete (1-based): ");
    scanf("%d", &position);
    
    if (position < 1) {
        printf("\nInvalid position!\n");
        return;
    }
    
    if (position == 1) {
        struct Node* temp = head;
        head = head->next;
        printf("\nDeleted node with value: %d\n", temp->data);
        free(temp);
        return;
    }
    
    struct Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->next == NULL) {
        printf("\nPosition out of range!\n");
        return;
    }
    
    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

// Function to delete by value
void deleteByValue() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);
    
    // If head node contains the value
    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        printf("\nDeleted node with value: %d\n", temp->data);
        free(temp);
        return;
    }
    
    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    
    if (temp->next == NULL) {
        printf("\nValue %d not found in the list!\n", value);
        return;
    }
    
    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

// Function to search for an element
void searchElement() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    int value, position = 1;
    printf("\nEnter the value to search: ");
    scanf("%d", &value);
    
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("\nValue %d found at position %d\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    
    printf("\nValue %d not found in the list!\n", value);
}

// Function to count nodes
void countNodes() {
    int count = 0;
    struct Node* temp = head;
    
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    printf("\nTotal number of nodes: %d\n", count);
}

// Function to reverse the list
void reverseList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }
    
    struct Node *prev = NULL, *current = head, *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
    printf("\nList reversed successfully!\n");
}

// Function to sort the list (Bubble Sort)
void sortList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }
    
    int swapped;
    struct Node *ptr1, *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    printf("\nList sorted successfully!\n");
}

// Function to display menu
void displayMenu() {
    printf("\n========================================");
    printf("\n    LINKED LIST OPERATIONS MENU");
    printf("\n========================================");
    printf("\n1.  Create List");
    printf("\n2.  Traverse/Display List");
    printf("\n3.  Insert at Beginning");
    printf("\n4.  Insert at End");
    printf("\n5.  Insert at Position");
    printf("\n6.  Delete from Beginning");
    printf("\n7.  Delete from End");
    printf("\n8.  Delete from Position");
    printf("\n9.  Delete by Value");
    printf("\n10. Search Element");
    printf("\n11. Count Nodes");
    printf("\n12. Reverse List");
    printf("\n13. Sort List");
    printf("\n14. Exit");
    printf("\n========================================");
    printf("\nEnter your choice: ");
}

// Main function
int main() {
    int choice;
    
    printf("\n*** LINKED LIST OPERATIONS PROGRAM ***\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createList();
                break;
            case 2:
                traverseList();
                break;
            case 3:
                insertAtBeginning();
                break;
            case 4:
                insertAtEnd();
                break;
            case 5:
                insertAtPosition();
                break;
            case 6:
                deleteAtBeginning();
                break;
            case 7:
                deleteAtEnd();
                break;
            case 8:
                deleteAtPosition();
                break;
            case 9:
                deleteByValue();
                break;
            case 10:
                searchElement();
                break;
            case 11:
                countNodes();
                break;
            case 12:
                reverseList();
                break;
            case 13:
                sortList();
                break;
            case 14:
                printf("\nExiting program. Goodbye!\n");
                // Free all nodes before exiting
                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
