#include "StudentSystemManager.h"

int main() {
	//create head point information
	Node* head = malloc(sizeof(Node));
	head->next = NULL;
	loadStudent(head);

	while (1) {

		welcome();

		char c = _getch();

		switch (c)
		{
		case '1':  //input student information
			inputStudent(head);
			break;
		case '2':  //print student information
			printStudent(head);
			break;
		case '3':  //sum of students
			countStudent(head);
			break;
		case '4':  //search student information
			findStudent(head);
			break;
		case '5':  //modify student information
			modifyStudent(head);
			break;
		case '6':  //delete student information
			deleteStudent(head);
			break;
		case '7':  //sort by GPA
			sortStudent(head);
			break;
		case '8':  //exit the system
			system("cls");
			printf("Bye Bye!\n");
			exit(0);
			break;
		default:
			printf("please enter again\n");
			break;
		}
	}

	return 0;
}

void welcome() {
	printf("*********************************\n");
	printf("*\tstudent GPA management system\t*\n");
	printf("*********************************\n");
	printf("*\tplease slect\t\t*\n");
	printf("*********************************\n");
	printf("*\t1.input student information\t\t*\n");
	printf("*\t2.print student information\t\t*\n");
	printf("*\t3.sum of students\t\t*\n");
	printf("*\t4.search student information\t\t*\n");
	printf("*\t5.modify student information\t\t*\n");
	printf("*\t6.delete student information\t\t*\n");
	printf("*\t7.sort by GPA\t\t*\n");
	printf("*\t8.exit system\t\t*\n");
	printf("*********************************\n");
}

void inputStudent(Node* head) {

	Node* fresh = malloc(sizeof(Node));
	fresh->next = NULL;
	printf("please input student's student number, name, GPA ");
	scanf("%d%s%d", &fresh->student.stuNum, fresh->student.name, &fresh->student.score);

	Node* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	//insert student to tail
	move->next = fresh;

	saveStudent(head);
	//pause system
	system("pause");
	//clear console
	system("cls");
}

void printStudent(Node* head) {
	Node* move = head->next;
	while (move != NULL) {
		printf("student number:%d student's name:%s GPA:%d\n", move->student.stuNum, move->student.name, move->student.score);
		move = move->next;
	}
	//pause system
	system("pause");
	//clear console
	system("cls");
}

void countStudent(Node* head) {
	int count = 0;
	Node* move = head->next;
	while (move != NULL) {
		count++;
		move = move->next;
	}
	printf("sum of students :%d\n", count);
	//pause system
	system("pause");
	//clear console
	system("cls");
}

void findStudent(Node* head) {
	printf("please enter the student's number who you are looking for: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL) {
		if (stuNum == move->student.stuNum) {
			printf("student number: %d student's name:%s GPA:%d\n", move->student.stuNum, move->student.name, move->student.score);
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("no such student\n");
	
	system("pause");
	system("cls");
}

void saveStudent(Node* head) {
	FILE* file = fopen("./stu.info", "w");
	Node* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->student, sizeof(Student), 1, file) != 1) {
			printf("save%serrors\n");
			return;
		}
		move = move->next;
	}
	fclose(file);
}

void loadStudent(Node* head) {
	FILE* file = fopen("./stu.info", "r");
	if (!file) {
		printf("can not find student,skip reading\n");
		return;
	}
	Node* fresh = malloc(sizeof(Node));
	fresh->next = NULL;
	Node* move = head;
	while (fread(&fresh->student, sizeof(Student), 1, file) == 1) {
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(Student));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	printf("read successful\n");
}

void modifyStudent(Node* head) {
	printf("please enter the student number which need to be modified: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL) {
		if (move->student.stuNum == stuNum) {
			printf("please enter student's name, GPA\n");
			scanf("%s%d", move->student.name, &move->student.score);
			saveStudent(head);
			printf("modify successful\n");
			
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("can not find the student\n");
	system("pause");
	system("cls");
}

void deleteStudent(Node* head) {
	printf("please enter the student number which need to be deleted ");
	int stuNum = 0;
	scanf("%d", &stuNum);

	Node* move = head;
	while (move->next != NULL) {
		
		if (move->next->student.stuNum == stuNum) {
			Node* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveStudent(head);
			printf("delete successful\n");
			system("pause");
			system("cls");
			return;
		}

		move = move->next;
	}
	printf("can not find the student\n");
	
	system("pause");
	system("cls");
}

void sortStudent(Node* head) {
	Node* save = NULL;
	Node* move = NULL;
	for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
		for (move = head->next; move->next != save; move = move->next) {
			if (move->student.score > move->next->student.score) {
				Student temp = move->student;
				move->student = move->next->student;
				move->next->student = temp;
			}
		}
		save = move;
	}
	printStudent(head);
}