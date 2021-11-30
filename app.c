#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUFFER_SIZE 1000

void Read();
void Write();
void append();
void clear();
void help();
void dt();
void exits();
void startscreen();
void removes();
void renames();
void cdir();
void copy();
void cknow();
void lknow();
void ccount();
void replace();
void replaceAll(char *str, const char *oldWord, const char *newWord);
void edit();

int main(){

    char a[100];
    printf("__________________Command Line Text Editor__________________\n\n");

    dt();
    printf("Type \"help\" for more things!\n\n");

    do
    {
        printf(">>> ");
        fflush(stdin);
        scanf("%s", a);
        if(strcmp(a, "read") == 0)
        {
            Read();
        }
        else if(strcmp(a, "write") == 0)
        {
            Write();
        }
        else if(strcmp(a, "append") == 0)
        {
            append();
        }
        else if(strcmp(a, "clr") == 0)
        {
            clear();
        }
        else if(strcmp(a, "help") == 0)
        {
            help();
        }
        else if(strcmp(a, "dt") == 0)
        {
            dt();
        }
        else if(strcmp(a, "stscr") == 0)
        {
            startscreen();
        }
        else if(strcmp(a, "remove") == 0)
        {
            removes();
        }
        else if(strcmp(a, "rename") == 0)
        {
            renames();
        }
        else if(strcmp(a, "cdir") == 0)
        {
            cdir();
        }
        else if(strcmp(a, "copy") == 0)
        {
            copy();
        }
        else if(strcmp(a, "cknow") == 0)
        {
            cknow();
        }
        else if(strcmp(a, "lknow") == 0)
        {
            lknow();
        }
        else if(strcmp(a, "ccount") == 0)
        {
            ccount();
        }
        else if(strcmp(a, "exit") == 0)
        {
            exits();
        }
        else if(strcmp(a, "replace")==0)
        {
            replace();
        }
        else if(strcmp(a, "edit") == 0)
        {
            edit();
        }
        else
        {
            printf("Enter only stated things in help\n");
        }
    }while(strcmp(a,"exit"));
    return 0;
}

void Read()
{
    char a[100];
    scanf("%s", a);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    char c;
    int fd = open(a, O_RDONLY);
    if(fd == -1)
    {
        printf("\nError\n");
        return;
    }
    printf("\n");
    while(read(fd, &c, 1) == 1)
        printf("%c", c);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    close(fd);
    printf("\nSuccessfully Read\n");
}

void Write()
{
    char a[100];
    scanf("%s", a);
    fflush(stdin);
    int fd = open(a, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        printf("Error\n");
        return;
    }
    printf("Enter ~ to exit from writing\n");
    printf("Start writing: \n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    char ch;
    while(ch != '~')
    {
        ch = getchar();
        if(ch != '~')
            write(fd, &ch, 1);
    }
    close(fd);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("Successfully Written\n");
}

void append()
{
    char a[100];
    FILE *p;
    scanf("%s", a);
    p = fopen(a, "a");
    if(p == NULL)
    {
        printf("Error");
        return;
    }
    printf("Enter ~ to exit from writing\n");
    printf("Start writing: \n");
    char ch;
    while(ch != '~')
    {
        ch = getchar();
        if(ch != '~')
        {
            fputc(ch, p);
        }
    }
    fclose(p);
    printf("\n\nSuccessfully Appended\n");
}

void clear()
{
    system("clear");
}

void dt()
{
    time_t tt = time(NULL);
    printf("%s", ctime(&tt));
}

void startscreen()
{
    system("cls");
    printf("Command Line Text Editor\n\n");

    dt();
    printf("Type \"help\" for more things!\n\n");
}

void removes()
{
    char a[100];
    int m;
    scanf("%s", a);
    m = remove(a);
    if(m == 0)
    {
        printf("Successfully removed a file\n");
    }
    else
    {
        printf("Error in removing please check if the file exists in directory\n");
    }
}

void renames()
{
    char a[100], b[100];
    int m;
    scanf("%s", a);
    scanf("%s", b);
    m = rename(a, b);
    if(m == 0)
    {
        printf("Successfully renamed a file\n");
    }
    else
    {
        printf("Error in removing please check if the file exists in directory\n");
    }

}


void cdir()
{
    char a[100];
    printf("Your Directory:\n");
    system("dir");
}

void copy()
{
    char a[100], b[100];
    int c;
    FILE *p, *q;
    scanf("%s", a);
    scanf("%s", b);
    p = fopen(a, "r");
    q = fopen(b, "a");
    if(p == NULL )
    {
        printf("The file is not found\n");
    }
    else
    {
        c = fgetc(p);
        while(c != EOF)
        {
            fputc(c, q);
            c = fgetc(p);
        }
        fclose(p);
        fclose(q);
        printf("\nSuccessfully copied\n");
    }

}

void cknow()
{
    char a[100], cha;
    int c, count=0;
    FILE *p;
    scanf("%s", a);
    fflush(stdin);
    printf("\nEnter the character to search: ");
    scanf("%c", &cha);
    p = fopen(a, "r");
    if(p == NULL)
    {
        printf("The file is not found\n");
    }
    else
    {
        c = fgetc(p);
        while(c != EOF)
        {
            if(c == cha)
            {
                count++;
            }
            c = fgetc(p);
        }
        fclose(p);
        printf("No. of times %c repeated is = %d\n",  cha, count);
    }
}

void lknow()
{
    char a[100], cha;
    int c, count=0;
    FILE *p;
    scanf("%s", a);
    p = fopen(a, "r");
    if(p == NULL)
    {
        printf("The file is not found\n");
    }
    else
    {
        c = fgetc(p);
        while(c != EOF)
        {
            if(c == '\n')
            {
                count++;
            }
            c = fgetc(p);
        }
        fclose(p);
        printf("No. of lines = %d\n", count);
    }

}

void ccount()
{
    char a[100], cha;
    int c, count=0;
    FILE *p;
    scanf("%s", a);
    p = fopen(a, "r");
    if(p == NULL)
    {
        printf("The file is not found\n");
    }
    else
    {
        c = fgetc(p);
        while(c != EOF)
        {
            if(c != ' ' && c != '\n')
            {
                count++;
            }
            c = fgetc(p);
        }
        fclose(p);
        printf("No. of characters in file is = %d\n", count);
    }
}


void replace()
{
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    char buffer[BUFFER_SIZE];
    char oldWord[100], newWord[100];
    scanf("%s", path);
    scanf("%s", oldWord);
    scanf("%s", newWord);
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 
    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        // Replace all occurrence of word from current line
        replaceAll(buffer, oldWord, newWord);

        // After replacing write it to temp file.
        fputs(buffer, fTemp);
    }
      /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);
    /* Delete original source file */
    remove(path);
    /* Rename temp file as original file */
    rename("replace.tmp", path);
    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);
}

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    owlen = strlen(oldWord);
    // Fix: If oldWord and newWord are same it goes to infinite loop
    if (!strcmp(oldWord, newWord)) 
    {
        return;
    }
    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Backup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}

void edit()
{
    char fileName[100];
    scanf("%s",fileName);
    int lineNo;
    scanf("%d",&lineNo);
    FILE* p,*q;
    p=fopen(fileName,"r");
    q=fopen("temp","w");
    if(p == NULL )
    {
        printf("The file is not found\n");
    }
    else
    {
        char c;
        c = fgetc(p);
        int count=1;
        while(c != EOF && count<=lineNo)
        {
            fputc(c, q);
            if(c=='\n')
                count++;
            c = fgetc(p);
        }
        fflush(stdin);
        printf("Enter ~ to exit from writing\n");
        printf("Start writing: \n");
        char ch;
        while(ch != '~')
        {
            ch = getchar();
            if(ch != '~')
            {
            fputc(ch, q);
            }
        }
        c = fgetc(p);
        while(c!='\n'&& c!=EOF)
            c=fgetc(p);
        while(c != EOF)
        {
            fputc(c, q);
            c = fgetc(p);
        }
        fclose(p);
        fclose(q);
        int m=remove(fileName);
        m = rename("temp",fileName);
    }
}

void help()
{
    printf("\n");
    printf("You can enter the following commands:\n\n");
    printf("write  >>> To write to a file\t\t\t\tSyntax: \"write filename.txt\"\n");
    printf("read   >>> To read from a file\t\t\t\tSyntax: \"read filename.txt\"\n");
    printf("append >>> To append a file\t\t\t\tSyntax: \"append filename.txt\"\n");
    printf("remove >>> To remove a file\t\t\t\tSyntax: \"remove filename.txt\"\n");
    printf("rename >>> To rename a file\t\t\t\tSyntax: \"rename oldFileName.txt newFileName.txt\"\n");
    printf("clr    >>> To clear the screen\n");
    printf("dt     >>> To show date and time\n");
    printf("stscr  >>> To show start screen\n");
    printf("cdir   >>> To see the directory(location) and files\n");
    printf("copy   >>> To copy one file to new file\t\t\tSyntax: \"copy file1.txt file2.txt\"\n");
    printf("cknow  >>> To know character count\t\t\tSyntax: \"cknow fileName.txt character\"\n");
    printf("lknow  >>> To get number of lines\t\t\tSyntax: \"lknow FileName.txt\"\n");
    printf("replace>>> To find and replace \t\t\tSyntax: \"replace FileName.txt oldWord newWord\"\n");

    printf("exit   >>> To exit\n");
    printf("\n");
}

void exits()
{
    exit(1);
}