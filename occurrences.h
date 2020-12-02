#ifndef __H_OCCURRENCES
#define __H_OCCURRENCES

struct OccurrenceLL {
	char c;
	long unsigned int count;
	struct OccurrenceLL *next;
};
typedef struct OccurrenceLL OccurrenceLL;

struct Occurrence {
	char c;
	long unsigned int count;
};
typedef struct Occurrence Occurrence;

struct OccurrenceArray {
	long unsigned int size;
	Occurrence *array;
};
typedef struct OccurrenceArray OccurrenceArray;

void insertOccurrence(OccurrenceArray *occurrences, char c);
OccurrenceArray getOccurrences(char *string);
void sortOccurrences(OccurrenceArray occurrences);
void displayOccurrences(OccurrenceArray occurrences);
Occurrence popSmallestOccurrence(OccurrenceArray *occurrences);

void insertOccurrenceLL(OccurrenceLL **occurrences, char c);
OccurrenceLL *getOccurrencesLL(char *string);
void displayOccurrencesLL(OccurrenceLL *occurrences);
OccurrenceLL *popSmallestOccurrenceLL(OccurrenceLL **occurrences);

#endif
