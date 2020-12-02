#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "occurrences.h"

void insertOccurrence(OccurrenceArray *occurrences, char c) {
	int a = 0, b = occurrences->size - 1;

	while (a < b) {
		int mid = (a + b) / 2;

		if (c == occurrences->array[mid].c) {
			a = mid;
			b = mid;
		} else if (c > occurrences->array[mid].c)
			a = mid + 1;
		else b = mid;
	}

	if (occurrences->array == NULL || occurrences->array[a].c != c) {
		++occurrences->size;
		if (occurrences->array == NULL)
			occurrences->array = (Occurrence *) malloc(sizeof(Occurrence) * occurrences->size);
		else occurrences->array = (Occurrence *) realloc(occurrences->array, sizeof(Occurrence) * occurrences->size);

		for (b = occurrences->size - 1; b > a; --b)
			occurrences->array[b] = occurrences->array[b - 1];

		occurrences->array[a].c = c;
		occurrences->array[a].count = 1;
	} else ++occurrences->array[a].count;
}

void sortOccurrences(OccurrenceArray occurrences) {
	for (int i = 0; i < occurrences.size - 1; ++i) {
		int max = i;
		for (int j = i + 1; j < occurrences.size; ++j)
			if (occurrences.array[j].count > occurrences.array[max].count)
				max = j;

		if (max != i) {
			Occurrence tmp = occurrences.array[i];
			occurrences.array[i] = occurrences.array[max];
			occurrences.array[max] = tmp;
		}
	}
}

OccurrenceArray getOccurrences(char *string) {
	OccurrenceArray occurrences = { 0, NULL };

	for (int i = 0; i < strlen(string); ++i)
		insertOccurrence(&occurrences, string[i]);

	sortOccurrences(occurrences);
	return occurrences;
}

void displayOccurrences(OccurrenceArray occurrences) {
	for (int i = 0; i < occurrences.size; ++i) {
		if (i != 0) printf(" -> ");
		printf("%c (%lu)", occurrences.array[i].c, occurrences.array[i].count);
	}
}

Occurrence popSmallestOccurrence(OccurrenceArray *occurrences) {
	if (occurrences->size == 0) {
		Occurrence smallest = { '\0', 0 };
		return smallest;
	}

	return occurrences->array[--occurrences->size];
}


void insertOccurrenceLL(OccurrenceLL **occurrences, char c) {
	while (*occurrences != NULL && (*occurrences)->c != c)
		occurrences = &(*occurrences)->next;

	if (*occurrences == NULL) {
		OccurrenceLL *new = (OccurrenceLL *) malloc(sizeof(OccurrenceLL));
		new->c = c;
		new->count = 1;
		new->next = *occurrences;
		*occurrences = new;
	} else {
		++(*occurrences)->count;
	}
}

OccurrenceLL *getOccurrencesLL(char *string) {
	OccurrenceLL *occurrences = NULL;

	for (int i = 0; i < strlen(string); ++i)
		insertOccurrenceLL(&occurrences, string[i]);

	return occurrences;
}

void displayOccurrencesLL(OccurrenceLL *occurrences) {
	if (occurrences == NULL) return;

	printf("%c (%lu)", occurrences->c, occurrences->count);

	while (occurrences->next != NULL) {
		occurrences = occurrences->next;
		printf(" -> %c (%lu)", occurrences->c, occurrences->count);
	}
}

OccurrenceLL *popSmallestOccurrenceLL(OccurrenceLL **occurrences) {
	if (*occurrences == NULL) return NULL;

	OccurrenceLL **current = occurrences;

	while ((*occurrences)->next != NULL) {
		occurrences = &(*occurrences)->next;

		if ((*occurrences)->count < (*current)->count)
			current = occurrences;
	}

	OccurrenceLL *smallest = *current;
	*current = (*current)->next;
	smallest->next = NULL;
	return smallest;
}
