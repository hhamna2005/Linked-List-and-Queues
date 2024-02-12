#pragma once
// Header file

#ifndef QUEUES_H
#define QUEUES_H

// Struct for variables
typedef struct {
	char username[11];
	int level;
	char faction[6];
}User;

// Struct for defining node
typedef struct {
	User user;
	struct Node* next;
}Node;

typedef struct {
	Node* head;
	Node* tail;
}Queue;

Queue* createQueue();
int isEmpty(Queue* queue);
void enqueue(Queue*, User user);
User dequeue(Queue* queue);
void freeQueue(Queue* queue);
void generateRandomUsername(char* username);
int enqueueRandomUsers(Queue* queue, int numUsers);
void writeUsersToFile(Queue* queue, const char* filename);
Queue* readUsersFromFile(const char* filename);
void printUsers(Queue* queue);

#endif
