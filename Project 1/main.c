/*in C, Create a struct to represent users in a game.What is required of
each person is their unique username, their level (levels can range from
1 – 60), and their faction (red, blue or green).*/

// Hamna Hamna - PROG72370 - Winter2024
// 2/12/2024

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queues.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("%s <number_of_users>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int numUsers = atoi(argv[1]);
	Queue* queue = createQueue();
	if (enqueueRandomUsers(queue, numUsers) != 0) {
		printf("Cannot enqueue users.\n");
		freeQueue(queue);
		return EXIT_FAILURE;
	}
	while (!isEmpty(queue)) {
		User user = dequeue(queue);
		printf("Username: %s, Level: %d, Faction: %s\n", user.username, user.level, user.faction);
	}
	freeQueue(queue);

	return EXIT_SUCCESS;
}