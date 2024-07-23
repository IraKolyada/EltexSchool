/*
 * program 4.c - subscriber directory
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE_BOOK 100
#define SIZE_EL 10
#define LEN_EL "10" /*LEN_EL  == SIZE_EL*/

/*
 * Structure for storing subscriber information
 */
struct abonent{
	char name[SIZE_EL];
	char second_name[SIZE_EL];
	char tel[SIZE_EL];
	int do_it;/*flag: 0 - write doesn't exist,
				1 - write exist*/
};

/*
 * function to detect non-digits in a phone number
 */
int check_tel(struct abonent *ptr){
	for(int i = 0; i < SIZE_EL; i++){
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

/*
 * function fills the subscriber's inform
 * into the location passed by the pointer
 */
int add_abonent(struct abonent *ptr){
	printf("Enter name: ");
	scanf("%"LEN_EL"s",ptr->name);

	printf("Enter second name: ");
	scanf("%"LEN_EL"s",ptr->second_name);

	printf("Enter telephone: ");
	do{
		scanf("%"LEN_EL"s",ptr->tel);
	}while(!check_tel(ptr));/* phone check */

	ptr->do_it = 1;/* write exist */
	return 0;
}

/*
 * function delete the subscrider's inform
 *
 * if subscriber's name and second name in the struct(*ptr)
 *  indentical name(*ptr_del_name) and second name(*ptr_del_second_name) 
 *  to deletes -inform from struct is replaced wiht zeros
 *  and return 1
 *
 * else return 0 
 */
int delete_abonent (char *ptr_del_name,char *ptr_del_second_name,struct abonent *ptr){
	/*
	 * strncmp() returns zero if the string are equal
	 */
	if ((!strncmp(ptr_del_name,ptr->name,SIZE_EL)) && 
	(!strncmp(ptr_del_second_name,ptr->second_name,SIZE_EL))){
		memset(ptr->name,'0',SIZE_EL);
		memset(ptr->second_name,'0',SIZE_EL);
		memset(ptr->tel,'0',SIZE_EL);
		ptr->do_it = 0; /* write doesn't exist*/
		printf("\nAbonent deleted.\n");
		return 1;
	}
	return 0;
}

/*
 * function found  the subscrider's inform
 *
 * if subscriber's name or second name in the struct(*ptr)
 *  indentical name(*ptr_found_name) to find 
 *  -inform from struct is printed
 *  and reurn 1
 *
 * else return 0 
 */
int found_abonent(char *ptr_found_name,struct abonent *ptr){
	/*
	 * strncmp() returns zero if the string are equal
	 */
	if ((!strncmp(ptr_found_name,ptr->name,SIZE_EL)) || 
	(!strncmp(ptr_found_name,ptr->second_name,SIZE_EL))){
		/*printf("\nAbonent founded:\n");*/
		printf("\n%."LEN_EL"s\n",ptr->name);
		printf("%."LEN_EL"s\n",ptr->second_name);
		printf("%."LEN_EL"s\n\n",ptr->tel);
		return 1;
	}
/*	else */
	/*	printf("\nNot found!\n");*/	
	return 0;
}

/*
 * function is printed inform from struct if write is exist
 * else print ---
 */
int print_book(struct abonent *ptr){
	if(ptr->do_it){
		printf("\n%."LEN_EL"s\n",ptr->name);
		printf("%."LEN_EL"s\n",ptr->second_name);
		printf("%."LEN_EL"s\n\n",ptr->tel);
	}
	else 
		printf("---\n");
	return 0;
}

int main(void){
	struct abonent book[SIZE_BOOK] = {0};
	struct abonent *add_ptr,*ptr_book;
	add_ptr = &book[0];
	ptr_book = &book[0];
	char abonent_found[SIZE_EL] = {0};/*subscribe's name for found or delete*/
	char *ptr_found = &abonent_found[0];
	char abonent_found_two[SIZE_EL] = {0};/*subscribe's second name for delete*/
	char *ptr_found_two = &abonent_found_two[0];
	int on = 0; /* switch states */
	int flag = 1; /* while states */
	int not_found = 0; /*flag for finding the desired subscriber*/
	int fullness_book = 0;
	
	while(flag){
		printf("\nCommand:\n");
		scanf("%d",&on);

		switch(on){
			case 1:
				fullness_book = 0;
				/*
				 * count the book's fullness
				 */
				for(int i = 0; i < SIZE_BOOK; i++)
					fullness_book +=book[i].do_it;

				if(fullness_book == SIZE_BOOK)
					printf("NOT SPASE!");
				else{
					for(int i = 0; i < SIZE_BOOK; i++){
						/*
						 * remember the pointer to 
						 * the first free space
						 */
						if(!book[i].do_it){
							add_ptr = &book[i];
							break;
						}
					}
					add_abonent(add_ptr);
				}
				break;
			case 2:
				printf("Abonent name to delete: ");
				scanf("%"LEN_EL"s",ptr_found);
				printf("Abonent second name to delete: ");
				scanf("%"LEN_EL"s",ptr_found_two);
				not_found = 0;
				for(int i = 0; i < SIZE_BOOK; i++){
					ptr_book = &book[i];
					/*
					 * if it finds equality 'not_found' !=0
					 */
					not_found += delete_abonent(ptr_found,
							ptr_found_two,ptr_book);
				}	
				if(!not_found){
					printf("NOT FOUND!!!");
				}
				break;
			case 3:
				printf("Abonent name to find: ");
				scanf("%"LEN_EL"s",ptr_found);
				not_found = 0;
				printf("Rez:\n");
				for( int i = 0; i < SIZE_BOOK; i++){
					ptr_book = &book[i];
					/*
					 * if it finds equality 'not_found' !=0
					 */
					not_found += found_abonent(ptr_found,ptr_book);
				}
				if(!not_found){
					printf("NOT FOUND!!");
				}
				printf("\n");
				break;
			case 4:
				printf(" Abonent book:\n");
				for(int i = 0; i < SIZE_BOOK;i++){
					ptr_book = &book[i];
					print_book(ptr_book);
				}
				break;
			case 5:
				flag = 0;
				break;
			default:
				printf("\nCommand not found!\n");
				break;
		}
	}
	return 0;
}

