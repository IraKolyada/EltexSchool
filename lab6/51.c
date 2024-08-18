#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct abonent{
	int len_name;
	char *name;
	int len_second;
	char *second_name;
	int len_tel;
	char *tel;
};

/*
 * check_tel - function to detect non-digits in a phone number
 * @ptr: pointer subscriber information
 * @size: size string
 */
int check_tel(struct abonent *ptr,int size)
{
	for(int i = 0; i < size; i++){
		/*
		 * isdigit() returns zero if 
		 * the variable isn't a digit 
		 */
		if(!isdigit(ptr->tel[i])){
			printf("Only numbers, please re-enter.\n");
			return 0;
		}
	}
	return 1;
}

/**
 * check_spase - checks whether subscriber information is
 * @ptr:pointer subscriber information
 * 
 * return 0 if subscriber information isn't
 * return 1 if subscriber information is
 */

int check_spase(struct abonent *ptr)
{
	if((ptr->name[0] == '\0')&&(ptr->second_name[0] == '\0')&&(ptr->tel[0] == '\0')){
		printf("Subscriber information isn't filled in, please re-enter\n");
		return 0;
	}
	return 1;
}

/**
 * free_abonent - free memory allocated wihin a structure
 * @ptr:pointer subscriber information
 */
void free_abonent(struct abonent *ptr)
{
	if(ptr){
		if(ptr->name){
			if(ptr->tel){
				free(ptr->name);
				free(ptr->second_name);
				free(ptr->tel);
				ptr->name = NULL;
				ptr->second_name = NULL;
				ptr->tel = NULL;
			}
		}
	}
}

/**
 * get_string - creates a string of any length and remembers its lenght
 * @len:pointer lenght of string
 */
char *get_string(int *len)
{
	*len = 0;
	int capacity = 1;
	char *s = (char*) malloc(sizeof(char));
	char c = getchar();

	if(c == '\n')
		c = getchar();

	while(c != '\n'){
		s[(*len)++] = c;
		if(*len >= capacity){
			capacity *= 2;
			s = (char*) realloc(s, capacity * sizeof(char));
		}
		c = getchar();
	}

	s[*len] = '\0';
	return s;
}

/**
 * add - increases the subscrider book by one and offers to fill out 
 * information about the new subscriber
 * @size: subscriber book size
 * @ptr_book: subscrider book
 */
struct abonent *add(int size, struct abonent *ptr_book)
{
	if(size == 0){
		ptr_book = (struct abonent*)malloc(sizeof(struct abonent));
	}
	else{
		ptr_book = (struct abonent*)realloc(ptr_book,(size+1) * 
				sizeof(struct abonent));
	}

	do{
		printf("\nEnter name: \n");
		ptr_book[size].name = get_string(&ptr_book[size].len_name);

		printf("\nEnter second name: \n");
		ptr_book[size].second_name = get_string(&ptr_book[size].len_second);

		printf("\nEnter telephone: \n");
		ptr_book[size].len_tel = 0;
		do{
			ptr_book[size].tel = get_string(&ptr_book[size].len_tel);
		}while(!check_tel(&ptr_book[size], ptr_book[size].len_tel)); /* phone check */

	}while(!check_spase(&ptr_book[size])); /* information subscriber check*/

	return ptr_book;
}

/**
 * delete - removes a subscriber from the book
 * @size: subscriber book size
 * @ptr_book: subscrider book
 *
 * if the lenght of the name to be deleted isw equal to the book item,
 * compare the contents of the lines, if they are equal,
 * change the menu item to the last item and reduce the book lenght by one,
 * first clear the inform inside the structure
 */
struct abonent *delete(int size, struct abonent *ptr_book)
{
	char *del_name;
	char *del_second;
	int len_name;
	int len_second;
	printf("\nName to delete:\n");
	del_name = get_string(&len_name);
	printf("\nSecond name to delete:\n");
	del_second = get_string(&len_second);

	for(int i = 0;i < size;i++){
		/*if len of the existing str and desired str are the same go next level*/
		if((len_name == ptr_book[i].len_name) && (len_second == ptr_book[i].len_second)){
			/*if the contents of the existing str and desired str are the same go next level*/
			if((!strncmp(del_name, ptr_book[i].name, len_name)) && 
				(!strncmp(del_second, ptr_book[i].second_name, len_second))){

				/*Replacing the name with the name of the last abonent from the book*/
				ptr_book[i].len_name = ptr_book[size - 1].len_name;
				if(ptr_book[size - 1].len_name != 0)
					strncpy(ptr_book[i].name, ptr_book[size - 1].name, ptr_book[size - 1].len_name);
				else
					ptr_book[i].name[0] = '\0';

				/*Replacing the second name with the name of the last abonent from the book*/
				ptr_book[i].len_second = ptr_book[size - 1].len_second;
				if(ptr_book[size - 1].len_second != 0)
					strncpy(ptr_book[i].second_name, ptr_book[size - 1].second_name,ptr_book[size - 1].len_second);
				else
					ptr_book[i].second_name[0] = '\0';

				/*Replacing the tel with the name of the last abonent from the book*/
				ptr_book[i].len_tel = ptr_book[size - 1].len_tel;
				if(ptr_book[size - 1].len_tel != 0)
					strncpy(ptr_book[i].tel, ptr_book[size - 1].tel,ptr_book[size - 1].len_tel);
				else
					ptr_book[i].tel[0] = '\0';

				/*Deleting the last abonent from the book*/
				free_abonent(&(ptr_book[size - 1]));
				ptr_book = (struct abonent*)realloc(ptr_book,(size-1) * 
						sizeof(struct abonent));
				printf("\nSubscriber information delete\n");

				free(del_name);
				free(del_second);
				return ptr_book;
			}
		}
	}

	free(del_name);
	free(del_second);
	printf("\nNot found to delete");
	return ptr_book;
}

/**
 * print_book - displays inform from a book
 * @size: subscriber book size
 * @ptr_book: subscrider book
 */
int print_book(int size, struct abonent *ptr_book){
	printf("\nBOOK:\n");
	for(int i = 0; i <= size - 1; i++){
		printf("\n%s", ((ptr_book[i].name[0] == '\0') ? "-----" : ptr_book[i].name));
		printf("\n%s", ((ptr_book[i].second_name[0] == '\0') ? "-----" : ptr_book[i].second_name));
		printf("\n%s\n", ((ptr_book[i].tel[0] == '\0') ? "-----" : ptr_book[i].tel));
	}

	return 0;
}

/**
 * found - dysplays the found inform on the screen
 * @size: subscriber book size
 * @ptr_book: subscrider book
 *
 * if the text entered for search in full or "as the first letters"
 * matches the first or last name - displays inform about the subscriber
 */
int found(int size, struct abonent *ptr_book)
{
	char *found_name;
	int len_name;
	int flag_found = 0;
	printf("\nName to find:\n");
	found_name = get_string(&len_name);

	for(int i = 0;i < size;i++){
		if((!strncmp(found_name,ptr_book[i].name,len_name))||(!strncmp(found_name,ptr_book[i].second_name,len_name))){
		printf("\n%s", ((ptr_book[i].name[0] == '\0') ? "-----" : ptr_book[i].name));
		printf("\n%s", ((ptr_book[i].second_name[0] == '\0') ? "-----" : ptr_book[i].second_name));
		printf("\n%s\n", ((ptr_book[i].tel[0] == '\0') ? "-----" : ptr_book[i].tel));

		flag_found++;
		}
	}

	if(!flag_found)
		printf("\nNot found\n");

	free(found_name);
	return 0;
}

int main(void){
	struct abonent *book;
	int size = 0;
	int flag = 1;
	int on = 0;

	while(flag){
		printf("\nCommand:\n");
		scanf("%d",&on);

		switch(on){
			case 1:
				book = add(size, book);
				size++;
				break;
			case 2:
				book = delete(size, book);
				size--;
				break;
			case 3:
				found(size, book);
				break;
			case 4:
				print_book(size, book);
				break;
			case 5:
				for(int i = 0;i < size;i++){
					free_abonent(&(book[i]));
				}
				free(book);
				flag = 0;
				break;
			default:
				printf("\nCommand not found!\n");
				break;
		}
	}
	return 0;
}
