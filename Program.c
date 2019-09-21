#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
void addbook();
void deletebook();
void searchbook();
void updatebook();
void displaybooks();
void issuebook();
void menu();
struct book_detail
{
    int serial;
    char name[30];
    char isbn[15];
    char author[30];
    char edition[10];
    int Is_reserved;
};
int main()
{
    printf("***Welcome to Haider's Library***\n\n\n");
    menu();
}
void menu()
{
    int choose;
    printf("Select an option:\n");
    printf("1: Add Book\n");
    printf("2: Modify/Update Book\n");
    printf("3: Search Book\n");
    printf("4: Delete Book\n");
    printf("5: Issue Book\n");
    printf("6: Display all Books\n");
    printf("7: Exit\n\n");
    scanf("%d",&choose);
    switch (choose)
    {
        case 1:
            system("cls");
            addbook();
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            updatebook();
            system("cls");
            menu();
            break;
        case 3:
            system("cls");
            searchbook();
            system("cls");
            menu();
            break;
        case 4:
            system("cls");
            deletebook();
            system("cls");
            menu();
            break;
        case 5:
            system("cls");
            issuebook();
            system("cls");
            menu();
            break;
        case 6:
            system("cls");
            displaybooks();
            system("cls");
            menu();
            break;
        case 7:
            exit(0);
        default:
            system("cls");
            printf("Invalid Input\n\n");
            menu();
            break;
    }
}
void addbook()
{
    struct book_detail x;
    FILE *openfile=fopen("Library.txt","a");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        printf("Enter Book Serial Number:\n");
        scanf("%d", &x.serial);
        printf("Enter Book Name: \n");
        scanf("%s", x.name);
        printf("Enter Book ISBN: \n");
        scanf("%s", x.isbn);
        printf("Enter Author Name:\n");
        scanf("%s", x.author);
        printf("Enter Edition:\n");
        scanf("%s", x.edition);
        x.Is_reserved=0;
        fprintf(openfile, "%d %s %s %s %s %d\n", x.serial, x.name, x.isbn, x.author, x.edition, x.Is_reserved);
        fclose(openfile);
        printf("\nThe Book is Successfully Added.");
        getch();
    }
}
void deletebook()
{
    struct book_detail x;
    int delchk,ifnot=0;
    FILE *openfile=fopen("Library.txt","r");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        printf("Enter Book Serial Number to Delete:\n");
        scanf("%d",&delchk);
        while(!feof(openfile))
        {
            fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
            if(x.serial==delchk)
            {
                printf("\n\nThe Book with serial number %d is Available\n",x.serial);
                ifnot=1;
            }
        }
        if(ifnot==1)
        {
            FILE *opendummy=fopen("dummy.txt","w");
            rewind(openfile);
            while(!feof(openfile))
            {
                fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
                if(x.serial!=delchk)
                {
                    fprintf(opendummy, "%d %s %s %s %s \n", x.serial, x.name, x.isbn, x.author, x.edition);
                }
            }
            fclose(opendummy);
            fclose(openfile);
            remove("Library.txt");
            rename("dummy.txt","Library.txt");
            printf("\nThe Book is Successfully Deleted.");
            getch();
        }
        if(ifnot==0)
        {
            printf("\n\nNo Book with this ID found\n");
            getch();
            return;
        }
    }
}
void searchbook()
{
    struct book_detail x;
    int ifnot=0;
    FILE *openfile=fopen("Library.txt","rb+");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        char search_choice,again;
        printf("Search Book By:\n");
        printf("1: ISBN\n");
        printf("2: Book Name\n");
        printf("3: Author Name\n\n");
        fflush(stdin);
        scanf("%c",&search_choice);
        switch (search_choice)
        {
            case '1':
            {
                char isbnchk[15];
                fflush(stdin);
                printf("\nEnter Book ISBN:\n");
                gets(isbnchk);
                rewind(openfile);
                while(!feof(openfile))
                {
                    fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
                    if(strcmp(x.isbn,isbnchk)==0)
                    {
                        printf("\nThe Book with serial number %d is Available\n",x.serial);
                        printf("Book Name: %s\n",x.name);
                        printf("Author Name: %s\n",x.author);
                        printf("ISBN: %s\n",x.isbn);
                        printf("Edition: %s\n",x.edition);
                        if(x.Is_reserved==0)
                        {
                            printf("The Book is not Reserved.\n");
                        }
                        if(x.Is_reserved==1)
                        {
                            printf("The Book is Reserved.\n");
                        }
                        fclose(openfile);
                        ifnot=1;
                        getch();
                    }
                    if(ifnot==1)
                    {
                        printf("\nDo You Want to search another Book (Y/N): ");
                        fflush(stdin);
                        scanf("%c",&again);
                        if(again=='y' || again=='Y')
                        {
                            searchbook();
                            return;
                        }
                        else
                        {
                            return;
                        }
                    }
                }
                if(ifnot==0)
                {
                    printf("\nNo Book with this ISBN found\n");
                    getch();
                    printf("\nDo You Want to search another Book (Y/N): ");
                    fflush(stdin);
                    scanf("%c",&again);
                    if(again=='y' || again=='Y')
                    {
                        searchbook();
                        return;
                    }
                    else
                    {
                        return;
                    }
                }
                break;
            }
            case '2':
            {
                char namechk[30];
                fflush(stdin);
                printf("\nEnter Book Name:\n");
                gets(namechk);
                rewind(openfile);
                while(!feof(openfile))
                {
                    fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
                    if(strcmp(x.name,namechk)==0)
                    {
                        printf("\nThe Book with serial number %d is Available\n",x.serial);
                        printf("Book Name: %s\n",x.name);
                        printf("Author Name: %s\n",x.author);
                        printf("ISBN: %s\n",x.isbn);
                        printf("Edition: %s\n",x.edition);
                        if(x.Is_reserved==0)
                        {
                            printf("The Book is not Reserved.\n");
                        }
                        if(x.Is_reserved==1)
                        {
                            printf("The Book is Reserved.\n");
                        }
                        fclose(openfile);
                        ifnot=1;
                        getch();
                    }
                    if(ifnot==1)
                    {
                        printf("\nDo You Want to search another Book (Y/N): ");
                        fflush(stdin);
                        scanf("%c",&again);
                        if(again=='y' || again=='Y')
                        {
                            searchbook();
                            return;
                        }
                        else
                        {
                            return;
                        }
                    }
                }
                if(ifnot==0)
                {
                    printf("\nNo Book with this Name found\n");
                    getch();
                    printf("\nDo You Want to search another Book (Y/N): ");
                    fflush(stdin);
                    scanf("%c",&again);
                    if(again=='y' || again=='Y')
                    {
                        searchbook();
                        return;
                    }
                    else
                    {
                        return;
                    }
                }
                break;
            }
            case '3':
            {
                char authorchk[30];
                fflush(stdin);
                printf("\nEnter Book Author Name:\n");
                gets(authorchk);
                rewind(openfile);
                while(!feof(openfile))
                {
                    fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
                    if(strcmp(x.author,authorchk)==0)
                    {
                        printf("\nThe Book with serial number %d is Available\n",x.serial);
                        printf("Book Name: %s\n",x.name);
                        printf("Author Name: %s\n",x.author);
                        printf("ISBN: %s\n",x.isbn);
                        printf("Edition: %s\n",x.edition);
                        if(x.Is_reserved==0)
                        {
                            printf("The Book is not Reserved.\n");
                        }
                        if(x.Is_reserved==1)
                        {
                            printf("The Book is Reserved.\n");
                        }
                        fclose(openfile);
                        ifnot=1;
                        getch();
                    }
                    if(ifnot==1)
                    {
                        printf("\nDo You Want to search another Book (Y/N): ");
                        fflush(stdin);
                        scanf("%c",&again);
                        if(again=='y' || again=='Y')
                        {
                            searchbook();
                            return;
                        }
                        else
                        {
                            return;
                        }
                    }
                }
                if(ifnot==0)
                {
                    printf("\nNo Book with this Author Name found.\n");
                    getch();
                    printf("\nDo You Want to search another Book (Y/N): ");
                    fflush(stdin);
                    scanf("%c",&again);
                    if(again=='y' || again=='Y')
                    {
                        searchbook();
                        return;
                    }
                    else
                    {
                        return;
                    }
                }
                break;
            }
            default:
            {
                printf("\nWrong Entry.");
                getch();
                break;
            }
        }
    return;
    }
}
void updatebook()
{
    struct book_detail x,y;
    int changechk,ifnot=0;
    FILE *openfile=fopen("Library.txt","rb+");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        printf("Enter Book Serial Number to Update:\n");
        scanf("%d",&changechk);
        while(!feof(openfile))
        {
            fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
            if(ifnot!=1)
            {
                if(x.serial==changechk)
                {
                    printf("\n\nThe Book with serial number %d is Available\n",x.serial);
                    ifnot=1;
                }
            }
        }
        if(ifnot==1)
        {
            printf("Enter New Book Name: \n");
            scanf("%s", y.name);
            printf("Enter New Book ISBN: \n");
            scanf("%s", y.isbn);
            printf("Enter New Author Name:\n");
            scanf("%s", y.author);
            printf("Enter New Edition:\n");
            scanf("%s", y.edition);
            FILE *opendummy=fopen("dummy2.txt","w");
            rewind(openfile);
            while(!feof(openfile))
            {
                fscanf(openfile,"%d %s %s %s %s",&x.serial,x.name,x.author,x.isbn,x.edition);
                if(x.serial!=changechk)
                {
                    fprintf(opendummy, "%d %s %s %s %s \n", x.serial, x.name, x.isbn, x.author, x.edition);
                }
                if(x.serial==changechk)
                {
                    fprintf(opendummy, "%d %s %s %s %s \n", y.serial, y.name, y.isbn, y.author, y.edition);
                }
            }
            fclose(opendummy);
            fclose(openfile);
            remove("Library.txt");
            rename("dummy2.txt","Library.txt");
            printf("\nThe Book is Successfully Updated.");
            getch();
        }
        if(ifnot==0)
        {
            printf("\n\nNo Book with this ID found\n");
            getch();
            return;
        }
    }
    return;
}
void displaybooks()
{
    struct book_detail x;
    FILE *openfile=fopen("Library.txt","r");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        printf("Sr.\tName\tISBN\t\tAuthor\tEdition\t\tStatus\n");
        while(!feof(openfile))
        {
            if((fscanf(openfile,"%d %s %s %s %s %d",&x.serial,x.name,x.author,x.isbn,x.edition,&x.Is_reserved))!=EOF)
            {
                fscanf(openfile,"%d %s %s %s %s %d",&x.serial,x.name,x.author,x.isbn,x.edition,&x.Is_reserved);
                printf("\n%d\t%s\t%s\t%s\t%s\t\t",x.serial,x.name,x.author,x.isbn,x.edition);
                if(x.Is_reserved==0)
                {
                    printf("not Reserved.");
                }
                if(x.Is_reserved==1)
                {
                    printf("Reserved.");
                }
            }
        }
        getch();
        return;
    }
}
void issuebook()
{
    struct book_detail x;
    int issbook,ifnot=0;
    FILE *openfile=fopen("Library.txt","r");
    if(openfile == NULL)
    {
        printf("No File Found");
        getch();
        return;
    }
    else
    {
        printf("Enter Book Serial Number to Issue:\n");
        scanf("%d",&issbook);
        while(!feof(openfile))
        {
            fscanf(openfile,"%d %s %s %s %s %d",&x.serial,x.name,x.author,x.isbn,x.edition,&x.Is_reserved);
            if(ifnot!=1)
            {
                if(x.serial==issbook)
                {
                    printf("\n\nThe Book with serial number %d is Available\n",x.serial);
                    x.Is_reserved=1;
                    fprintf(openfile,"%d",x.Is_reserved);
                    ifnot=1;
                }
            }
        }
        if(ifnot==1)
        {
            printf("Book Issued Successfully.");
            getch();
            system("cls");
            menu();
        }
    }
}
