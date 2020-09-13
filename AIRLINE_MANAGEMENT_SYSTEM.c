#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <windows.h>

#define MAN_NAME_LEN 50
#define maxe 100
#define maxb 100
typedef struct event
{
	int date;
	int month;
	int years;
}event;


typedef struct flight
{
	int flight_no,
		avail_economy_class_seat_count,
		avail_business_class_seat_count,
		economy_class_fare,
		business_class_fare;

		event date_of_flight; /* date of flight take off */

	char flight_name[50],
		flight_destination[20],
		flight_start[20];
}flight;


typedef struct ticket
{
	long int booking_id;	/* the value that distinguishes each ticket*/
	int ticket_status;/* stores whether the ticket is valid, invalid or cancelled */
	char name_of_user[30];
	char gender_of_user;
	int age_of_user;
	float total_cost;
	int number_of_business_class_ticket;
	int number_of_economy_class_ticket;
	int flight_booked;
	char flight_name[20];
	flight carrier_flight;
}ticket;

flight* newflight;//GLOBAL STRUCTURE POINTER
ticket newticket;//GLOBAL VARIABLE OF STRUCTURE TICKET
int choice,password_invocations=0;
char password[10]={"pkmkb"};
int f_number;//GLOBAL VARIABLE DECLARED FOR NUMBER OF FLIGHT (SEARCH FUNCTION);
char*f_name;//GLOBAL VARIABLE DECLARED FOR NAME OF FLIGHT(SEARCH FUNCTION);
int FLAG=1;//TEMPORARY FLAG VARIABLE;
void print_space_in_newline(int qty)
{
    printf("\n");
    while(qty>0)
    {
        printf(" ");
        --qty;
    }
}
/*
int get_time()
{
	time_t rawtime;
	struct tm * timeinfo;
	char* day,
		*month;

	int date=0,
		hour=0,
		min=0,
		sec=0,
		year=0;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("\n\nCurrent local time and date: %s", asctime(timeinfo));
	sscanf(asctime(timeinfo),"%s%s%d %d:%d:%d %d",day,month,&date,&hour,&min,&sec,&year);
	printf("\n date : %d",date);
	printf("\n hour : %d",hour);
	printf("\n min : %d",min);
	printf("\n sec : %d",sec);
	printf("\n year : %d",year);

	return 0;
}
*/

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Password(void) //for password option
{
    if(password_invocations!=0)
    system("cls");

    ++password_invocations;
    system("color 06");
    char d[25]="Password Protected";
    char ch,pass[10];
    int i=0,j;
    //textbackground(WHITE);
    //textcolor(RED);
   // gotoxy(10,4);
   printf("\n\n\t\t");
    for(j=0;j<20;j++)
    {
        Sleep(10);
        printf("*");
    }

    for(j=0;j<20;j++)
    {
        Sleep(10);
        printf("%c",d[j]);
    }

    for(j=0;j<20;j++)
    {
        Sleep(10);
        printf("*");
    }

   // gotoxy(10,10);
    printf("\n\n\tEnter Password:");

    while(ch!=13)
    {
        ch=getch();

        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }

    pass[i] = '\0';

    if(strcmp(pass,password)==0)
    {
       // gotoxy(15,9);
        //textcolor(BLINK);
        printf("\n\n\tPassword match");
       // gotoxy(17,10);
        printf("\n\n\tPress any key to continue.....");
        getch();
        admin();
    }
    else
    {
       // gotoxy(15,16);
        printf("\aWarning!! Incorrect Password");
        getch();
        Password();
    }
}

void admin()
{
    int choice;
    char*filenamee={"HANGER.dat"};
    system("color 06");
    system("cls");
    gotoxy(20,3);
    printf("ADMIN MENU");
    gotoxy(20,5);
    printf("1. Add Flights ");
    gotoxy(20,7);
    printf("2. Delete FLights");
    gotoxy(20,9);
    printf("3. Search Flights(BY NUMBER)");
    gotoxy(20,11);
    printf("4. Search Flights (BY NAME)");
    gotoxy(20,13);
    printf("5. View All Flights");
    gotoxy(20,15);
    printf("6. Edit All Flights");
    gotoxy(20,17);
    printf("7. Return To Main Menu");
    gotoxy(20,19);

    printf(" Enter your choice  :");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:append_flight_details_to_file(&newflight,filenamee);
            break;
        case 2:
              printf("\nENTER FLIGHT NUMBER TO DELETE");
              scanf("%d",&f_number);
              delete_fight_by_id(f_number,filenamee);
            break;
        case 3:
            printf("\nENTER FLIGHT NUMBER TO SEARCH");
            scanf("%d",&f_number);
            search_and_print_flight_by_no(f_number,filenamee);
            break;
        case 4:  printf("\nENTER FLIGHT NAME TO SEARCH");
            scanf("%s",&f_name);
            search_and_print_flight_by_name(&f_name,filenamee);
        case 5:print_all_flights(filenamee);
            break;
        case 6:printf("\nENTER FLIGHT NUMBER TO SEARCH");
                scanf("%d",&f_number);
           edit_flight_with_id(f_number,filenamee);
           break;
        case 7:main();
            break;
        default:main();
    }


}
/*
flight* test_init()
{
	flight* newflight;
	newflight=(flight*)malloc(sizeof(flight));

	newflight->flight_no=1;
	newflight->economy_class_seat_count=10;
	newflight->business_class_seat_count=5;
	newflight->economy_class_fare=5000;
	newflight->business_class_fare=10000;
	newflight->date_of_flight.date=10;
	newflight->date_of_flight.month=4;
	newflight->date_of_flight.years=2019;
	strcpy(newflight->flight_name,"indigo");
	strcpy(newflight->flight_destination,"delhi");
	strcpy(newflight->flight_start,"mumbai");

	return newflight;
}*/

void get_flight_details_by_user(flight* flight_details_holder)
{
	printf("\n FLIGHT NO : ");
	scanf("%d",&flight_details_holder->flight_no);

	printf("\n NO OF ECONOMY CLASS SEATS : ");
	scanf("%d",&flight_details_holder->avail_economy_class_seat_count);

	printf("\n NO OF BUSINESS CLASS SEATS : ");
	scanf("%d",&flight_details_holder->avail_business_class_seat_count);

	printf("\n ECONOMY CLASS FARE : ");
	scanf("%d",&flight_details_holder->economy_class_fare);

	printf("\n BUSINESS CLASS FARE : ");
	scanf("%d",&flight_details_holder->business_class_fare);

	printf("\n DATE OF FLIGHT : ");
	scanf("%d",&flight_details_holder->date_of_flight.date);

	printf("\n MONTH OF FLIGHT : ");
	scanf("%d",&flight_details_holder->date_of_flight.month);

	printf("\n YEAR OF FLIGHT : ");
	scanf("%d",&flight_details_holder->date_of_flight.years);

	printf("\n FLIGHT NAME : ");
	scanf("%s",flight_details_holder->flight_name);

	printf("\n FLIGHT DESTINATION : ");
	scanf("%s",flight_details_holder->flight_destination);

	printf("\n FLIGHT PLACE OF ORIGIN : ");
	scanf("%s",flight_details_holder->flight_start);

	printf("\n\n");
}
void print_given_flight_details(flight avl_flight)
{
	printf("\n FLIGHT NO : %d",avl_flight.flight_no);
	printf("\n NO OF ECONOMY CLASS SEATS : %d",avl_flight.avail_economy_class_seat_count);
	printf("\n NO OF BUSINESS CLASS SEATS : %d",avl_flight.avail_business_class_seat_count);
	printf("\n ECONOMY CLASS FARE : %d",avl_flight.economy_class_fare);
	printf("\n BUSINESS CLASS FARE : %d",avl_flight.business_class_fare);

	printf("\n DATE OF FLIGHT : %d",avl_flight.date_of_flight.date);
	printf("\n MONTH OF FLIGHT : %d",avl_flight.date_of_flight.month);
	printf("\n YEAR OF FLIGHT : %d",avl_flight.date_of_flight.years);

	printf("\n FLIGHT NAME : %s",avl_flight.flight_name);
	printf("\n FLIGHT DESTINATION : %s",avl_flight.flight_destination);
	printf("\n FLIGHT PLACE OF ORIGIN : %s",avl_flight.flight_start);
	printf("\n\n");
}

int append_flight_details_to_file(flight* newflight, char* filename)
{
	FILE* file;
	file=fopen(filename,"wb");

	if(file==NULL)
	{
		printf("\n unable to open file\n");
	}
	else
	{get_flight_details_by_user(newflight);
		fwrite(newflight,sizeof(flight),1,file);
	}

	fclose(file);

	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
	return 0;
}


int search_and_print_flight_by_no(int f_no, char* filename)
{
	/*
		* the function returns -1 if unable to open file
		* -2 if details not found
		* 0 if details found
	*/

	FILE* file;
	flight newflight;
	int found_flag=0;
	file=fopen(filename,"rb");

	if(file==NULL)
	{
		printf("\n unable to open file\n");
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&newflight,sizeof(flight),1,file)>0)
		{
			if(newflight.flight_no==f_no)
			{
				found_flag=1;
				print_given_flight_details(newflight);
			}
			else
			{
				continue;
			}
		}
		fclose(file);
		if(found_flag==0)
		{
			printf("\n NO FLIGHT WITH FLIGHT NO { %d } IS AVAILABLE\n",f_no );
			return 1;
		}
		else
		{	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;
			return 0;
		}
	}


	}
}


int search_and_print_flight_by_name(char* f_name, char* filename)
{
	/*
		* the function returns -1 if unable to open file
		* -2 if details not found
		* 0 if details found
	*/

	FILE* file;
	int found_flag=0;
	flight newflight;
	file=fopen(filename,"rb");

	if(file==NULL)
	{
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&newflight,sizeof(flight),1,file)>0)
		{
			if(strcmp(newflight.flight_name,f_name)==0)
			{
				found_flag=1;
				print_given_flight_details(newflight);
			}
			else
			{
				continue;
			}
		}
		fclose(file);
		if(found_flag==0)
		{
			printf("\n NO FLIGHT WITH FLIGHT NAME { %s } IS AVAILABLE",f_name );
			return 1;
		}
		else
		{
		    	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
			return 0;
		}
	}

}

/* int search_flight_by_date(); */
/* int search_flight_by_fare(); */

int delete_fight_by_id(int f_no, char* filename)
{
	flight newflight;
	FILE* file;
	FILE* temp_file;
	int found_flag=0;

	file=fopen(filename,"rb");
	temp_file=fopen("TEMP.dat","wb");

	if(file==NULL || temp_file==NULL)
	{
		printf("\n delete operation failed due to file error\n");
		fclose(temp_file);
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&newflight,sizeof(flight),1,file)>0)
		{
			if(newflight.flight_no==f_no)
			{
				found_flag=1;
				continue;
			}
			else
			{
				printf("\n FLIGHT NO : %d\n",newflight.flight_no);
				fwrite(&newflight,sizeof(flight),1,temp_file);
			}
		}


		fclose(file);
		fclose(temp_file);

		if(found_flag==0)
		{
			printf("\n NO FLIGHT WITH FLIGHT NO { %d } IS AVAILABLE \n \n",f_no );
			remove("TEMP.dat");
			return -2;
		}
		else
		{
			printf("\n FLIGHT WITH FLIGHT NO { %d } SUCCESSFULLY DELETED \n",f_no );
			remove(filename);
			rename("TEMP.dat",filename);

		}
	}
	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
	return 0;
}

int edit_flight_with_id(int f_no, char* filename)
{

	flight newflight;
	FILE* file;
	FILE* temp_file;
	int found_flag=0;

	file=fopen(filename,"rb");
	temp_file=fopen("TEMP.dat","wb");

	if(file==NULL || temp_file==NULL)
	{
		printf("\n edit operation failed due to file error\n");
		fclose(temp_file);
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&newflight,sizeof(flight),1,file)>0)
		{
			if(newflight.flight_no==f_no)
			{
				found_flag=1;
				get_flight_details_by_user(&newflight);
				fwrite(&newflight,sizeof(flight),1,temp_file);
				//continue;
			}
			else
			{
				printf("\n FLIGHT NO : %d\n",newflight.flight_no);
				fwrite(&newflight,sizeof(flight),1,temp_file);
			}
		}


		fclose(file);
		fclose(temp_file);

		if(found_flag==0)
		{
			printf("\n NO FLIGHT WITH FLIGHT NO { %d } IS AVAILABLE \n \n",f_no );
			remove("TEMP.dat");
			return -2;
		}
		else
		{
			printf("\n FLIGHT WITH FLIGHT NO { %d } SUCCESSFULLY EDITED \n",f_no );
			remove(filename);
			rename("TEMP.dat",filename);

		}
	}
	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
return 0;
}

int print_all_flights(char* filename)
{
	flight newflight;
	FILE* file;
	file=fopen(filename,"rb");
	while(fread(&newflight,sizeof(flight),1,file)>0)
	{
		print_given_flight_details(newflight);
	}
	fclose(file);
		printf("\nENTER 1 FOR MAIN MENU AND 2 FOR ADMIN MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:admin();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
	return 0;
}
/* USER FUNCTION WHICH CONTAINS DIFFERENT FUNCTIONS WHICH ARE FOLLOWING*/
void user()
{
    long int bookid;
    int choice;
    char*filename2={"TICKET.dat"};
    system("cls");
    system("color 06");
    gotoxy(20,3);
    printf(" USER MENU ");
    gotoxy(20,5);
    printf(" 1. Reserve a TickeT ");
    gotoxy(20,7);
    printf(" 2. Search Ticket(BY ID)");
    gotoxy(20,9);
    printf(" 3. View All Ticket");
    gotoxy(20,11);
    printf(" 4. Cancel Ticket");
    gotoxy(20,13);
    printf(" 5. Edit Ticket Details");
    gotoxy(20,15);
    printf(" 6.Return To Mainmenu");
        gotoxy(20,17);

    printf("\nPRESS RESPECTIVE KEYS FOR RESPECTIVE CHOICE");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:get_ticket_details_by_user(&newticket);
                 append_ticket_to_file(newticket,filename2);
         break;
        case 2:
            printf("\nEnter Book ID");
            scanf("%ld",&bookid);
            search_and_print_ticket_by_id(bookid,filename2);
        break;
        case 3:
            print_all_tickets(filename2);
        break;
        case 4:  printf("\nEnter Book ID");
            scanf("%ld",&bookid);
            delete_ticket_by_id(bookid,filename2);
        break;
        case 5:  printf("\nEnter Book ID");
            scanf("%ld",&bookid);
            edit_ticket_with_id(bookid,filename2);
        break;
        case 6:main();
        break;
        default:printf("\nWRONG CHOICE");
        user();
    }
}

int print_given_ticket(ticket given_ticket)
{
	/* add sometype of screen divider at the beginning and at the end*/
	/* add the beginning screen divider here*/
	printf("\nBOOKING ID : %ld",given_ticket.booking_id);
	printf("\nTICKET STATUS : %d",given_ticket.ticket_status);
	printf("\nNAME OF USER: %s",given_ticket.name_of_user);
	printf("\nGENDER OF USER: %c",given_ticket.gender_of_user);
	printf("\nNUMBER OF BUSINESS CLASS SEATS: %d",given_ticket.number_of_business_class_ticket);
	printf("\nNUMBER OF ECONOMY CLASS SEATS: %d",given_ticket.number_of_economy_class_ticket);
	printf("\nFLIGHT BOOKED: %d",given_ticket.flight_booked);
	printf("\nFLIGHT NAME: %s",given_ticket.flight_name);
	printf("\nTOTAL COST OF TICKET: %f",given_ticket.total_cost);

	/* add the end screen divider here*/
	return 0;
}

int print_all_tickets(char* filename)
{
	FILE* file;
	file=fopen(filename,"rb");
	ticket ticket_details_holder;

	if(file==NULL)
	{
		printf("\n TICKET PRINTING OPERATION FAILED DUE TO FILE ERROR\n");
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&ticket_details_holder,sizeof(ticket),1,file)>0)
		{
			print_given_ticket(ticket_details_holder);
			printf("\n\n\n");
		}
		fclose(file);
			printf("\nENTER 1 FOR MAIN MENU AND 2 FOR USER MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
		return 0;
	}
}

void get_ticket_details_by_user(ticket* ticket_details_holder)
{
    FILE*file;
    flight newflight;
    file=fopen("HANGER.dat","rb");
    printf("\n ENTER HOW MANY BUSINESS CLASS SEATS YOU WANT TO BOOK: ");
    scanf("%d",&ticket_details_holder->number_of_business_class_ticket);
    printf("\n ENTER HOW MANY ECONOMY CLASS SEATS YOU WANT TO BOOK: ");
    scanf("%d",&ticket_details_holder->number_of_economy_class_ticket);
    printf("\n IN WHICH FLIGHT YOU WANT TO BOOK TICKET");
    scanf("%d",&ticket_details_holder->flight_booked);

 while(fread(&newflight,sizeof(flight),1,file)>0)
    {
    if(newflight.flight_no==ticket_details_holder->flight_booked)
    {
        strcpy(ticket_details_holder->flight_name,newflight.flight_name);

        if(newflight.avail_business_class_seat_count<ticket_details_holder->number_of_business_class_ticket && newflight.avail_economy_class_seat_count<ticket_details_holder->number_of_economy_class_ticket)
        {printf("\nSEATS ARE NOT AVAILABLE");
        FLAG=0;}

    else{

    printf("\n BOOKING ID : ");
	scanf("%ld",&ticket_details_holder->booking_id);

	printf("\n TICKET STATUS : ");
	scanf("%d",&ticket_details_holder->ticket_status);
    fflush(stdin);
	printf("\n ENTER NAME : ");
	gets(ticket_details_holder->name_of_user);
    fflush(stdin);
	printf("\n ENTER GENDER: ");
	scanf("%c",&ticket_details_holder->gender_of_user);


    ticket_details_holder->total_cost=ticket_details_holder->number_of_business_class_ticket*newflight.business_class_fare+ticket_details_holder->number_of_economy_class_ticket*newflight.economy_class_fare;
	printf("\n");

    }}
    else
        printf("\nFLIGHT IS NOT AVAILABLE");
}
newflight.avail_business_class_seat_count-=ticket_details_holder->number_of_business_class_ticket;
newflight.avail_economy_class_seat_count-=ticket_details_holder->number_of_economy_class_ticket;
fclose(file);


	//get_flight_details_by_user(&ticket_details_holder->carrier_flight);
}

int append_ticket_to_file(ticket newticket, char* filename)
{
	FILE* file;
	file=fopen(filename,"ab");

	if(file==NULL)
	{
		printf("\nTICKET APPENDING OPERATION FAILED DUE TO FILE ERROR\n");
		fclose(file);
		return -1;
	}
	else

	{
	    if(FLAG==1)
        printf("\n TICKET BOOKED SUCCESSFULLY");
        else
            printf("\nTICKET NOT BOOKED");
		fwrite(&newticket,sizeof(ticket),1,file);
		fclose(file);

	}
	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR USER MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
return 0;
}





int search_and_print_ticket_by_id(long int bk_id,char*filename)
{
	/*
		* the function returns -1 if unable to open file
		* -2 if details not found
		* 0 if details found
	*/

	FILE* file;
	ticket temp_ticket;
	int found_flag=0;
	file=fopen(filename,"rb");

	if(file==NULL)
	{
		printf("\n TICKET SEARCH BY ID OPERATION FAILED DUE TO FILE ERROR\n");
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&temp_ticket,sizeof(ticket),1,file)>0)
		{
			if(temp_ticket.booking_id==bk_id)
			{
				found_flag=1;
				print_given_ticket(temp_ticket);
			}
			else
			{
				continue;
			}
		}
		fclose(file);
		if(found_flag==0)
		{
			printf("\n NO TICKET WITH BOOKING IT { %ld } IS AVAILABLE\n",bk_id );
			return 1;
		}
		else
		{
		    	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR USER MENU");
	            scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
			return 0;
		}
	}


}

int delete_ticket_by_id(long int bk_id,char*filename)
{
	ticket temp_ticket;
	FILE* file;
	FILE* temp_file;
	int found_flag=0;

	file=fopen(filename,"rb");
	temp_file=fopen("TEMP.dat","wb");

	if(file==NULL || temp_file==NULL)
	{
		printf("\n delete ticket operation failed due to file error\n");
		fclose(temp_file);
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&temp_ticket,sizeof(ticket),1,file)>0)
		{
			if(temp_ticket.booking_id==bk_id)
			{
				found_flag=1;
				continue;
			}
			else
			{
				fwrite(&temp_ticket,sizeof(ticket),1,temp_file);
			}
		}


		fclose(file);
		fclose(temp_file);

		if(found_flag==0)
		{
			printf("\n NO TICKET WITH BOOKING ID { %ld } IS AVAILABLE \n \n",bk_id);
			remove("TEMP.dat");
			return -2;
		}
		else
		{
			printf("\n TICKET WITH BOOKING ID { %ld } SUCCESSFULLY CANCELLED \n",bk_id );
			remove(filename);
			rename("TEMP.dat",filename);

		}
	}
	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR USER MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
	return 0;

}

int edit_ticket_with_id(int long bk_id,char* filename)
{system("cls");
	ticket temp_ticket;
	FILE* file;
	FILE* temp_file;
	int found_flag=0;

	file=fopen(filename,"rb");
	temp_file=fopen("TEMP.dat","wb");

	if(file==NULL || temp_file==NULL)
	{
		printf("\n edit operation failed due to file error\n");
		fclose(temp_file);
		fclose(file);
		return -1;
	}
	else
	{
		while(fread(&temp_ticket,sizeof(ticket),1,file)>0)
		{
			if(temp_ticket.booking_id==bk_id)
			{
				found_flag=1;
				get_ticket_details_by_user(&temp_ticket);
				fwrite(&temp_ticket,sizeof(ticket),1,temp_file);
				continue;
			}			else
			{
				fwrite(&temp_ticket,sizeof(ticket),1,temp_file);
			}
		}


		fclose(file);
		fclose(temp_file);

		if(found_flag==0)
		{
			printf("\n NO TICKET WITH BOOKING ID { %ld } IS AVAILABLE \n \n",bk_id );
			remove("TEMP.dat");
			return -2;
		}
		else
		{
			printf("\n TICKET WITH BOOKING ID { %ld } SUCCESSFULLY EDITED \n",bk_id );
			remove(filename);
			rename("TEMP.dat",filename);

		}
	}
	printf("\nENTER 1 FOR MAIN MENU AND 2 FOR USER MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:main();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}
	return 0;
}
void flight_move()
{
    system("MODE 990,595");/* sets terminal size to desired one*/

    #define SCREEN_SIZE 90
    #define SCREEN_MID 50

    int current_pos;
    /*
            ______
            _\ _~-\___
    =  = ==(____AA____D
                \_____\___________________,-~~~~~~~`-.._
                /     o O o o o o O O o o o o o o O o  |\_
                `~-.__        ___..----..                  )
                      `---~~\___________/------------`````
                      =  ===(_________D
    */

    /*
      |
                           --====|====--
                                 |

                             .-"""""-.
                           .'_________'.
                          /_/_|__|__|_\_\
                         ;'-._       _.-';
    ,--------------------|    `-. .-'    |--------------------,
     ``""--..__    ___   ;       '       ;   ___    __..--""``
               `"-// \\.._\             /_..// \\-"`
                  \\_//    '._       _.'    \\_//
                   `"`        ``---``        `"`
    */
    for(current_pos=0;current_pos<SCREEN_SIZE;++current_pos)
    {
        system("cls");
        system("color 02");
        print_space_in_newline(current_pos);printf("\t\t______");
        print_space_in_newline(current_pos);printf("\t\t_\\ _~-\\___");
        print_space_in_newline(current_pos);printf("\t=  = ==(_____A____D");
        print_space_in_newline(current_pos);printf("\t\t\\_____\\___________________,-~~~~~~~`-.._");
        print_space_in_newline(current_pos);printf("\t\t/     o O o o o o O O o o o o o o O o  |\\_");
        print_space_in_newline(current_pos);printf("\t\t`~-.__        ___..----..                  )");
        print_space_in_newline(current_pos);printf("\t\t\t`---~~\\___________/------------`````");
        print_space_in_newline(current_pos);printf("\t\t\t=  ===(_________D\n");
        Sleep(3); // will sleep for 1 s
    }
    system("cls");
    print_space_in_newline(SCREEN_MID);
    print_space_in_newline(SCREEN_MID);printf("                         --====|====--");
    print_space_in_newline(SCREEN_MID);printf("                               | ");
    print_space_in_newline(SCREEN_MID);printf("                               +  ");
    print_space_in_newline(SCREEN_MID);printf("                           .-\"\"\"\"\"-. ");
    print_space_in_newline(SCREEN_MID);printf("                         .'_________'.");
    print_space_in_newline(SCREEN_MID);printf("                        /_/_|__|__|_\\_\\");
    print_space_in_newline(SCREEN_MID);printf("                       ;'-._       _.-';");
    print_space_in_newline(SCREEN_MID);printf("  ,--------------------|    `-. .-'    |--------------------,");
    print_space_in_newline(SCREEN_MID);printf("   ``\"\"--..__    ___   ;       '       ;   ___    __..--\"\"``");
    print_space_in_newline(SCREEN_MID);printf("             `\"-// \\\\.._\\             /_..// \\\\-\"`");
    print_space_in_newline(SCREEN_MID);printf("                \\\\_//    '._       _.'    \\\\_//");
    print_space_in_newline(SCREEN_MID);printf("                 `\"`        ``---``        `\"`");
    print_space_in_newline(SCREEN_MID);printf("\n\n\n\n");
}
int main()
{
    flight_move();

	//newflight= test_init();

	int choice;
	printf("\nENTER 1 FOR ADMIN MENU AND 2 FOR USER MENU");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:Password();
	            admin();
	    break;
	    case 2:user();
	    break;
	    default:printf("\nWRONG CHOICE\n");
	    main();
	    break;

	}

	return 0;
}
