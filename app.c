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
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
void get_mac();
void get_ip();
void edit();
void Sysinfo();

int main()
{
    char a[100];
    printf("__________________Command Line Text Editor__________________\n\n");
    dt();
    printf("Type \"help\" for more things!\n\n");
    do
    {
        printf(">>> ");
        fflush(stdin);
        scanf("%s", a);
        if (strcmp(a, "sysinfo") == 0)
        {
            Sysinfo();
        }
        else if(strcmp(a, "read") == 0)
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
    scanf("%s", a);
    int fd = open(a, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        printf("Error\n");
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
            write(fd, &ch, 1);
        }
    }
    close(fd);
    printf("\nSuccessfully Appended\n");
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
    system("clear");
    printf("Command Line Text Editor\n\n");
    dt();
    printf("Type \"help\" for more things!\n\n");
}

void removes()
{
    char a[100];
    int m;
    scanf("%s", a);
    m = unlink(a);
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
    char c;
    scanf("%s", a);
    scanf("%s", b);
    int in = open(a, O_RDONLY);
    int out = open(b, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(in == -1 || out == -1)
    {
        printf("The file is not found\n");
        return;
    }
    else
    {
        while(read(in, &c, 1) == 1)
        {
            write(out, &c, 1);
        }
        close(in);
        close(out);
        printf("\nSuccessfully copied\n");
    }

}

void cknow()
{
    char a[100], cha;
    int c, count=0;
    scanf("%s", a);
    c = getchar();
    scanf("%c", &cha);
    int fd = open(a, O_RDONLY);
    if(fd == -1)
    {
        printf("Error : cannot open %s\n", a);
        return;
    }
    else
    {
        while(read(fd, &c, 1) == 1)
        {
            if(c == cha)
            {
                count++;
            }
        }
        close(fd);
        printf("No. of times %c repeated is = %d\n",  cha, count);
    }
}

void lknow()
{
    char a[100], cha;
    int count=0;
    char c;
    scanf("%s", a);
    int fd = open(a, O_RDONLY);
    if(fd == -1)
    {
        printf("Eror : cannot open file %s\n", a);
        return;
    }
    else
    {
        while(read(fd, &c, 1) == 1)
        {
            if(c == '\n')
            {
                count++;
            }
        }
        printf("No. of lines = %d\n", count);
        close(fd);
    }
}

void ccount() 
{
    char a[100], cha;
    int count = 0;
    char c;
    scanf("%s", a);
    int fd = open(a, O_RDONLY);
    if (fd == -1) 
    {
        printf("Error : cannot open file %s\n", a);
    } 
    else 
    {
        while (read(fd, & c, 1) == 1) 
        {
            if (c != ' ' && c != '\n') 
            {
                count++;
            }
        }
        printf("No. of characters in file is = %d\n", count);
    }
    close(fd);
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
    scanf("%s", fileName);
    int lineNo;
    scanf("%d", & lineNo);
    int p = open(fileName, O_RDONLY);
    int q = open("temp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (p == -1 || q == -1) 
    {
        printf("The file is not found\n");
    } 
    else 
    {
        char c;
        int count = 1;
        while (count < lineNo && read(p, & c, 1) == 1) 
        {
            write(q, & c, 1);
            if (c == '\n')
                count++;
        }
        fflush(stdin);
        printf("Enter ~ to exit from writing\n");
        printf("Start writing: \n");
        char ch;
        while (ch != '~') 
        {
            ch = getchar();
            if (ch != '~') 
            {
                write(q, & ch, 1);
            }
        }
        while (read(p, &c, 1) == 1 && c != '\n');
        while (read(p, &c, 1) == 1) 
        {
            write(q, &c, 1);
        }
        close(p);
        close(q);
        int m = remove(fileName);
        m = rename("temp", fileName);
    }
}

void get_mac()
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strcpy(s.ifr_name, "eth0");
    if (ioctl(fd, SIOCGIFHWADDR, &s) == 0) 
    {
        int i;
        printf("MAC address : ");
        for (i = 0; i < 6; ++i)
        {
            printf("%02x", (unsigned char) s.ifr_addr.sa_data[i]);
            if (i < 5)
                printf(":");
        }
        printf("\n");
        return;
    }
    return;
}

void get_ip()
{
    int n;
    struct ifreq ifr;
    char array[] = "eth0";
    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //display result
    printf("IP Address : %s\n", inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
}

void Sysinfo()
{
    printf("Number of processors configured : %ld\n", sysconf(_SC_NPROCESSORS_CONF));
    printf("Number of processors available  : %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
    get_mac();
    get_ip();
}

void help()
{
    printf("\n");
    printf("You can enter the following commands:\n\n");
    printf("sysinfo  >>> To get important system information\n");
    printf("write  >>> To write to a file\t\t\t\tSyntax: \"write filename.txt\"\n");
    printf("read   >>> To read from a file\t\t\t\tSyntax: \"read filename.txt\"\n");
    printf("edit   >>> To edit a particular line from a file\tSyntax: \"edit filename.txt line_no\"\n");
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
    printf("replace>>> To find and replace \t\t\t\tSyntax: \"replace FileName.txt oldWord newWord\"\n");
    printf("exit   >>> To exit\n");
    printf("\n");
}

void exits()
{
    exit(1);
}