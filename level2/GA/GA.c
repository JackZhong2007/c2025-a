//0 is wall;1 is node;2 is can be chosen road;3 is road;4 is target;5 is man

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

#define LINE 25
#define COLUMN 101
#define WALL 0
#define NODE 1
#define CanBeChosenRoad 2
#define ROAD 3
#define Target 4
#define MAN 5
#define OrginalLine 1
#define OrginalColumn 1
typedef struct{
    int x;
    int y;
}CAN_BE_CHOSEN_POSITION;
int mate[25][101];
int node_number,can_be_chosen_number;
int current_Line=OrginalLine,current_Column=OrginalColumn;
CAN_BE_CHOSEN_POSITION can_be_chosen_position[LINE*COLUMN];

void mate_initialization();
void print_mate();
void can_be_chosen_road(int line,int column);
bool mate_generate();
void hide_cursor();
void game_time();
void move(char keyboard);

void mate_initialization(){
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            if(1==i%2&&1==j%2){
                mate[i][j]=NODE;
                node_number++;
            }else{
                mate[i][j]=WALL;
            }
        }
    }
    mate[OrginalLine][OrginalColumn]=ROAD;
    can_be_chosen_road(OrginalLine,OrginalColumn);
    node_number--;
}
void print_mate(){
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            switch(mate[i][j]){
                case WALL:  
                    printf("\033[1;34m0\033[0m");
                    break;
                case ROAD:
                    printf(" ");
                    break;
                case CanBeChosenRoad:
                    printf("\033[1;34m0\033[0m");
                    break;
                case Target:
                    printf("\033[1;31m6\033[0m");
                    break;
                case MAN:
                    printf("\033[1;32m5\033[0m");
                    break;
            }
        }
        printf("\n");
    }
}
void can_be_chosen_road(int line,int column){
    if(line>1&&mate[line-1][column]==WALL){
        mate[line-1][column]=CanBeChosenRoad;
        can_be_chosen_position[can_be_chosen_number].x=line-1;
        can_be_chosen_position[can_be_chosen_number].y=column;
        can_be_chosen_number++;
    }
    if(line<LINE-2&&mate[line+1][column]==WALL){
        mate[line+1][column]=CanBeChosenRoad;
        can_be_chosen_position[can_be_chosen_number].x=line+1;
        can_be_chosen_position[can_be_chosen_number].y=column;
        can_be_chosen_number++;
    }
    if(column>1&&mate[line][column-1]==WALL){
        mate[line][column-1]=CanBeChosenRoad;
        can_be_chosen_position[can_be_chosen_number].x=line;
        can_be_chosen_position[can_be_chosen_number].y=column-1;
        can_be_chosen_number++;
    }
    if(column<COLUMN-2&&mate[line][column+1]==WALL){
        mate[line][column+1]=CanBeChosenRoad;
        can_be_chosen_position[can_be_chosen_number].x=line;
        can_be_chosen_position[can_be_chosen_number].y=column+1;
        can_be_chosen_number++;
    }
}
bool mate_generate(){
    int chosen_position=rand()%can_be_chosen_number;
    int x=can_be_chosen_position[chosen_position].x,y=can_be_chosen_position[chosen_position].y;
    can_be_chosen_number--;
    can_be_chosen_position[chosen_position]=can_be_chosen_position[can_be_chosen_number];
    if(x>1&&mate[x-1][y]==NODE){
        mate[x-1][y]=ROAD;
        mate[x][y]=ROAD;
        node_number--;
        can_be_chosen_road(x-1,y);
    }else if(x<LINE-2&&mate[x+1][y]==NODE){
        mate[x][y]=ROAD;
        mate[x+1][y]=ROAD;
        node_number--;
        can_be_chosen_road(x+1,y);
    }else if(y>1&&mate[x][y-1]==NODE){
        mate[x][y]=ROAD;
        mate[x][y-1]=ROAD;
        node_number--;
        can_be_chosen_road(x,y-1);
    }else if(y<COLUMN-2&&mate[x][y+1]==NODE){
        mate[x][y]=ROAD;
        mate[x][y+1]=ROAD;
        node_number--;
        can_be_chosen_road(x,y+1);
    }
    /*system("cls");
    print_mate();
    Sleep(100000);*/
    if(node_number<=0||can_be_chosen_number<=0){
        return false;
    }else{
        return true;
    }
}
void hide_cursor(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorinfo;
    GetConsoleCursorInfo(hConsole,&cursorinfo);
    cursorinfo.bVisible=false;
    SetConsoleCursorInfo(hConsole,&cursorinfo);
}
void game_time(){
    mate[LINE-2][COLUMN-2]=Target;
    mate[current_Line][current_Column]=MAN;
    while(mate[LINE-2][COLUMN-2]==Target){
        print_mate();
        Sleep(50);
        char keyboard = getch();
        move(keyboard);
        system("cls");
    }
    MessageBox(0,TEXT("Congratulation!"),TEXT("ok"),MB_OK);
}
void move(char keyboard){
    switch(keyboard){
        case 'a':
            if(mate[current_Line][current_Column-1]==ROAD||mate[current_Line][current_Column-1]==Target){
                mate[current_Line][current_Column]=ROAD;
                mate[current_Line][current_Column-1]=MAN;
                current_Column--;
            }else{
                move(getch());
            }
            break;
        case 's':
            if(mate[current_Line+1][current_Column]==ROAD||mate[current_Line+1][current_Column]==Target){
                mate[current_Line][current_Column]=ROAD;
                mate[current_Line+1][current_Column]=MAN;
                current_Line++;
            }else{
                move(getch());
            }
            break;
        case 'd':if(mate[current_Line][current_Column+1]==ROAD||mate[current_Line][current_Column+1]==Target){
                mate[current_Line][current_Column]=ROAD;
                mate[current_Line][current_Column+1]=MAN;
                current_Column++;
            }else{
                move(getch());
            }
            break;
        case 'w':if(mate[current_Line-1][current_Column]==ROAD||mate[current_Line-1][current_Column]==Target){
                mate[current_Line][current_Column]=ROAD;
                mate[current_Line-1][current_Column]=MAN;
                current_Line--;
            }else{
                move(getch());
            }
            break;
        default :
            move(getch());
    }
}
int main(){
    srand((unsigned)time(NULL));
    mate_initialization();
    while(mate_generate());
    hide_cursor();
    game_time();
    return 0;
}