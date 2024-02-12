// Functions implementation

// Hamna Hamna - PROG72370 - Winter2024
// 2/12/2024

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queues.h"

// Function to create a queue
Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->head == NULL;
}

// Function to push a node into the queue
void enqueue(Queue* queue, User user)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->user = user;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->head = newNode;
    }
    else {
        queue->tail->next = newNode;
    }
    queue->tail = newNode;
}

// Function to pop a node from queue
User dequeue(Queue* queue)
{
    if (isEmpty(queue)) {
        printf("Queue is empty.\n"); // Checking to see if queue is empty
        exit(EXIT_FAILURE); // if empty
    }
    Node* temp = queue->head;
    User user = temp->user;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp); // free memory
    return user;
}

void freeQueue(Queue* queue)
{
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

void generateRandomUsername(char* username)
{
    const char alphabetset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    for (int i = 0; i < 10; ++i) {
        username[i] = alphabetset[rand() % (sizeof(alphabetset) - 1)];
    }
    username[10] = '\0';
}

int enqueueRandomUsers(Queue* queue, int numUsers)
{
    if (numUsers <= 0) {
        printf("Invalid number of users.\n");
        return 1;
    }
    for (int i = 0; i < numUsers; ++i) {
        User newUser;
        generateRandomUsername(newUser.username);
        newUser.level = rand() % 60 + 1;
        const char* factions[] = { "red", "blue", "green" };
        strcpy(newUser.faction, factions[rand() % 3]);
        enqueue(queue, newUser);
    }
    return 0;
}

void writeUsersToFile(Queue* queue, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    while (!isEmpty(queue)) {
        User user = dequeue(queue);
        fprintf(file, "%s %d %s\n", user.username, user.level, user.faction);
    }
    fclose(file);
}

Queue* readUsersFromFile(const char* filename) {
    Queue* queue = createQueue();
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return queue;
    }
    char username[11];
    int level;
    char faction[7];
    while (fscanf(file, "%10s %d %6s", username, &level, faction) == 3) {
        User user;
        strcpy(user.username, username);
        user.level = level;
        strcpy(user.faction, faction);
        enqueue(queue, user);
    }
    fclose(file);
    return queue;
}


void printUsers(Queue* queue)
{
    while (!isEmpty(queue)) {
        User user = dequeue(queue);
        printf("Username: %s, Level: %d, Faction: %s\n", user.username, user.level, user.faction);
    }
}