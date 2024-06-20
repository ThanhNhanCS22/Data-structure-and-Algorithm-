#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next, *prev;
};

struct List {
    struct Node *head, *tail;
};

void add(struct Node **head, int newData) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = *head;
    newNode->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void append(struct Node **head, int newData) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    struct Node *last = *head;
    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    newNode->prev = last;
}

void printList(struct Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void insert(struct List *L, struct Node *x) {
    x->next = L->head;
    x->prev = NULL;

    if (L->head != NULL) {
        L->head->prev = x;
    }

    L->head = x;

    // If the list was empty, update the tail as well
    if (L->tail == NULL) {
        L->tail = x;
    }
}

int main() {
    struct List myList;
    myList.head = NULL;
    myList.tail = NULL;

    add(&myList.head, 1);
    add(&myList.head, 2);
    add(&myList.head, 3);

    printf("Linked List (Added to the Beginning): ");
    printList(myList.head);

    append(&myList.head, 4);
    append(&myList.head, 5);

    printf("Linked List (Added to the End): ");
    printList(myList.head);

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = 0;

    insert(&myList, newNode);

    printf("Linked List (After Inserting at the Beginning): ");
    printList(myList.head);

    freeList(myList.head);

    return 0;
}
