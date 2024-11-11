#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

#define LENGTH 50
#define overstock 1000
#define understock 5

	float net_transactions=0;
	int withdraw_quantity=0, deposit_quantity=0;
	float withdraw_value=0, deposit_value=0;
	char heading_line[100];
	char status[10];
    char u_name[10];
    char u_pass[10];

struct Product {
    int productId;
    char productName[LENGTH];
    unsigned int productquantity;
    float productPrice;
    char productCategory[LENGTH];
	};
	
	struct Product product;

void login(int j); //Function to check identity.
void printWelcome(void); //Function to display the initial display.
void menu(); //Function to display starting menu. 
void input_item(void); //Function to enter item into the system.
int product_check(char name[]);
int assignID(void); //Function to assign ID to products.
void display_menu(void); //Function to display the menu.
void search(void); //Funtion to search items by ID or Category.
void search_by_ID(void); //Function to search specific ID.
void search_by_category(void); //Function to search items of specific category.
void withdraw(void); //Function to withdraw items from the system.
void withdraw_by_ID(void); //Function to withdraw by Product ID.
void withdraw_by_name(void); //Function to withdraw by product name.
void Transactionshistory(void); //Function to display history of transactions.
void bill(); //Funtion to display the bill of items 

int main(void)
{
	char name[10];
	system("COLOR F1");
	printf("\n\n\t\t\t\t   *************************************\n");
	printf("\t\t\t\t   |    Log in to access the system    |\n");
	printf("\t\t\t\t   *************************************\n");
	login(1);
	menu();
}

void printWelcome(void)
{
	system("COLOR 06");
		puts("===============================================================================");
		puts(" __          __  _                                                ");
		puts(" \\ \\        / / | |                           _____       ____ _____ __  __             ");
		puts("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  |_   _|__   / ___|_   _|  \\/  |             ");
		puts("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\  \\___ \\ | | | |\\/| |              ");
		puts("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/   | | (_) |  ___) || | | |  | |               ");
		puts("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/  |____/ |_| |_|  |_|                     ");
		puts("===============================================================================");
}

void login(int j)
{
    int check=1;
    char name[10];
    char password[10];
    int i=0;
    printf("\t\t\t\t\tEnter username: ");
    fflush(stdin);
    gets(u_name);
    printf("\t\t\t\t\tEnter Password: ");

        int p=0;
    do
	{
		u_pass[p]=getch();
		if(u_pass[p]!='\r'&&u_pass[p]!='\b')
		printf("*");
	
		if(u_pass[p]=='\b')
		{	
			printf("\b \b");
			u_pass[p-1]='\0';
			p=p-2;
		}	
		p++;
	}while(u_pass[p-1]!='\r'); 
    FILE *fptr;
    fptr = fopen("login.txt", "r");
    rewind(fptr);
    fgets(heading_line, sizeof(heading_line), fptr);
    while (i<3)
    {
        fscanf(fptr, "%s %s",name,password);
        if (strcmp(u_name, name) == 0 && strncmp(u_pass, password, 7) == 0)
        {
            printf("\n\t\t\t\t\t\t\b\b\bLogin Successful");
            Beep(2500, 150);
            Beep(2600, 350);
            system("cls");
            check=0;
            printWelcome();
            return;
        }
        if (check == 0)
        {
            break;
        }
        i++;
        if (i==3)
        {
            j++;
            if (j<=3)
            {
                printf("\n\t\t\t\t\tWrong username or password\n\t\t\t\t\t\tTry Again: \n");
                Beep(250, 200);
                Beep(200, 400);
                fclose(fptr);
                login(j);
            }
            else
            {
                printf("\n\t\t\t\t\t\t\b3 Wrong tries\n\t\t\t\t\t\t\b\b\b\b\b\bPlease try again later");
                Beep(250, 200);
                Beep(200, 400);
                Beep(150,500);
                fclose(fptr);
                exit(0);
            }
        }
    }
    fclose(fptr);
}

void menu(void)
{
    int choice;
    do
    {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 06);
        puts("\n\tChoose which operation you would like to perform.\n");
        puts("\t[1] Add Product.");
		puts("\t[2] Withdraw Product.");
		puts("\t[3] Search Product(s).");
		puts("\t[4] Display All Products");
		puts("\t[5] Display transaction history.\n");
		puts("\t[6] Exit.\n");
        do
        {
            printf("\t%s", "Enter your choice: ");
            scanf("%d", &choice);
            if(choice > 0 && choice < 7)
            {
                break;
            }
            else
            {
                puts("\n\tYou have entered an incorrect option\n");
                Beep(100,500);
            }
        }while(1);
        
        if(choice == 1)
        {
            input_item();
        }
        else if(choice == 2)
        {
            withdraw();
        }
        else if(choice == 3)
        {
            search();
        }
        else if(choice == 4)
		{
			display_menu();
		}
        else if(choice == 5)
        {
			Transactionshistory();
        }
        else if(choice ==6)
        {
        	bill();
        	break;	
		}
    } while(1);
}

void input_item(void)
{
	FILE *transactions=fopen("Transactions.txt","a+");
	strcpy(status,"Deposit");
    char choice;
    int check=0, count=0;
    unsigned int quantity=0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 04);
	printf("\n\n\t\t*************************************\n");
	printf("\t\t|           Adding an Item          |\n");
	printf("\t\t*************************************\n");
    do 
	{
	SetConsoleTextAttribute(hConsole, 03);
    	FILE *file = fopen("Products.txt", "a+"); 
    	if (file == NULL) 
	{
        printf("Error opening file for writing!\n");
        exit(0);
    }
    	rewind(file);
        printf("\n\n\tEnter product name: \t");
        fflush(stdin);
        gets(product.productName);
	
		check=product_check(product.productName);
		
		if(check == 0)
		{
		product.productId=assignID();
		printf("\tEnter product quantity: ");
        scanf("%d",&product.productquantity);
        
        printf("\tEnter product price: \t");
        scanf("%f", &product.productPrice);

        printf("\tEnter product category: ");
        fflush(stdin);
        gets(product.productCategory);
        fprintf(file, "%3d %11s %10d %9.2f %10s\n", product.productId, product.productName,product.productquantity, product.productPrice, product.productCategory);
        fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,product.productquantity, product.productPrice, product.productCategory,status);
		if(product.productquantity > overstock)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    		SetConsoleTextAttribute(hConsole, 04);
			printf("\n\n\t\t*************************************\n");
			printf("\t\t| ALERT : INVENTORY IS OVERSTOCKING |\n");
			printf("\t\t*************************************\n");
			for(int i=0; i<3; i++)
				{
					Beep(750, 800);
				}
		}
		net_transactions=net_transactions + (product.productquantity*product.productPrice);
		deposit_value=deposit_value + (product.productquantity*product.productPrice);
        fclose(file);
		}
		else if(check == 1)
		{
			printf("\tEnter product quantity: ");
        	scanf("%d",&product.productquantity);
			FILE *temp=fopen("temp.txt","w");
			struct Product temporary;
			rewind(file);
			fgets(heading_line,sizeof(heading_line),file);
			fputs(heading_line,temp);
			while(fscanf(file,"%d %s %d %f %s",&temporary.productId,temporary.productName,&temporary.productquantity,&temporary.productPrice,temporary.productCategory) == 5)
			{
				if(!(strcmp(product.productName,temporary.productName)==0))
				{
					fprintf(temp,"%3d %11s %10d %9.2f %10s\n",temporary.productId,temporary.productName,temporary.productquantity,temporary.productPrice,temporary.productCategory);
				}
				if(strcmp(product.productName,temporary.productName)==0 && count==0)
				{
				fprintf(temp,"%3d %11s %10d %9.2f %10s\n",temporary.productId,temporary.productName,temporary.productquantity+product.productquantity,temporary.productPrice,temporary.productCategory);
				fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,product.productquantity, product.productPrice, product.productCategory,status);
				count++;
				net_transactions=net_transactions+product.productquantity*product.productPrice;
					if(product.productquantity+temporary.productquantity > overstock)
					{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    					SetConsoleTextAttribute(hConsole, 04);
						printf("\n\n\t\t*************************************\n");
						printf("\t\t| ALERT : INVENTORY IS OVERSTOCKING |\n");
						printf("\t\t*************************************\n");
						for(int i=0; i<3; i++)
						{
							Beep(750, 800);
						}
					}	
				}
			}
			deposit_value=deposit_value + (product.productquantity*product.productPrice);
			fclose(temp);
			fclose(file);
			remove("Products.txt");
			rename("temp.txt","Products.txt");
		}
		else
		fclose(file);
		deposit_quantity++;
		printf("\tDo you want to enter another product? (y/n): ");
        scanf(" %c", &choice); 
    } while (choice == 'y' || choice == 'Y');
    fclose(transactions);
}

int product_check(char name[])
{
    struct Product temp;
    int check = 0;
    FILE *checker = fopen("Products.txt", "r");
    fgets(heading_line, sizeof(heading_line), checker);
    while (fscanf(checker, "%d %s %d %f %s", &temp.productId,temp.productName,&temp.productquantity,&temp.productPrice,temp.productCategory) == 5)
    {
        if (strcmp(temp.productName, name) == 0)
        {
            check = 1;
        }
    }
    rewind(checker);
    fclose(checker);
    return check;
}


void display_menu(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleTextAttribute(hConsole, 04);
	printf("\n\n\t\t*************************************\n");
	printf("\t\t|          Displaying Menu          |\n");
	printf("\t\t*************************************\n");
    FILE *file=fopen("Products.txt", "r");
    if (file==NULL) 
    {
        printf("Error opening file for reading!\n");
        return;
    }
    rewind(file);
    fgets(heading_line, sizeof(heading_line), file);
    SetConsoleTextAttribute(hConsole, 02);
	printf("\t_____________________________________________________\n");
	printf("\t|ID |     Product|   Quantity|     Price|   Category|\n");
	printf("\t|---------------------------------------------------|\n");
    while(fscanf(file, "%d %s %d %f %s", &product.productId, product.productName, &product.productquantity, &product.productPrice, product.productCategory) == 5)
    {
        printf("\t|%3d| %11s| %10d| %9.2f| %10s|\n", product.productId, product.productName, product.productquantity, product.productPrice, product.productCategory);
	}
	printf("\t|___________________________________________________|\n");
    fclose(file);
}

int assignID(void)
{
	int id;
	char sentence[100];
	int line=1, max=0;
	FILE *fptr=fopen("Products.txt","r");
	rewind(fptr);
	struct Product temp;
    while(fgets(sentence,sizeof(sentence),fptr)!=NULL) 
	{
        line++;
    }
	rewind(fptr);
    if(line == 1)
	id=1;
	else
	{
		fgets(sentence,sizeof(sentence),fptr);
		while (fscanf(fptr, "%d %s %d %f %s", &temp.productId, temp.productName, &temp.productquantity, &temp.productPrice, temp.productCategory) == 5)
		{
			if(max<temp.productId)
			max=temp.productId;
		}
		id=max;
	}
	fclose(fptr);
	id++;
	return id;
}

void search(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleTextAttribute(hConsole, 04);
	printf("\n\n\t\t*************************************\n");
	printf("\t\t|         Searching an Item         |\n");
	printf("\t\t*************************************\n");
	int choice;
	SetConsoleTextAttribute(hConsole, 03);
	printf("\n\tChoose an option:\n");
	puts("\t[1] Search by Product ID");
	puts("\t[2] Search by Category Name");
	printf("\n\tEnter your choice: ");
	scanf("%d", &choice);
	
	if(choice == 1)
	{
		search_by_ID();
	}
	else if(choice == 2)
	{
		search_by_category();
	}
	else
	{
		printf("\n\tWrong Choice!!\n\tEnter Again: \n");
		search();
	}
}

void search_by_ID(void)
{
	int desired_id; 
    printf("\tEnter the ID you want to search for: ");
    scanf("%d", &desired_id);
    FILE *file = fopen("Products.txt", "r");
    if (file == NULL) 
	{
        printf("Error opening file\n");
        exit(0);
    }
    int found = 0;
    fgets(heading_line,sizeof(heading_line),file);
    while(fscanf(file, "%d %s %d %f %s", &product.productId, product.productName, &product.productquantity, &product.productPrice, product.productCategory) == 5)
    {
        if(desired_id == product.productId)
        {
            found = 1;
        	break;
        }
    }
    if(found == 0)
    {
        printf("\n%s\n", "\tID not found. Try a different ID:");
        search_by_ID();
    }
    rewind(file);
    fgets(heading_line,sizeof(heading_line),file);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 02);
    printf("\t_____________________________________________________\n");
	printf("\t|ID |     Product|   Quantity|     Price|   Category|\n");
	printf("\t|---------------------------------------------------|\n");
    while(fscanf(file,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
	{
		if(desired_id==product.productId)
		{
			printf("\t|%3d| %11s| %10d| %9.2f| %10s|\n", product.productId, product.productName, product.productquantity, product.productPrice, product.productCategory);
		}
	}
   	printf("\t|___________________________________________________|\n");
    fclose(file);
}

void search_by_category(void)
{
	char desired_category[20];
	printf("\tEnter the category you want to search for: ");
	fflush(stdin);
	gets(desired_category);
	FILE *fptr=fopen("Products.txt","r");
	if (fptr == NULL) 
	{
        printf("Error opening file\n");
        exit(0);
    }
    int found = 0;
    fgets(heading_line,sizeof(heading_line),fptr);
    while(fscanf(fptr, "%d %s %d %f %s", &product.productId, product.productName, &product.productquantity, &product.productPrice, product.productCategory) == 5)
    {
        if(strcmp(product.productCategory,desired_category) == 0)
        {
            found = 1;
        	break;
        }
    }
    if(found == 0)
    {
        printf("\n%s\n", "\tCategory not found. Try a different Category: ");
        search_by_category();
    }
    rewind(fptr);
	fgets(heading_line,sizeof(heading_line),fptr);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 02);
	printf("\t_____________________________________________________\n");
	printf("\t|ID |     Product|   Quantity|     Price|   Category|\n");
	printf("\t|---------------------------------------------------|\n");
	while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
	{
		if(strcmp(product.productCategory,desired_category)==0)
		{
			printf("\t|%3d| %11s| %10d| %9.2f| %10s|\n", product.productId, product.productName, product.productquantity, product.productPrice, product.productCategory);
		}
	}
	printf("\t|___________________________________________________|\n");
    fclose(fptr);
}

void withdraw(void)
{
	int choice;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleTextAttribute(hConsole, 04);
	printf("\n\n\t\t*************************************\n");
	printf("\t\t|        Withdrawing an Item        |\n");
	printf("\t\t*************************************\n");
	SetConsoleTextAttribute(hConsole, 03);
	printf("\n\tChoose an option:\n");
	puts("\t[1] Withdraw by Product ID");
	puts("\t[2] Withdraw by Product Name");
	printf("\n\tEnter your choice: ");
	scanf("%d", &choice);
	if(choice == 1)
	{
		withdraw_by_ID();
	}
	else if(choice == 2)
	{
		withdraw_by_name();
	}
	else
	{
		printf("\n\tWrong Choice!!\n\tEnter Again: \n");
		withdraw();
	}
}

void withdraw_by_ID(void)
{
	strcpy(status,"Withdraw");
	FILE *transactions = fopen("Transactions.txt","a+");
	int id, choice, quantity;
	FILE *fptr=fopen("Products.txt","r");
	FILE *temp=fopen("temp.txt","w");
	printf("\tEnter ID of product you want to withdraw: ");
	scanf("%d",&id);
    if (fptr == NULL || temp == NULL) 
	{
        printf("Error opening file\n");
        exit(0);
    }
    int found = 0;
    fgets(heading_line,sizeof(heading_line),fptr);
    while(fscanf(fptr, "%d %s %d %f %s", &product.productId, product.productName, &product.productquantity, &product.productPrice, product.productCategory) == 5)
    {
        if(id == product.productId)
        {
            found = 1;
        	break;
        }
    }
    if(found == 0)
    {
        printf("\n%s\n", "\tID not found. Try a different ID: ");
        fclose(transactions);
        fclose(fptr);
        fclose(temp);
        withdraw_by_ID();
    }
    printf("\tChoose an option:\n");
	puts("\t[1] Withdraw Full Amount");
	puts("\t[2] Withdraw Specific Amount");
	printf("\n\tEnter your choice: ");
	scanf("%d", &choice);
    rewind(fptr);
	fgets(heading_line,sizeof(heading_line),fptr);
	if(choice == 1)
	{
		fputs(heading_line,temp);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
	{
		if(id!=product.productId)
		{
			fprintf(temp,"%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity,product.productPrice,product.productCategory);
		}
		else
		{
			fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,product.productquantity, product.productPrice, product.productCategory,status);
			withdraw_value=withdraw_value + (product.productquantity*product.productPrice);
			net_transactions=net_transactions - (product.productquantity*product.productPrice);
			}
		}
	}
	else if(choice == 2)
	{
		printf("\tEnter the quantity you wish to withdraw: ");
		scanf("%d",&quantity);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
		{
			if(id == product.productId)
			{
				if(product.productquantity<quantity)
				{
					printf("\n\n\tThe quantity you entered is more than the quantity in the system");
					printf("\n\tYou cant withdraw more than %d",product.productquantity);
					printf("\n\tEnter Again: \n");
					fclose(transactions);
					fclose(fptr);
					withdraw_by_ID();
				}
			}
		}
		rewind(fptr);
		fgets(heading_line,sizeof(heading_line),fptr);
		fputs(heading_line,temp);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
		{
			if(id!=product.productId)
			{
				fprintf(temp,"%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity,product.productPrice,product.productCategory);
			}
			else
			{
				fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,quantity, product.productPrice, product.productCategory,status);
				if(product.productquantity > quantity)
				{
						fprintf(temp,"%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity-quantity,product.productPrice,product.productCategory);
						if(product.productquantity-quantity < understock)
				{
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    				SetConsoleTextAttribute(hConsole, 04);
					printf("\n\n\t\t*************************************\n");
					printf("\t\t| ALERT: INVENTORY IS UNDERSTOCKING |\n");
					printf("\t\t*************************************\n");
					for(int i=0; i<3; i++)
						{
				 			Beep(750, 800);
						}
					}
				}
				net_transactions=net_transactions - (quantity*product.productPrice);
				withdraw_value=withdraw_value + (quantity*product.productPrice);
			}
		}
	}
	else
	{
		printf("\n\tWrong Choice!!\n\tEnter Again: \n");
		withdraw_by_ID();
	}
	fclose(transactions);
	fclose(fptr);
	fclose(temp);
	remove("Products.txt");
	rename("temp.txt","Products.txt");
	withdraw_quantity++;
}

void withdraw_by_name(void)
{
	strcpy(status,"Withdraw");
	FILE *transactions = fopen("Transactions.txt","a+");
	char name[30];
	int choice, quantity;
	printf("\tEnter Product Name you wish to withdraw: ");
	scanf("%s",name);
	FILE *fptr=fopen("Products.txt","r");
	FILE *temp=fopen("temp.txt","w");
	int found = 0;
    fgets(heading_line,sizeof(heading_line),fptr);
    while(fscanf(fptr, "%d %s %d %f %s", &product.productId, product.productName, &product.productquantity, &product.productPrice, product.productCategory) == 5)
    {
        if(strcmp(name,product.productName) == 0)
        {
            found = 1;
        	break;
        }
    }
    if(found == 0)
    {
        printf("\n%s\n", "\tProduct not found. Try a different Product: ");
        fclose(transactions);
        withdraw_by_name();
    }
    rewind(fptr);
	printf("\tChoose an option:\n");
	puts("\t[1] Withdraw Full Amount");
	puts("\t[2] Withdraw Specific Amount");
	printf("\n\tEnter your choice: ");
	scanf("%d", &choice);
	fgets(heading_line,sizeof(heading_line),fptr);
	if(choice == 1)
	{
		fputs(heading_line,temp);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
	{
		if(!(strcmp(product.productName,name) == 0))
		{
			fprintf(temp,"%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity,product.productPrice,product.productCategory);
		}
		else
		{
			fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,product.productquantity, product.productPrice, product.productCategory,status);
			withdraw_value=withdraw_value + (product.productquantity*product.productPrice);
			net_transactions=net_transactions - (product.productquantity*product.productPrice);
		}
	}
	}
	else if(choice == 2)
	{
		printf("\tEnter the quantity you wish to withdraw: ");
		scanf("%d",&quantity);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
		{
			if(strcmp(product.productName,name) == 0)
			{
				if(product.productquantity < quantity)
				{
					printf("\n\n\tThe quantity you entered is more than the quantity in the system");
					printf("\n\tYou cant withdraw more than %d",product.productquantity);
					printf("\n\tEnter Again: \n");
					withdraw_by_name();
				}
			}
		}
		rewind(fptr);
		fgets(heading_line,sizeof(heading_line),fptr);
		fputs(heading_line,temp);
		while(fscanf(fptr,"%d %s %d %f %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory) == 5)
		{
			if(!(strcmp(product.productName,name) == 0))
			{
				fprintf(temp,"\%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity,product.productPrice,product.productCategory);
			}
			else
			{
				fprintf(transactions, "%3d %11s %10d %9.2f %12s %9s\n", product.productId, product.productName,quantity, product.productPrice, product.productCategory,status);
				if(product.productquantity>quantity)
				{
					fprintf(temp,"%3d %11s %10d %9.2f %10s\n",product.productId,product.productName,product.productquantity-quantity,product.productPrice,product.productCategory);
				}
				net_transactions=net_transactions - (quantity*product.productPrice);
				withdraw_value=withdraw_value + (quantity*product.productPrice);
				if(product.productquantity-quantity < understock)
					{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    				SetConsoleTextAttribute(hConsole, 04);
						printf("\n\n\t\t*************************************\n");
						printf("\t\t| ALERT: INVENTORY IS UNDERSTOCKING |\n");
						printf("\t\t*************************************\n");
						for(int i=0; i<3; i++)
							{
					 			Beep(750, 800);
							}
					}
			}
		}
	}
	else
	{
		printf("\n\tWrong Choice!!\n\tEnter Again: \n");
		withdraw_by_name();
	}
	fclose(fptr);
	fclose(temp);
	fclose(transactions);
	remove("Products.txt");
	rename("temp.txt","Products.txt");
	withdraw_quantity++;
}

void Transactionshistory(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 04);
	FILE *transactions = fopen("Transactions.txt","r");
	printf("\n\n\t\t\t\b\b*************************************\n");
	printf("\t\t\t\b\b|        Transaction History        |\n");
	printf("\t\t\t\b\b*************************************\n");	
 	SetConsoleTextAttribute(hConsole, 02);
	printf("\t_______________________________________________________________\n");
	printf("\t|ID |     Product|   Quantity|     Price|   Category|   Status|\n");
	printf("\t|-------------------------------------------------------------|\n");
	fgets(heading_line,sizeof(heading_line),transactions);
	while(fscanf(transactions,"%d %s %d %f %s %s",&product.productId,product.productName,&product.productquantity,&product.productPrice,product.productCategory,status) == 6)
	{
		printf("\t|%3d| %11s| %10d| %9.2f| %10s| %8s|\n", product.productId, product.productName, product.productquantity, product.productPrice, product.productCategory,status);
	}
	printf("\t|_____________________________________________________________|\n");
	fclose(transactions);
}

void bill(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 01);
	puts("\t________________________________________");
	puts("\t|           Transaction Bill           |");
	puts("\t|--------------------------------------|");
	printf("\t| User: %30s |\n",u_name);
	printf("\t| No. of items Deposited: %12d |\n",deposit_quantity);
	printf("\t| Value: %29.2f |\n",deposit_value);
	printf("\t| No. of items Withdrawn: %12d |\n",withdraw_quantity);
	printf("\t| Value: %29.2f |\n",withdraw_value);
	puts("\t|--------------------------------------|");
	printf("\t| Net Value: %25.2f |\n",net_transactions);
	puts("\t|______________________________________|");
	SetConsoleTextAttribute(hConsole, 07);
}
