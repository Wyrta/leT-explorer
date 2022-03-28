#include <stdio.h>
#include <dirent.h>
#include <string.h>

/************************************************************/
/************************************************************/

//For clear screen portability 
#if defined LINUX
    #define CLEAR_SCREEN system("clear");
#elif defined WIN32
    #define CLEAR_SCREEN system("cls");
//for more platforms
#endif

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

//Key macro
#define ARROW_UP    72
#define ARROW_DOWN  80
#define ARROW_LEFT  75
#define ARROW_RIGHT 77
#define ENTER 13
#define ESCAPE 27

/************************FUNCTION****************************/
/************************************************************/

void displayDir(char *path);
void storeDir(char *screen[10][260], char *path);
int keyPressed(void);


/**************************MAIN******************************/
/************************************************************/


int main(int argc, char *argv[]) {
/*
    char buff1[] = "hello world\n";
    char buff2[] = "hello le T\n";


    //      txt, sizeof 1 element, sizeof txt,      file
    fwrite(buff1, sizeof(char), sizeof(buff1) - 1, stdout);
    fflush(stdout);

    CLEAR_SCREEN


    fwrite(buff2, sizeof(char), sizeof(buff2) - 1, stdout);
*/
    
    /**
     * Screen buffer
     * assuming files name arent over 260 char and more than 10files/dirs in one in current
    */
    char screen[10][260];
    for (int i = 0; i < 10; i++) 
        strcpy(screen[i], "  ");

    int cursor = 0;
    screen[cursor][0] = '|'; screen[cursor][1] = '|';


    //CLEAR_SCREEN

    DIR *folder;
    folder = opendir(".");
    //if err => nahnahnah
    struct dirent *entry;
    int files = 0;
    while( (entry=readdir(folder)) ) {
        strcat(screen[files], entry->d_name);
        files++;
    }
    closedir(folder);


    for (int i = 0; i < 10; i++){
        printf(screen[i]);
        printf("\n");
    }

    int key = 1;
    while(1) {
        key = keyPressed();

        if((key == ARROW_UP) && (cursor > 0)) { screen[cursor][0] = ' '; screen[cursor][1] = ' '; cursor--; }
        if((key == ARROW_DOWN) && (cursor < 10)) { screen[cursor][0] = ' '; screen[cursor][1] = ' '; cursor++; }
        if(key == ENTER) {
            //Reset buffer
            for (int i = 0; i < 10; i++) 
                strcpy(screen[i], "  ");

/*************************************************************************************************************************************************************/
            DIR *folder;
            folder = opendir("test1");
            //if err => nahnahnah
            struct dirent *entry;
            int files = 0;
            while( (entry=readdir(folder)) ) {
                strcat(screen[files], entry->d_name);
                files++;
            }
            closedir(folder);
        }
        if(key == ESCAPE) return 0;


        screen[cursor][0] = '|'; screen[cursor][1] = '|';


        CLEAR_SCREEN


        for (int i = 0; i < 10; i++){
            printf(screen[i]);
            printf("\n");
        }

    }
    


    return 0;
}



/*********************FUNCTION CODE**************************/
/************************************************************/

void displayDir(char *path) {
    DIR *folder;

    folder = opendir(path);
    if(folder == NULL) {
        puts("Unable to read directory");
        return;
    }
    else {
        puts("Directory is opened!");
        int files = 0;
        struct dirent *entry;
        
        while( (entry=readdir(folder)) ) {
            files++;
            printf(" %s\n", entry->d_name );
        }
    }
    closedir(folder);
}

void storeDir(char *screen[10][260], char *path) {
    DIR *folder;
    folder = opendir(path);
    //if err => nahnahnah
    struct dirent *entry;
    int files = 0;
    while( (entry=readdir(folder)) ) {
        strcat(*screen[files], entry->d_name);
        files++;
    }
    closedir(folder);
}

int keyPressed(void) {
    int ch1, ch2;
    ch1 = getch();
    ch2 = 0;
    if (ch1 == 0xE0) { // a scroll key was pressed  else its for F1-12 key
        ch2 = getch();
        // determine what it was
        switch(ch2)
        {
            case 72: return ARROW_UP;    break;
            case 80: return ARROW_DOWN;  break;
            case 75: return ARROW_LEFT;  break;
            case 77: return ARROW_RIGHT; break;
            case 27: return ESCAPE;      break;
            case '\r': return ENTER;     break;

            // ... we can set also others like HOME, END, PGUP, PGDOWN, ...
        default:
            //return ENTER;
            //printf("SOME OTHER SCROLL KEY PRESSED: %d %d\n", ch1, ch2); 
            break;
        };
    } //else printf("key pressed: %d %c\n", ch1, ch2);
return 0;
}