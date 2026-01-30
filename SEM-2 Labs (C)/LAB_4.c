/*
 * LAB_4.c - Singly Linked List Implementation for Student Records
 * This program demonstrates various operations on a singly linked list:
 * - Insert at front, end, or specific position
 * - Delete from front, end, or by USN
 * - Display all records and count students
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Student node in the singly linked list
// Each node contains student information and a pointer to the next node
struct Student
{
    char USN[20];          // Unique Student Number
    char Name[50];         // Student's name
    char Branch[20];       // Branch/Department
    int sem;               // Semester number
    char Phone_Number[20]; // Contact number

    struct Student *next; // Pointer to the next student node in the list
};

// Global pointer to the first node (head) of the linked list
struct Student *head = NULL;

// Function to create a new student node and take input from user
// Returns: pointer to the newly created node, or NULL if memory allocation fails
struct Student *createNode()
{
    // Dynamically allocate memory for a new student node
    struct Student *temp = (struct Student *)malloc(sizeof(struct Student));

    // Check if memory allocation was successful
    if (temp == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // Collect student information from user
    printf("Enter USN: ");
    scanf("%s", temp->USN);
    printf("Enter Name: ");
    scanf("%s", temp->Name);
    printf("Enter Branch: ");
    scanf("%s", temp->Branch);
    printf("Enter sem: ");
    scanf("%d", &temp->sem);
    printf("Enter your Phone Number: ");
    scanf("%s", temp->Phone_Number);

    // Initialize next pointer to NULL (this will be the last node initially)
    temp->next = NULL;
    return temp;
}

// Function to insert a new student node at the front (beginning) of the linked list
// Time Complexity: O(1) - constant time operation
void Insert_Front()
{
    // Create a new student node with user input
    struct Student *newNode = createNode();

    // Check if node creation was successful
    if (newNode == NULL)
    {
        return;
    }
    // Case 1: If list is empty, make the new node as head
    if (head == NULL)
    {
        head = newNode;
    }
    // Case 2: If list is not empty, insert new node before current head
    else
    {
        newNode->next = head; // Make new node point to current first node
        head = newNode;       // Update head to point to new node
    }
    printf("Student inserted at the front successfully!\n");
}

// Function to insert a new student node at the end of the linked list
// Time Complexity: O(n) - needs to traverse entire list to find last node
void Insert_End()
{
    // Create a new student node with user input
    struct Student *newNode = createNode();

    // Check if node creation was successful
    if (newNode == NULL)
    {
        return;
    }
    // Case 1: If list is empty, make the new node as head
    if (head == NULL)
    {
        head = newNode;
    }
    // Case 2: If list is not empty, traverse to the end and insert
    else
    {
        struct Student *temp = head; // Start from the first node

        // LOOP LOGIC: Traverse the list until we reach the last node
        // The last node is identified by temp->next == NULL
        // Continue moving to next node as long as current node is not the last
        while (temp->next != NULL)
        {
            temp = temp->next; // Move to the next node
        }
        // After loop, temp points to the last node
        temp->next = newNode; // Link the last node to the new node
    }
    printf("Student inserted at the end successfully!\n");
}

// Function to insert a student node at a specific 1-based position
// Time Complexity: O(n) - may traverse the list to reach the position
void Insert_At_Position()
{
    int position;

    printf("Enter the position (1-based) to insert the new student: ");
    scanf("%d", &position);

    // Validate position input
    if (position <= 0)
    {
        printf("Invalid position. Position must be 1 or greater.\n");
        return;
    }

    // If list is empty, only position 1 is valid
    if (head == NULL && position != 1)
    {
        printf("List is empty. You can only insert at position 1.\n");
        return;
    }

    struct Student *newNode = createNode();
    if (newNode == NULL)
    {
        return;
    }

    // Insert at the head when position is 1
    if (position == 1)
    {
        newNode->next = head;
        head = newNode;
        printf("Student inserted at position %d successfully!\n", position);
        return;
    }

    // Traverse to the node just before the desired position
    struct Student *temp = head;
    int currentPos = 1;
    while (temp != NULL && currentPos < position - 1)
    {
        temp = temp->next;
        currentPos++;
    }

    // If position is beyond current length+1, insertion is invalid
    if (temp == NULL)
    {
        printf("Position exceeds the current list length. Insertion failed.\n");
        free(newNode);
        return;
    }

    // Link the new node into the list
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Student inserted at position %d successfully!\n", position);
}

// Function to delete the first node from the linked list
// Time Complexity: O(1) - constant time operation
void Delete_Front()
{
    // Check if list is empty
    if (head == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    else
    {
        struct Student *temp = head; // Store reference to current first node
        head = head->next;           // Move head to the next node
        free(temp);                  // Free memory of the deleted node
        printf("Student deleted from the front successfully!\n");
    }
}
// Function to delete the last node from the linked list
// Time Complexity: O(n) - needs to traverse to second-last node
void Delete_End()
{
    // Case 1: Check if list is empty
    if (head == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }
 
    // Case 2: If list has only one node
    if (head->next == NULL)
    {
        free(head);  // Free the only node
        head = NULL; // Set head to NULL to indicate empty list
        printf("Student deleted from the end successfully!\n");
    }
    // Case 3: If list has multiple nodes
    else
    {
        struct Student *temp = head; // Start from first node

        // LOOP LOGIC: Traverse until we reach the second-last node
        // We need second-last node because we need to update its 'next' pointer
        // temp->next->next == NULL means temp is pointing to second-last node
        // Continue moving forward as long as the next node is not the last node
        while (temp->next->next != NULL)
        {
            temp = temp->next; // Move to next node
        }
        // After loop, temp points to the second-last node
        free(temp->next); // Free the last node (temp->next)

        temp->next = NULL; // Update second-last node's next to NULL
        printf("Student deleted from the end successfully!\n");
    }
}

// Function to delete a student node by searching for a specific USN
// Time Complexity: O(n) - may need to traverse entire list to find the target
void Delete_By_USN()
{
    char target[20]; // Variable to store the target USN to search for
    
    // Check if list is empty
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    // Get the USN to search for from user
    printf("Enter the USN of the student you want to delete: ");
    scanf("%s", target);

    // Case 1: Check if the head node itself is the target
    if (strcmp(head->USN, target) == 0)
    {
        struct Student *temp = head; // Store reference to current head
        head = head->next;           // Move head to next node
        free(temp);                  // Free the deleted node
        printf("Student with USN %s was deleted successfully!\n", target);
        return;
    }
    
    // Case 2: Search for the target USN in the rest of the list
    struct Student *temp = head; // Start from head
    
    // LOOP LOGIC: Traverse until we find the node before the target
    // We need the previous node to update its 'next' pointer
    // Continue while: (1) next node exists AND (2) next node's USN doesn't match
    while (temp->next != NULL && strcmp(temp->next->USN, target) != 0)
    {
        temp = temp->next; // Move to next node
    }

    // After loop, check if target was found
    if (temp->next == NULL)
    {
        printf("Student with USN %s not found in the list!\n", target);
    }
    else
    {
        // Target found - delete the node
        struct Student *to_Delete = temp->next;  // Store node to delete
        temp->next = temp->next->next;           // Bypass the node to delete
        free(to_Delete);                         // Free memory
        printf("Student with USN %s was successfully deleted.\n", target);
    }
}

// Function to display all student records and count total students
// Time Complexity: O(n) - traverses entire list once
void Display()
{
    // Check if list is empty
    if (head == NULL)
    {
        printf("List is empty. No students to display.\n");
        return;
    }
    else
    {
        struct Student *temp = head; // Start from the first node
        int count = 0;               // Counter to track number of students

        printf("\n--- Student Records ---\n");
        // LOOP LOGIC: Traverse through entire list and display each student
        // Continue until we reach the end of list (temp becomes NULL)
        // At the end of list, the last node's next pointer is NULL
        while (temp != NULL)
        {
            // Display current student's information
            printf("\n[Student %d]\n", count + 1);
            printf("USN: %s\n", temp->USN);
            printf("Name: %s\n", temp->Name);
            printf("Branch: %s\n", temp->Branch);
            printf("Phone Number: %s\n", temp->Phone_Number);
            printf("Semester: %d\n", temp->sem);

            temp = temp->next; // Move to the next node in the list
            count++;           // Increment student counter
        }
        // After loop completes, all nodes have been visited
        printf("\nTotal number of students: %d\n", count);
    }
}

// Function to free all nodes in the list (cleanup before exit)
void freeList()
{
    struct Student *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main function - Entry point of the program
int main()
{
    int choice; // Variable to store user's menu choice

    // Display menu options to user (shown only once)
    printf("\n=== SINGLY LINKED LIST MENU ===\n");
    printf("1. Create / Insert at Front\n"); // Syllabus asks to create using front insertion
    printf("2. Insert at End\n");
    printf("3. Insert at a specific position\n");
    printf("4. Delete from Front\n");
    printf("5. Delete from End\n");
    printf("6. Delete by specific USN\n");
    printf("7. Display & Count\n");
    printf("8. Exit\n");
    printf("================================\n");

    // DO-WHILE LOOP LOGIC: Menu-driven program that runs repeatedly
    // The loop ensures menu is displayed at least once
    // It continues executing until user chooses option 7 (Exit)
    // Loop condition is checked AFTER executing the loop body
    do
    {
        printf("\nEnter choice: ");
        scanf("%d", &choice); // Read user's choice

        // Use switch-case to execute corresponding function based on choice
        switch (choice)
        {
        case 1:
            Insert_Front(); // Insert new student at beginning
            break;
        case 2:
            Insert_End(); // Insert new student at end
            break;
        case 3:
            Insert_At_Position(); // Insert new student at a specific position
            break;
        case 4:
            Delete_Front(); // Remove student from beginning
            break;
        case 5:
            Delete_End(); // Remove student from end
            break;
        case 6:
            Delete_By_USN(); // Delete student by searching for specific USN
            break;
        case 7:
            Display(); // Display all students and count
            break;
        case 8:
            printf("Exiting the program...\n"); // Exit the program
            break;
        default:
            printf("Invalid choice! Please try again.\n"); // Handle invalid input
        }
    } while (choice != 8); // Loop continues until user enters 8

    // Free all allocated memory before exiting
    freeList();

    return 0;
}