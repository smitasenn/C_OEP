#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
/*<stdio.h>: This header file stands for "standard input/output" and provides functions for input and output operations, such as reading from and writing to files, printing to the console, etc.

<string.h>: This header file provides various string manipulation functions, including functions for string copying, concatenation, comparison, searching, and more.

<stdlib.h>: This header file includes functions for performing general utility functions, such as memory allocation and deallocation (malloc, free), random number generation (rand, srand), sorting and searching arrays, and other general-purpose functions.

<math.h>: This header file contains mathematical functions and constants. It includes functions like trigonometric operations (sin, cos, tan), logarithmic operations (log, exp), rounding (round, floor, ceil), and more.

<time.h>: This header file provides functions for manipulating date and time. It includes functions for getting the current time (time), formatting time (strftime), and performing various time-related calculations.

<unistd.h>: This header file provides access to various POSIX (Portable Operating System Interface) functions, including system calls, file and directory operations, process management, and other low-level operations. It includes functions like fork (creating a new process), exec (executing a new program), and sleep (suspending the execution for a specified number of seconds).*/
// structure to store songs from file to structured array
typedef struct song_list
{
        int song_id;
        char song_name[25];
        char singer_name[20];
        int no_of_likes;
        char album[25];
        char year[4];
        int time;
} sl;
// structure to create playlist
typedef struct node
{
        char sname[25];
        char artist[20];
        char albname[20];
        struct node *next;
} cp;
cp *first = NULL;

// colouring functions
void white()
{
        printf("\033[0;37m");
};
void red()
{
        printf("\033[0;31m");
};
void reset()
{
        printf("\033[0m");
};

// display playlist
void display_playlist()
{
        cp *ptr;
        if (first == NULL)
        {
                printf("\n\n*****************  No Songs In Playlist To Display  ******************\n\n");
                return;
        }
        else
        {
                ptr = first;
                printf("%-25s%-20s%-25s%\n", "|Song Name|", "|Artist Name|", "|Album Name|");
                while (ptr != NULL)
                {
                        printf("%-25s", ptr->sname);

                        printf("%-20s", ptr->artist);

                        printf("%-25s", ptr->albname);

                        ptr = ptr->next;
                        printf("\n");
                }
        }
}

// add song in playlist
void add_song()
{

        cp *temp, *ptr;

        temp = (struct node *)malloc(sizeof(struct node));

        if (temp == NULL)
        {
                printf("nOut of Memory Space:n");
                return;
        }

        printf("Enter Track Name:");
        scanf("%s", temp->sname);

        printf("Enter Artist Name:");
        scanf("%s", temp->artist);

        printf("Enter Album Name:");
        scanf("%s", temp->albname);

        temp->next = NULL;
        if (first == NULL)
        {
                first = temp;
        }
        else
        {
                ptr = first;
                while (ptr->next != NULL)
                {
                        ptr = ptr->next;
                }
                ptr->next = temp;
        }
}

// remove song using position
void remove_song()
{
        int i, pos;
        char rsong;
        cp *temp, *ptr;
        if (first == NULL)
        {
                printf("\n\n||******************************** NO ~ SONG ~ IN ~ PLAYLIST ********************************||\n\n\n\n");
        }
        else
        {
                printf("Song Position To Remove : ");
                scanf("%d", &pos);
                if (pos == 1)
                {
                        ptr = first;
                        first = first->next;

                        printf("\n\n Removing '%s' from playlist.....\n", ptr->sname);

                        printf("\n\n Removed!!\n\n");
                        free(ptr);
                }
                else
                {
                        ptr = first;
                        for (i = 0; i < pos - 1; i++)
                        {
                                temp = ptr;
                                ptr = ptr->next;
                                if (ptr == NULL)
                                {

                                        printf("No Songs At this position in playlist\n");
                                        return;
                                }
                        }
                        temp->next = ptr->next;

                        printf("\n\n Removing '%s' from playlist.....\n", ptr->sname);

                        printf("\n\n Removed!!\n\n");

                        free(ptr);
                }
        }
}

//welcome function
void menu()
{
        white();

        printf("\n||~~~~~~~~~~~~~~~~~~~~~~~~~   WELCOME TO GAANA   ~~~~~~~~~~~~~~~~~~~~~~~~||\n");

        reset();
        red();

        printf("\n||~~~~~~~~~~~~~~~~~~~~~~   HOPE YOU WILL ENJOY IT  ~~~~~~~~~~~~~~~~~~~~~~||\n");
        reset();

        white();
        printf("\n||~~~~~~~~~~~~~~~~~~~~~~~~   LET'S GET STARTED   ~~~~~~~~~~~~~~~~~~~~~~~~||\n");

        reset();
}

// search song naive's algorithm
int flag=0;
int search_song(char search[], sl songlist)
{
        
        int M = strlen(search);

        int N = strlen(songlist.song_name);

        for (int i = 0; i <= N - M; i++)
        {
                int j;
                for (j = 0; j < M; j++)
                        if (songlist.song_name[i + j] != search[j])
                                break;

                if (j == M)
                {
                        flag=1;
                        printf("%-25s\t", songlist.song_name);
                        printf("%-20s\t", songlist.singer_name);
                        printf("%-7d\t", songlist.no_of_likes);
                        printf("%-25s\t\n", songlist.album);
                }
        }
        return flag;
}

// select song string matching
int swch;
void select_song(char search[], sl songlist)
{
        int M = strlen(search);
        int N = strlen(songlist.song_name);

        for (int i = 0; i <= N; i++)
        {
                int j;
                for (j = 0; j < M; j++)
                        if (songlist.song_name[i + j] != search[j])
                                break;
                if (j == M)
                {
                        printf("\n\n'SELECTED' %s by %s\n\n", songlist.song_name, songlist.singer_name);

                        while (1)

                        {
                                printf("1:Play '%s'\n", songlist.song_name);
                                printf("2:Go to main menu");
                                printf("\n\nEnter Choice:");
                                scanf("%d", &swch);
                                switch (swch)
                                {
                                case 1:
                                        printf("\n\n Now Playing......\n\n");

                                        for (int i = 0; i < songlist.time; i++)
                                        {
                                                printf(">");
                                                sleep(1);
                                                fflush(stdout);
                                        }
                                        printf("\n\n");
                                        break;
                                case 2:
                                        return;

                                default:
                                        printf("invalid choice!!");
                                        break;
                                }
                        }
                }
        }
}

// search singer string matching
int flagg=0;
int search_singer(char singer[], sl songlist)
{
       
        int i, j;
        int M = strlen(singer);
        int N = strlen(songlist.singer_name);

        for (i = 0; i <= N - M; i++)
        {
                for (j = 0; j < M; j++)
                        if (songlist.singer_name[i + j] != singer[j])
                                break;

                if (j == M)
                {
                        flagg=1;
                        printf("%-25s\t", songlist.song_name);
                        printf("%-20s\t", songlist.album);
                        printf("%-4d\t\n", songlist.no_of_likes);
                }
        }
        return flagg;
}

// search by year
int flaggg=0;
int search_by_year(char year[], sl songlist)
{
        int i, j;
        int M = strlen(year);
        int N = strlen(songlist.year);

        for (i = 0; i <= N - M; i++)
        {

                for (j = 0; j < M; j++)
                {
                        if (songlist.year[i + j] != year[j])
                                break;
                }

                if (j == M)
                {
                        flaggg=1;
                        printf("%-25s\t", songlist.song_name);
                        printf("%-20s\t", songlist.album);
                        printf("%-4d\t\n", songlist.no_of_likes);
                }
        }
        return (flaggg);
}

//main function
int main()
{
        int flag1;
        char sgname[20];
        char sing[20];
        sl songlist[200];
        char yr[4];
        int i = 0, j = 0;
        char selected_song[20];

        menu();

        FILE *song1;
        song1 = fopen("gana.txt", "rb");

        if (song1 == NULL)
        {
                printf("can not open file \n");
                return 1;
        }

        /*fetching input from file*/
        for (i = 0; i < 200; i++)
        {
                int result = fscanf(song1, "%d", &songlist[i].song_id);
                if (result != 1) {
                        // Failed to read the expected number of fields, indicating the end of the file
                        break;
                }
                fscanf(song1, "%s", songlist[i].song_name);
                fscanf(song1, "%s", songlist[i].singer_name);
                fscanf(song1, "%d", &songlist[i].no_of_likes);
                fscanf(song1, "%s", songlist[i].album);
                fscanf(song1, "%s", songlist[i].year);
                fscanf(song1, "%d", &songlist[i].time);
        }

        int ch;

        while (1)
        {
                red();
                printf("\n\n1)--> Search Songs\n");
                printf("2)--> Search Singer's Profile\n");
                printf("3)--> Play Songs\n");
                printf("4)--> Create Playlist\n");
                printf("5)--> Open Playlist\n");
                printf("6)--> Remove Songs From Playlist\n");
                printf("7)--> Search Songs By Year Of Release\n");
                printf("8)--> Exit the program\n\n");
                reset();
                printf("Select Functions To Perform -->");
                scanf("%d", &ch);

                switch (ch)
                {

                case 1:
                        printf("Song Name:");
                        scanf("%s", sgname);

                        printf("----------------------------Recommended songs as per your search----------------------------\n\n");
                        printf("%-25s\t%-20s\t%-7s\t%4s\n\n", "|Song Name|", "|Singer Name|", "|Likes|", "|Album|");

                        for (i = 0; i < 200; i++)
                        {
                                flag1=search_song(sgname, songlist[i]);
                        }
                        printf("\n");
                        if (flag1==0)
                        {
                                printf("\n------------------------------SORRY!! NO SONG RELATED TO YOUR CHOICE-------------------------");
                        }
                        break;

                case 2:
                        printf("Singer Name:");
                        scanf("%s", sing);

                        printf("----------------------------[%s's] Songs----------------------------\n\n", sing);
                        printf("%-25s\t%-20s\t%-4s\t\n\n", "|Song Name|", "|Album|", "|Likes|");

                        for (i = 0; i < 200; i++)
                        {
                                flag1=search_singer(sing, songlist[i]);
                        }
                        printf("\n");
                        if (flag1==0)
                        {
                                printf("\n----------------------SORRY!! NO SONG RELATED TO YOUR SINGER-----------------------");
                        }
                        break;

                case 3:
                        printf("\nSelect Song To Play:");
                        scanf("%s", selected_song);

                        for (i = 0; i < 200; i++)
                        {
                                select_song(selected_song, songlist[i]);
                        }
                        printf("Happy playing....see you soon\n\n");
                        break;

                case 4:
                        add_song();
                        break;
                case 5:
                        display_playlist();
                        break;
                case 6:
                        remove_song();
                        break;
                case 7:
                        printf("Enter Year(YYYY) To Get Songs: ");
                        scanf("%s", yr);
                        printf("----------------------------[%s's] Songs----------------------------\n\n", yr);
                        printf("%-25s\t%-20s\t%-4s\t\n\n", "|Song Name|", "|Album|", "|Likes|");
                        for (i = 0; i < 200; i++)
                        {
                                flag1=search_by_year(yr, songlist[i]);
                        }
                        if (flag1==0)
                        {
                                printf("\n------------------------SORRY!! NO SONG RELATED TO YOUR CHOICE---------------------");
                        }

                        break;
                case 8:
                        exit(0);

                default:
                        printf("INVALID CHOICE\n\n");
                        break;
                }
        }

        return 0;
}
