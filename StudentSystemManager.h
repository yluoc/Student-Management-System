#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//student information
typedef struct _Student
{
	int stuNum;
	char name[20];
	int score;
}Student;

//end point information
typedef struct _Node
{
	Student student;
	struct _Node* next;
}Node;

void welcome();

void inputStudent(Node* head);

void printStudent(Node* head);

void countStudent(Node* head);

void findStudent(Node* head);

void saveStudent(Node* head);

void loadStudent(Node* head);

void modifyStudent(Node* head);

void deleteStudent(Node* head);

void sortStudent(Node* head);