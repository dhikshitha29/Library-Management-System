#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h> //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h> //contains toupper(), tolower()
#include<time.h>
#include<dos.h>

char cata[][15]={"Computer","Electronics","Novel Books","Mathematics","Science book"};

//list of global files that can be accessed form anywhere in program
FILE *fp,*ft,*fs;
//list of global variable
int s;
char f;
char password[10]={"c"};
struct Date
{
    int mm,dd,yy;
};
struct books
{
    int id;//book ID
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    int Price;
    int count;
    int rackno;
    char *cat;
    struct Date issued;
    struct Date due;
};
struct books a;
void mainmenu()

{
    int i;
    system("cls");
    printf("\n\n\t\t\t\tMAIN MENU");
    printf("\n");
    printf("\n\t\t\t 1. Add Books   ");
    printf("\n");
    printf("\n\t\t\t 2. Delete books");
    printf("\n");
    printf("\n\t\t\t 3. Search Books");
    printf("\n");
    printf("\n\t\t\t 4. Issue Books");
    printf("\n");
    printf("\n\t\t\t 5. View Book list");
    printf("\n");
    printf("\n\t\t\t 6. Edit Book's Record");
    printf("\n");
    printf("\n\t\t\t 7. Close Application");
    printf("\n");
    printf("\n\n\tENTER YOUR CHOICE :");
    switch(getch())
    {
        case '1':
            add();
            break;
        case '2':
            delete();
            break;
        case '3':
            search();
            break;
        case '4':
            issue();
            break;
        case '5':
            view();
            break;
        case '6':
            edit();
            break;
        case '7':
        {
            printf("\n\n\t\t\tLIBRARY MANAGEMENT SYSTEM");
            printf("\n");
            printf("\n\t\t\tBY");
            printf("\n");
            printf("\n\t\t\tDHIKSHITA.A-19PD09");
            printf("\n");
            printf("\n\t\t\tSWATHI PRATHAA.P-19PD38");
            printf("\n");
            printf("\n\t\t\t\tTHANK YOU!!!");
            exit(0);
        }
        default:
        {
            printf("\n");
            printf("\n\n\tWrong Entry!!Please re-entered correct option");
            if(getch())
                mainmenu();
        }
    }
}
void mainmenu1(void)
{
  int i;
    system("cls");
    printf("\n\n\t\t\t\tMAIN MENU");
    printf("\n");
    printf("\n\t\t\t 1. Search Books");
    printf("\n");
    printf("\n\t\t\t 2. Issue Books");
    printf("\n");
    printf("\n\t\t\t 3. View Book list");
    printf("\n");
    printf("\n\t\t\t 4. Close Application");
    printf("\n");
    printf("\n\n\tENTER YOUR CHOICE :");
    switch(getch())
    {
        case '1':
            search1();
            break;
        case '2':
            issue1();
            break;
        case '3':
            view1();
            break;
        case '4':
        {
            printf("\n\n\t\t\tLIBRARY MANAGEMENT SYSTEM");
            printf("\n");
            printf("\n\t\t\tBY");
            printf("\n");
            printf("\n\t\t\tDHIKSHITA.A-19PD09");
            printf("\n");
            printf("\n\t\t\tSWATHI PRATHAA.P-19PD38");
            printf("\n");
            printf("\n\t\t\t\tTHANK YOU!!!");
            exit(0);
        }
        default:
        {
            printf("\n");
            printf("\n\n\tWrong Entry!!Please re-entered correct option");
            if(getch())
                mainmenu();
        }
    }
}
void add(void)    //function that add books
{
    int i;
    printf("\n\t\t\tSELECT CATEGORIES\t\t\t");
    printf("\n");
    printf("\n\n\t\t\t 1. Computer");
    printf("\n");
    printf("\n\t\t\t 2. Electronics");
    printf("\n");
    printf("\n\t\t\t 3. Novel Books");
    printf("\n");
    printf("\n\t\t\t 4. Mathematics");
    printf("\n");
    printf("\n\t\t\t 5. Science Book");
    printf("\n");
    printf("\n\t\t\t 6. Back to main menu");
    printf("\n");
    printf("\n\n\t\t\tENTER YOUR CHOICE:");
    scanf("%d",&s);
    if(s==6)
        mainmenu();
    fp=fopen("record.dat","ab+");//opens the file named record
    if(getdata()==1)
    {
        a.cat=cata[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);//closes the file named record
        printf("\n\t\t\tThe record is successfully saved");
        printf("Save any more?(Y / N):");
        if(getch()=='n')
            mainmenu();
        else
            add();
    }
}
void delete()    //function that delete items from file fp
{
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
        printf("\n");
        printf("\n\n\t\tEnter the Book ID to  delete:");
        scanf("%d",&d);
        fp=fopen("record.dat","rb");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id==d)
            {
                printf("\n");
                printf("\n\n\t\tThe book record is available");
                printf("\n\n\t\tBook name is %s",a.name);
                printf("\n\n\t\tRack No. is %d",a.rackno);
                f='t';
            }
        }
        if(f!='t')
        {
            printf("\n");
            printf("\n\n\t\t No record is found modify the search");
            if(getch())
            mainmenu();
        }
        if(f=='t' )
        {
            printf("\n");
            printf("\n\n\t\tDo you want to delete it?(y/n):");
            if(getch()=='y')
            {
                ft=fopen("delete.dat","wb+");  //temporary file for delete
                rewind(fp);
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.id!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,ft); //write all in temporary file except that we want to delete
                    }
                }
                fclose(ft);
                fclose(fp);
                remove("record.dat");
                rename("delete.dat","record.dat"); //copy all item from temporary file to fp except that we want to delete
                fp=fopen("record.dat","rb");
                if(f=='t')
                {
                    printf("\n");
                    printf("\n\t\tThe record is successfully deleted");
                    printf("\n");
                    printf("\n\t\tDelete another record?(y/n)");
                }
            }
            else
                mainmenu();
            another=getch();
        }
    }
        mainmenu();
}
void search()
{
    int d;
    printf("\n");
    printf("\n\n\t\t\t\tSearch Books");
    printf("\n");
    printf("\n\t\t\t 1. Search By ID");
    printf("\n");
    printf("\n\t\t\t 2. Searchss By Name");
    printf("\n");
    printf("\n\n\n\t\t  Enter Your Choice");
    fp=fopen("record.dat","rb+"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
        case '1':
        {
            printf("\n");
            printf("\n\n\t\t\tSearch Books By Id");
            printf("\n");
            printf("\n\t\tEnter the book id:");
            scanf("%d",&d);
            printf("Searching........");
            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(a.id==d)
                {
                    printf("\n");
                    printf("\n\n\t\tThe Book is available");
                    printf("\n");
                    printf("\n\t ID:%d",a.id);
                    printf("\n");
                    printf("\n\t Name:%s",a.name);
                    printf("\n");
                    printf("\n\t Author:%s ",a.Author);
                    printf("\n");
                    printf("\n\t Quantity:%d ",a.quantity);
                    printf("\n");
                    printf("\n\t Price:Rs.%d",a.Price);
                    printf("\n");
                    printf("\n\t Rack No:%d ",a.rackno);
                    printf("\n");
                    printf("\n");
                    f='t';
                }
            }
            if(f!='t')  //checks whether condition enters inside loop or not
            {
                printf("\n");
                printf("\n\n\n\t\t\t No Record Found");
            }
            printf("Try another search?(y/n)");
            if(getch()=='y')
            search();
            else
                mainmenu();
            break;
        }
    case '2':
    {
        char s[15];
        printf("\n\n\t\tSearch Books By Name");
        printf("\n");
        printf("Enter Book Name:");
        scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
            {
                printf("\n");
                printf("\n\n\t\t\tThe Book is available");
                printf("\n");
                printf("\n\n\t\t\t ID:%d",a.id);
                printf("\n");
                printf("\n\n\t\t\t Name:%s",a.name);
                printf("\n");
                printf("\n\n\t\t\t Author:%s",a.Author);
                printf("\n");
                printf("\n\n\t\t\t Quantity:%d",a.quantity);
                printf("\n");
                printf("\n\n\t\t\t Price:Rs.%d",a.Price);
                printf("\n");
                printf("\n\n\t\t\t Rack No:%d ",a.rackno);
                printf("\n");
                d++;
            }

        }
        if(d==0)
        {
            printf("\n\n\n");
            printf("\n\t\tNo Record Found");
        }
        printf("\n");
        printf("\n\n\t\t Try another search?(y/n)");
        if(getch()=='y')
        search();
        else
            mainmenu();
        break;
    }
        default :
            getch();
        search();
    }
    fclose(fp);
}
void search1()
{
    int d;
    printf("\n");
    printf("\n\n\t\t\t\tSearch Books");
    printf("\n");
    printf("\n\t\t\t 1. Search By ID");
    printf("\n");
    printf("\n\t\t\t 2. Search By Name");
    printf("\n");
    printf("\n\n\n\t\t  Enter Your Choice");
    fp=fopen("record.dat","rb+"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
        case '1':
        {
            printf("\n");
            printf("\n\n\t\t\tSearch Books By Id");
            printf("\n");
            printf("\n\t\tEnter the book id:");
            scanf("%d",&d);
            printf("Searching........");
            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(a.id==d)
                {
                    printf("\n");
                    printf("\n\n\t\tThe Book is available");
                    printf("\n");
                    printf("\n\t ID:%d",a.id);
                    printf("\n");
                    printf("\n\t Name:%s",a.name);
                    printf("\n");
                    printf("\n\t Author:%s ",a.Author);
                    printf("\n");
                    printf("\n\t Quantity:%d ",a.quantity);
                    printf("\n");
                    printf("\n\t Price:Rs.%d",a.Price);
                    printf("\n");
                    printf("\n\t Rack No:%d ",a.rackno);
                    printf("\n");
                    printf("\n");
                    f='t';
                }
            }
            if(f!='t')  //checks whether condition enters inside loop or not
            {
                printf("\n");
                printf("\n\n\n\t\t\t No Record Found");
            }
            printf("Try another search?(y/n)");
            if(getch()=='y')
            search1();
            else
                mainmenu1();
            break;
        }
    case '2':
    {
        char s[15];
        printf("\n\n\t\tSearch Books By Name");
        printf("\n");
        printf("Enter Book Name:");
        scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
            {
                printf("\n");
                printf("\n\n\t\t\tThe Book is available");
                printf("\n");
                printf("\n\n\t\t\t ID:%d",a.id);
                printf("\n");
                printf("\n\n\t\t\t Name:%s",a.name);
                printf("\n");
                printf("\n\n\t\t\t Author:%s",a.Author);
                printf("\n");
                printf("\n\n\t\t\t Quantity:%d",a.quantity);
                printf("\n");
                printf("\n\n\t\t\t Price:Rs.%d",a.Price);
                printf("\n");
                printf("\n\n\t\t\t Rack No:%d ",a.rackno);
                printf("\n");
                d++;
            }

        }
        if(d==0)
        {
            printf("\n\n\n");
            printf("\n\t\tNo Record Found");
        }
        printf("\n");
        printf("\n\n\t\t Try another search?(y/n)");
        if(getch()=='y')
        search1();
        else
            mainmenu1();
        break;
    }
        default :
            getch();
        search1();
    }
    fclose(fp);
}
void issue(void)  //function that issue books from library
{
    int t;
    printf("\n\t\t    ISSUE SECTION");
    printf("\n");
    printf("\n\t\t 1. Issue a Book");
    printf("\n");
    printf("\n\t\t 2. View Issued Book");
    printf("\n");
    printf("\n\t\t 3. Search Issued Book");
    printf("\n");
    printf("\n\t\t 4. Remove Issued Book");
    printf("\n");
    printf("Enter a Choice:");
    switch(getch())
    {
        case '1':  //issue book
        {
            int c=0;
            char another='y';
            while(another=='y')
            {
                printf("\n\n");
                printf("\n\t\t\t Issue Book section");
                printf("\n");
                printf("\n\t\t\t Enter the Book Id:");
                scanf("%d",&t);
                fp=fopen("record.dat","rb+");
                fs=fopen("Issue.dat","ab+");
                if(checkid(t)==0) //issues those which are present in library
                {
                    printf("\n");
                    printf("\n\t\t\t The book record is available");
                    printf("\n");
                    printf("\n\t\t\t There are %d unissued books in library ",a.quantity);
                    printf("\n");
                    printf("\n\t\t\t The name of book is %s",a.name);
                    printf("\n");
                    printf("\n\t\t\t Enter student name:");
                    scanf("%s",a.stname);
                    time_t t = time(NULL);
                    struct tm time = *localtime(&t);
                    a.issued.dd=time.tm_mday;
                    a.issued.mm=time.tm_mon + 1;
                    a.issued.yy=time.tm_year + 1900;
                    printf("\n");
                    printf("\t\t\tIssued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
                    printf("\n");
                    printf("\n\t\t\t The BOOK of ID %d is issued",a.id);
                    a.quantity--;
                    a.due.dd=time.tm_mday+15;   //for return date
                    a.due.mm=time.tm_mon + 1;
                    a.due.yy=time.tm_year + 1900;
                    if(a.due.dd>30)
                    {
                        a.due.mm+=a.due.dd/30;
                        a.due.dd-=30;

                    }
                    if(a.due.mm>12)
                    {
                        a.due.yy+=a.due.mm/12;
                        a.due.mm-=12;

                    }
                    printf("\n");
                    printf("\n\t\t\t To be return:%d-%d-%d",a.due.dd,a.due.mm,a.due.yy);
                    fseek(fs,sizeof(a)*(-1),1);
                    fwrite(&a,sizeof(a),1,fs);
                    fseek(fp,sizeof(a)*(-1),1);
                    fwrite(&a,sizeof(a),1,fp);
                    fclose(fs);
                    c=1;
                }
                if(c==0)
                {
                    printf("\n");
                    printf("\n\t\t\t No record found");
                }
                printf("\n");
                printf("\n\t\t\t Issue any more(y/n):");
                another=getche();
                fclose(fp);
            }

            break;
        }
        case '2':  //show issued book list
        {
            printf("\n");
            int j=4;
            printf("\n\t\t\tIssued book list");
            printf("\n");
            printf("STUDENT NAME    CATEGORY       ID    BOOK NAME    ISSUED DATE    RETURN DATE");
            fs=fopen("Issue.dat","rb");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                printf("\n %s      ",a.stname);
                printf("     %s    ",a.cat);
                printf("    %d  ",a.id);
                printf("      %s",a.name);
                printf("      %d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
                printf("     %d-%d-%d",a.due.dd,a.due.mm,a.due.yy);
                j++;
            }
            fclose(fs);
            returnfunc();
        }
        break;
        case '3':   //search issued books by id
        {
            printf("\n");
            printf("Enter Book ID:");
            int p,c=0;
            char another='y';
            while(another=='y')
            {

                scanf("%d",&p);
                fs=fopen("Issue.dat","rb");
                while(fread(&a,sizeof(a),1,fs)==1)
                {
                    if(a.id==p)
                    {
                        issuerecord();
                        printf("\n");
                        printf("Press any key.......");
                        getch();
                        issuerecord();
                        c=1;
                    }

                }
                fclose(fs);
                if(c==0)
                {
                    printf("\n");
                    printf("\n\t No Record Found");
                }
                printf("\n");
                printf("\n\t Try Another Search?(y/n)");
                another=getch();
            }
        }
        break;
        case '4':  //remove issued books from list
        {
            int b;
            FILE *fg;  //declaration of temporary file for delete
            char another='y';
            while(another=='y')
            {
                printf("\n\t\t");
                printf("\n\t Enter book id to remove:");
                scanf("%d",&b);
                fs=fopen("Issue.dat","rb+");
                while(fread(&a,sizeof(a),1,fs)==1)
                {
                    if(a.id==b)
                    {
                        issuerecord();
                        f='t';
                    }
                    if(f=='t')
                    {
                        printf("\n");
                        printf("\n\tDo You Want to Remove it?(y/n)");
                        if(getch()=='y')
                        {
                            fg=fopen("record1.dat","wb+");
                            rewind(fs);
                            while(fread(&a,sizeof(a),1,fs)==1)
                            {
                                if(a.id!=b)
                                {
                                    fseek(fs,0,SEEK_CUR);
                                    fwrite(&a,sizeof(a),1,fg);
                                }
                            }
                            fclose(fs);
                            fclose(fg);
                            remove("Issue.dat");
                            rename("record1.dat","Issue.dat");
                            printf("\n");
                            printf("\n\t The issued book is removed from list");

                        }

                    }
                    if(f!='t')
                    {
                        printf("\n");
                        printf("\n\t\t No Record Found");
                    }
                }
                printf("\n");
                printf("\n\t Delete any more?(y/n)");
                another=getch();
            }
        }
        default:
        printf("\n");
        printf("\n\n\tWrong Entry!!");
        getch();
        issue();
        break;
    }
    printf("\n");
    returnfunc();
}
void issue1(void)  //function that issue books from library
{
    int t;
    printf("\n\t\t    ISSUE SECTION");
    printf("\n");
    printf("\n\t\t 1. View Issued Book");
    printf("\n");
    printf("\n\t\t 2. Search Issued Book");
    printf("\n");
    printf("Enter a Choice:");
    switch(getch())
    {
        case '1':  //show issued book list
        {
            printf("\n");
            int j=4;
            printf("\n\t\t\tIssued book list");
            printf("\n");
            printf("STUDENT NAME    CATEGORY       ID    BOOK NAME    ISSUED DATE    RETURN DATE");
            fs=fopen("Issue.dat","rb+");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                printf("\n %s      ",a.stname);
                printf("     %s    ",a.cat);
                printf("    %d  ",a.id);
                printf("      %s",a.name);
                printf("      %d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
                printf("     %d-%d-%d",a.due.dd,a.due.mm,a.due.yy);
                j++;
            }
            fclose(fs);
            returnfunc1();
        }
        break;
        case '2':   //search issued books by id
        {
            printf("\n");
            printf("Enter Book ID:");
            int p,c=0;
            char another='y';
            while(another=='y')
            {

                scanf("%d",&p);
                fs=fopen("Issue.dat","rb+");
                while(fread(&a,sizeof(a),1,fs)==1)
                {
                    if(a.id==p)
                    {
                        issuerecord();
                        printf("\n");
                        printf("Press any key.......");
                        getch();
                        issuerecord();
                        c=1;
                    }

                }
                fclose(fs);
                if(c==0)
                {
                    printf("\n");
                    printf("\n\t No Record Found");
                }
                printf("\n");
                printf("\n\t Try Another Search?(y/n)");
                another=getch();
            }
        }
        break;
    }
}
void view(void)  //show the list of book persists in library
{
    int i=0,j;
    printf("\n");
    printf("\n\t\tBook List");
    printf("\n");
    printf("CATEGORY\tID\tBOOK NAME   AUTHOR\tQTY \tPRICE\tRackNo ");
    j=4;
    fp=fopen("record.dat","rb+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        printf("\n%s",a.cat);
        printf("\t%d",a.id);
        printf("\t%s",a.name);
        printf("\t    %s",a.Author);
        printf("\t%d",a.quantity);
        printf("\t%d",a.Price);
        printf("\t%d",a.rackno);
        j++;
        i=i+a.quantity;
    }
    printf("\n");
    printf("\n\t Total Books =%d",i);
    fclose(fp);
    printf("\n");
    returnfunc();
}
void view1(void)  //show the list of book persists in library
{
    int i=0,j;
    printf("\n");
    printf("\n\t\tBook List");
    printf("\n");
    printf("CATEGORY\tID\tBOOK NAME   AUTHOR\tQTY \tPRICE\tRackNo ");
    j=4;
    fp=fopen("record.dat","rb+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        printf("\n%s",a.cat);
        printf("\t%d",a.id);
        printf("\t%s",a.name);
        printf("\t    %s",a.Author);
        printf("\t%d",a.quantity);
        printf("\t%d",a.Price);
        printf("\t%d",a.rackno);
        j++;
        i=i+a.quantity;
    }
    printf("\n");
    printf("\n\t Total Books =%d",i);
    fclose(fp);
    printf("\n");
    returnfunc1();
}
void edit(void)  //edit information about book
{
    int c=0;
    int d,e;
    printf("\n");
    printf("\n\t\t Edit Books Section");
    char another='y';
    while(another=='y')
    {
        printf("\n");
        printf("\n\t\t Enter Book Id to be edited:");
        scanf("%d",&d);
        fp=fopen("record.dat","rb+");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(checkid(d)==0)
            {
                printf("\n");
                printf("\n\t The book is available");
                printf("\n");
                printf("\n\t The Book ID:%d",a.id);
                printf("\n");
                printf("\n\t Enter new name:");
                scanf("%s",a.name);
                printf("\n");
                printf("\n\t Enter new Author:");
                scanf("%s",a.Author);
                printf("\n");
                printf("\n\t Enter new quantity:");
                scanf("%d",&a.quantity);
                printf("\n");
                printf("\n\t Enter new price:");
                scanf("%d",&a.Price);
                printf("\n");
                printf("\n\t Enter new rackno:");
                scanf("%d",&a.rackno);
                printf("\n");
                printf("\n\t The record is modified");
                fseek(fp,ftell(fp)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {
                printf("\n\n");
                printf("\n\t No record found");
            }
        }
        printf("\n");
        printf("\n\t Modify another Record?(y/n)");
        another=getch() ;
    }
    returnfunc();
}
void returnfunc(void)
{
    {
        printf("\n\t Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
void returnfunc1(void)
{
    {
        printf("\n\t Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu1();
    else
    goto a;
}
int getdata()
{
    int t;
    printf("\n\n\t\t");
    printf("\t\t Enter the Information Below");
    printf("\n");
    printf("\n");
    printf("\n\t Category:");
    printf("%s",cata[s-1]);
    printf("\n");
    printf("\n\n\t\t Book ID:\t");
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
        printf("\n");
        printf("\n\tThe book id already exists\a");
        getch();
        mainmenu();
        return 0;
    }
    a.id=t;
    printf("\t\tBook Name:");
    scanf("%s",a.name);
    printf("\t\t Author:");
    scanf("%s",a.Author);
    printf("\t\t Quantity:");
    scanf("%d",&a.quantity);
    printf("\t\t Price:");
    scanf("%d",&a.Price);
    printf("\t\t Rack No:");
    scanf("%d",&a.rackno);
    return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.id==t)
    return 0;  //returns 0 if book exits
    return 1; //return 1 if it not
}
void Password(void) //for password option
{

    char ch,pass[10];
    int i=0,j;
    printf("\n\t\t\tWELCOME TO LIBRARY MANAGEMENT SYSTEM!!!");
    printf("\n");
    printf("\n");
    printf("\n\tEnter Password:");
    while(ch!=13)
    {
        ch=getch();

        if(ch!=13 && ch!=8){
        putch('*');
        pass[i] = ch;
        i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(pass,password)==0)
    {
        printf("\n");
        printf("\n\n\t  Password match");
        printf("\n");
        printf("\n\n\t  Press any key to continue.....");
        getch();
        mainmenu();
    }
    else
    {
        printf("\n");
        printf("\n\n\t Warning!! Incorrect Password");
        getch();
        Password();
    }
}
void issuerecord()  //display issued book's information
{
    printf("\n");
    printf("\n\n\t\t The Book has taken by Mr/Ms. %s",a.stname);
    printf("\n");
    printf("\n\n\t\t Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
    printf("\n");
    printf("\n\n\t\t Returning Date:%d-%d-%d",a.due.dd,a.due.mm,a.due.yy);
}
int main()
{
    int ch;
    printf("\n Enter an option");
    printf("\n\t\t1.ADMIN\n\t\t2.USER\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:Password();
        case 2:mainmenu1();
    }
    getch();
    return 0;
}

