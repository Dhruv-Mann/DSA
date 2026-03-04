#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 *  CIRCULAR DOUBLY LINKED LIST — COMPLETE OPERATIONS
 * ============================================================================
 *
 *  A Circular Doubly Linked List (CDLL) combines two concepts:
 *    1. Doubly linked — each node has 'next' AND 'prev' pointers.
 *    2. Circular — the last node's 'next' points to head, and head's 'prev'
 *       points to the last node. There is NO NULL anywhere.
 *
 *  Visually:
 *    +---> [10] <---> [20] <---> [30] <---+
 *    |      ^                       |      |
 *    |      |     (prev links)      |      |
 *    |      +-----------------------+      |
 *    +-------------------------------------+
 *              (next links form a circle)
 *
 *  This is the most "connected" linked list variant:
 *    - From any node, you can reach any other node going forward OR backward.
 *    - head->prev gives you the LAST node in O(1).
 *    - lastNode->next gives you the HEAD in O(1).
 *
 *  Key advantage:
 *    - O(1) access to both head and tail (via head->prev).
 *    - O(1) insertion/deletion at both ends without traversal.
 *    - Bidirectional circular traversal.
 *
 *  Key disadvantage:
 *    - Most complex pointer management — every insert/delete updates 4 pointers.
 *    - Highest memory overhead (two pointers per node).
 *
 * ============================================================================
 */

/*
 * Node structure for a circular doubly linked list.
 * Each node has data, a forward pointer (next), and a backward pointer (prev).
 */
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

/*
 * Global head pointer.
 * In a CDLL:
 *   - head->prev  = last node  (O(1) access to tail!)
 *   - lastNode->next = head
 * When the list is empty, head is NULL.
 * When there's one node, head->next = head->prev = head (points to itself).
 */
struct Node* head = NULL;

// Function prototypes
void createList();
void traverseForward();
void traverseBackward();
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

/*
 * Helper: Allocates a new node on the heap.
 * Both next and prev are set to NULL initially.
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/*
 * Creates the CDLL from scratch by asking the user for n values.
 *
 * Building follows this pattern:
 *   - First node: both next AND prev point to ITSELF (single-node circle).
 *   - Each subsequent node is inserted at the end:
 *       1. newNode->next = head         (new node's forward points to head)
 *       2. newNode->prev = tail         (new node's backward points to old tail)
 *       3. tail->next = newNode         (old tail's forward points to new node)
 *       4. head->prev = newNode         (head's backward points to new node)
 *     The new node is now the tail.
 *
 *  The 4-pointer update is the hallmark of CDLL operations.
 *  Compare:
 *    SLL: 1 pointer update
 *    CLL: 2 pointer updates (forward link + circle)
 *    DLL: 2 pointer updates (forward + backward)
 *    CDLL: 4 pointer updates (forward + backward + both ends of circle)
 */
void createList() {
    int n, value;
    struct Node* tail;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }

    // Free any existing list
    if (head != NULL) {
        struct Node* temp = head;
        head->prev->next = NULL;    // break the circle
        while (temp != NULL) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
        head = NULL;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;

        if (head == NULL) {
            // First node — points to itself in both directions
            head = newNode;
            newNode->next = head;   // circle forward
            newNode->prev = head;   // circle backward
            tail = head;
        } else {
            // Insert at end (4 pointer updates)
            newNode->next = head;       // new node's forward → head
            newNode->prev = tail;       // new node's backward → old tail
            tail->next = newNode;       // old tail's forward → new node
            head->prev = newNode;       // head's backward → new node (new tail)
            tail = newNode;             // tail tracker moves to new node
        }
    }
    printf("\nCircular doubly linked list created successfully!\n");
}

/*
 * Traverses forward from HEAD, printing each value.
 *
 * Uses do-while because the list is circular (temp starts at head,
 * and we stop when we return to head).
 *
 * head->prev gives us the last node — we can verify the circle is intact.
 */
void traverseForward() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    struct Node* temp = head;
    printf("\nForward: ... <-> ");
    do {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != head) {
            printf(" <-> ");
        }
    } while (temp != head);
    printf(" <-> ... (circular, back to head: %d)\n", head->data);
}

/*
 * Traverses backward from the LAST node to head.
 *
 * The last node is simply head->prev — this O(1) access is a key
 * advantage of CDLL over other linked list types.
 *
 * We walk backward using temp->prev and stop when we return to the last node.
 */
void traverseBackward() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    struct Node* last = head->prev;     // O(1) access to last node!
    struct Node* temp = last;
    printf("\nBackward: ... <-> ");
    do {
        printf("%d", temp->data);
        temp = temp->prev;
        if (temp != last) {
            printf(" <-> ");
        }
    } while (temp != last);
    printf(" <-> ... (circular, back to tail: %d)\n", last->data);
}

/*
 * Inserts a new node at the BEGINNING of the CDLL.
 *
 * Steps:
 *   1. Get the last node: last = head->prev  (O(1) — no traversal!)
 *   2. newNode->next = head        (new node points forward to old head)
 *   3. newNode->prev = last        (new node points backward to last node)
 *   4. last->next = newNode        (last node points forward to new node)
 *   5. head->prev = newNode        (old head points backward to new node)
 *   6. head = newNode              (update head to new node)
 *
 * This is O(1) — no traversal needed!
 * Compare: in a circular SLL, insert at beginning is O(n) because you
 * need to FIND the last node. In CDLL, last = head->prev is instant.
 */
void insertAtBeginning() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);

    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;

    if (head == NULL) {
        // Empty list — new node points to itself in both directions
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
    } else {
        struct Node* last = head->prev;     // O(1) access!
        newNode->next = head;               // new node → old head
        newNode->prev = last;               // new node ← last
        last->next = newNode;               // last → new node
        head->prev = newNode;               // old head ← new node
        head = newNode;                     // update head
    }
    printf("\nNode inserted at the beginning successfully!\n");
}

/*
 * Inserts a new node at the END of the CDLL.
 *
 * Steps (very similar to insertAtBeginning, without updating head):
 *   1. Get the last node: last = head->prev
 *   2. newNode->next = head        (new node points forward to head)
 *   3. newNode->prev = last        (new node points backward to old last)
 *   4. last->next = newNode        (old last points forward to new node)
 *   5. head->prev = newNode        (head points backward to new node)
 *
 * The new node becomes head->prev (the new last node).
 *
 * O(1) — no traversal needed! This is a major advantage of CDLL.
 * In SLL/CLL, insert at end is O(n). In CDLL, it's O(1).
 */
void insertAtEnd() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);

    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
    } else {
        struct Node* last = head->prev;
        newNode->next = head;           // new node → head (completes circle)
        newNode->prev = last;           // new node ← old last
        last->next = newNode;           // old last → new node
        head->prev = newNode;           // head's prev = new node (new tail)
    }
    printf("\nNode inserted at the end successfully!\n");
}

/*
 * Inserts a new node at a specific 1-based position.
 *
 * Position 1 = insertAtBeginning.
 * Otherwise, walk to node at position (p-1) and splice in.
 *
 * Splicing requires 4 pointer updates:
 *   1. newNode->next = temp->next
 *   2. newNode->prev = temp
 *   3. temp->next->prev = newNode
 *   4. temp->next = newNode
 */
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
        // Insert at beginning
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
        } else {
            struct Node* last = head->prev;
            newNode->next = head;
            newNode->prev = last;
            last->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    } else {
        if (head == NULL) {
            printf("\nPosition out of range!\n");
            free(newNode);
            return;
        }

        struct Node* temp = head;
        // Walk to node at position (p-1)
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
            if (temp == head) {
                // We've looped around — position is out of range
                printf("\nPosition out of range!\n");
                free(newNode);
                return;
            }
        }

        // Splice in the new node (4 pointer updates)
        newNode->next = temp->next;         // 1. new → next node
        newNode->prev = temp;               // 2. new ← current node
        temp->next->prev = newNode;         // 3. next node ← new
        temp->next = newNode;               // 4. current → new
    }
    printf("\nNode inserted at position %d successfully!\n", position);
}

/*
 * Deletes the FIRST node of the CDLL.
 *
 * Steps:
 *   1. If only one node: free it, head = NULL.
 *   2. Otherwise:
 *      a. last = head->prev
 *      b. Save head in temp.
 *      c. head = head->next          (move head forward)
 *      d. head->prev = last          (new head's prev = last node)
 *      e. last->next = head          (last node's next = new head)
 *      f. Free temp.
 *
 * O(1) — head->prev gives instant access to the last node.
 */
void deleteAtBeginning() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    struct Node* temp = head;

    if (head->next == head) {
        // Only one node — list becomes empty
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node* last = head->prev;     // O(1) access
    head = head->next;                  // move head forward
    head->prev = last;                  // new head's backward → last
    last->next = head;                  // last's forward → new head

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Deletes the LAST node of the CDLL.
 *
 * The last node is head->prev — O(1) access, no traversal needed!
 * This is a HUGE advantage over SLL and CLL where deleteAtEnd is O(n).
 *
 * Steps:
 *   1. last = head->prev           (the node to delete)
 *   2. secondLast = last->prev     (will become the new last)
 *   3. secondLast->next = head     (skip over the old last)
 *   4. head->prev = secondLast     (head's backward = new last)
 *   5. Free last.
 *
 * O(1) — no traversal!
 */
void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    if (head->next == head) {
        // Only one node
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node* last = head->prev;         // the node to delete
    struct Node* secondLast = last->prev;   // will be the new tail

    secondLast->next = head;                // skip over last
    head->prev = secondLast;                // head's backward = new tail

    printf("\nDeleted node with value: %d\n", last->data);
    free(last);
}

/*
 * Deletes the node at a specific 1-based position.
 *
 * We walk directly to the target node (not the one before it) because
 * in a DLL/CDLL, we can access both neighbours:
 *   - temp->prev->next = temp->next   (previous node skips over temp)
 *   - temp->next->prev = temp->prev   (next node skips over temp)
 *
 * Position 1 = deleteAtBeginning.
 */
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
        deleteAtBeginning();
        return;
    }

    struct Node* temp = head;
    // Walk to the target position
    for (int i = 1; i < position; i++) {
        temp = temp->next;
        if (temp == head) {
            printf("\nPosition out of range!\n");
            return;
        }
    }

    // Unlink temp from both directions
    temp->prev->next = temp->next;      // previous node skips over temp
    temp->next->prev = temp->prev;      // next node skips over temp

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Deletes the FIRST node that contains the given value.
 *
 * Walk forward from head. When we find the node:
 *   - If it's the only node: free it, head = NULL.
 *   - If it's the head: call deleteAtBeginning logic.
 *   - Otherwise: unlink using temp->prev and temp->next.
 */
void deleteByValue() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);

    struct Node* temp = head;

    // Search for the node
    do {
        if (temp->data == value) {
            // Found the node to delete

            if (temp->next == temp) {
                // Only one node in the list
                printf("\nDeleted node with value: %d\n", temp->data);
                free(temp);
                head = NULL;
                return;
            }

            // Unlink temp
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            // If we're deleting the head, update head
            if (temp == head) {
                head = temp->next;
            }

            printf("\nDeleted node with value: %d\n", temp->data);
            free(temp);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    printf("\nValue %d not found in the list!\n", value);
}

/*
 * Searches for a value and reports its 1-based position.
 * Uses do-while for circular traversal.
 */
void searchElement() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    int value, position = 1;
    printf("\nEnter the value to search: ");
    scanf("%d", &value);

    struct Node* temp = head;
    do {
        if (temp->data == value) {
            printf("\nValue %d found at position %d\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    } while (temp != head);

    printf("\nValue %d not found in the list!\n", value);
}

/*
 * Counts the total number of nodes.
 */
void countNodes() {
    if (head == NULL) {
        printf("\nList is empty! Node count: 0\n");
        return;
    }

    int count = 0;
    struct Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    printf("\nTotal number of nodes: %d\n", count);
}

/*
 * Reverses the CDLL by swapping prev and next pointers on every node.
 *
 * Same concept as DLL reversal — swap prev and next for each node.
 * After all swaps, the circle still exists but in the opposite direction.
 *
 * We use do-while because it's circular. After processing all nodes,
 * head should point to what was the LAST node (now the first).
 * Since head->prev was the last node, and after swapping head->prev
 * becomes head->next, the new head is the old head->prev... which we
 * can just access as head->next after the swap completes on head.
 *
 * O(n) time, O(1) space.
 */
void reverseList() {
    if (head == NULL || head->next == head) {
        printf("\nList is empty or has only one node!\n");
        return;
    }

    struct Node* current = head;
    struct Node* temp;

    // Swap prev and next for every node
    do {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;        // move forward (prev is now the old next)
    } while (current != head);

    // After swapping, head should move to what was the last node.
    // head->next now points to the old second-to-last node (due to swap),
    // and head->prev points to what was head->next (old second node).
    // The new head is head->next (which was the old tail after swap).
    head = head->next;

    printf("\nList reversed successfully!\n");
}

/*
 * Sorts the list using BUBBLE SORT (data swap).
 * Same logic as other linked list sorts — swap data, not nodes.
 *
 * The inner loop runs from head until it reaches lptr (sorted boundary).
 * lptr shrinks toward head after each pass.
 */
void sortList() {
    if (head == NULL || head->next == head) {
        printf("\nList is empty or has only one node!\n");
        return;
    }

    int swapped;
    struct Node *ptr1, *lptr = head;    // lptr = sorted boundary

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
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

// Display menu
void displayMenu() {
    printf("\n=================================================");
    printf("\n  CIRCULAR DOUBLY LINKED LIST OPERATIONS MENU");
    printf("\n=================================================");
    printf("\n1.  Create List");
    printf("\n2.  Traverse Forward");
    printf("\n3.  Traverse Backward");
    printf("\n4.  Insert at Beginning");
    printf("\n5.  Insert at End");
    printf("\n6.  Insert at Position");
    printf("\n7.  Delete from Beginning");
    printf("\n8.  Delete from End");
    printf("\n9.  Delete from Position");
    printf("\n10. Delete by Value");
    printf("\n11. Search Element");
    printf("\n12. Count Nodes");
    printf("\n13. Reverse List");
    printf("\n14. Sort List");
    printf("\n15. Exit");
    printf("\n=================================================");
    printf("\nEnter your choice: ");
}

// ========================  MAIN  ========================
int main() {
    int choice;

    printf("\n*** CIRCULAR DOUBLY LINKED LIST OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:  createList();        break;
            case 2:  traverseForward();   break;
            case 3:  traverseBackward();  break;
            case 4:  insertAtBeginning(); break;
            case 5:  insertAtEnd();       break;
            case 6:  insertAtPosition();  break;
            case 7:  deleteAtBeginning(); break;
            case 8:  deleteAtEnd();       break;
            case 9:  deleteAtPosition();  break;
            case 10: deleteByValue();     break;
            case 11: searchElement();     break;
            case 12: countNodes();        break;
            case 13: reverseList();       break;
            case 14: sortList();          break;
            case 15:
                printf("\nExiting program. Goodbye!\n");
                // Free all nodes — break the circle first
                if (head != NULL) {
                    struct Node* last = head->prev;
                    last->next = NULL;      // break the circle
                    while (head != NULL) {
                        struct Node* temp = head;
                        head = head->next;
                        free(temp);
                    }
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
