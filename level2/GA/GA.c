//0 is wall;1 is node;2 is can be chosen road;3 is road;4 is target;5 is man

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<math.h>

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
        printf("Please push asdw to control the '5'man\n");
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



//GA
//基本定义
#define GENE_LENGTH 3000
#define POPULATION_SIZE 500
#define CROSSOVER_RATE 85
#define MUTATE_RATE 5
const int ELITE_COUNT=0.1*POPULATION_SIZE;
typedef enum{left=0,right,up,down}WAY;
typedef struct{
    int genes[GENE_LENGTH];
    bool arrival_target;
    int fitness;
    int path_length;
    int eventual_line,eventual_column;
}INDIVIDUAL;
typedef struct{
    INDIVIDUAL individual[POPULATION_SIZE];
    INDIVIDUAL best_individual;
    int generation;
}POPULATION;
//
//函数原型
void population_initialization(POPULATION*population);
void fitness_evaluate(INDIVIDUAL*individual);
void crossover(INDIVIDUAL*parent_1,INDIVIDUAL*parent_2,INDIVIDUAL*child);
void mutate(INDIVIDUAL*individual);
int compare_individual(const void*a,const void*b);
void find_best_individual(POPULATION*population);
void section(POPULATION*population);
void evaluate_population(POPULATION*population);
//
//函数定义
void population_initialization(POPULATION*population){
    for(int i=0;i<POPULATION_SIZE;i++){
        for(int j=0;j<GENE_LENGTH;j++){
            int way=rand()%4;
            population->individual[i].genes[j]=way;
        }
        population->individual[i].arrival_target=false;
        population->individual[i].fitness=0;
        population->individual[i].path_length=0;
        population->individual[i].eventual_line=0;
        population->individual[i].eventual_column=0;
    }
}

void fitness_evaluate(INDIVIDUAL*individual){
    int visit[LINE][COLUMN]={0};
    int simulate_line=OrginalLine,simulate_column=OrginalColumn;
    visit[simulate_line][simulate_column]=1;
    for(int i=0;i<GENE_LENGTH;i++){
        int temp_line=simulate_line,temp_column=simulate_column;
        switch(individual->genes[i]){
            case left:  temp_column--;  break;
            case right: temp_column++;  break;
            case up:    temp_line--;    break;
            case down:  temp_line++;    break;
        }
        if(mate[temp_line][temp_column]==ROAD||mate[temp_line][temp_column]==Target){
            simulate_line=temp_line,simulate_column=temp_column;
            visit[simulate_line][simulate_column]++;
            if(visit[simulate_line][simulate_column]==Target){
                individual->arrival_target=true;
            }
        }else{
            visit[simulate_line][simulate_column]++;
            break;
        }
    }
    individual->eventual_line=simulate_line;
    individual->eventual_column=simulate_column;
    int revisit=0,uniquevisit=0;
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            if(visit[i][j]>0){
                uniquevisit++;
            }else if(visit[i][j]>1){
                revisit+=visit[i][j]-1;
            }
        }
    }
    individual->path_length=uniquevisit;
    int distance=pow(COLUMN-2-simulate_column,2)+(LINE-2-simulate_line,2);
    if(individual->arrival_target){
        individual->fitness=10000-individual->path_length-10*revisit;
    }else{
        individual->fitness=5000-distance-individual->path_length-12*revisit;
    }
}

void crossover(INDIVIDUAL*parent_1,INDIVIDUAL*parent_2,INDIVIDUAL*child){
    int whether_crossover=rand()%100;
    if(whether_crossover>CROSSOVER_RATE){
        if(parent_1->fitness>=parent_2->fitness){
            for(int i=0;i<GENE_LENGTH;i++){
                child->genes[i]=parent_1->genes[i];
            }
        }else{
            for(int i=0;i<GENE_LENGTH;i++){
                child->genes[i]=parent_2->genes[i];
            }
        }
        return ;
    }
    int point_1=rand()%(GENE_LENGTH/2);
    int point_2=point_1+rand()%(GENE_LENGTH/2);
    for(int i=0;i<GENE_LENGTH;i++){
        if(i<point_1||i>point_2){
            child->genes[i]=parent_1->genes[i];
        }else{
            child->genes[i]=parent_2->genes[i];
        }
    }
}

void mutate(INDIVIDUAL*individual){
    for(int i=0;i<GENE_LENGTH;i++){
        int whether_mutate=rand()%100;
        if(whether_mutate<MUTATE_RATE){
            int new_way=rand()%4;
            individual->genes[i]=new_way;
        }
    }
}

int compare_individual(const void*a,const void*b){
    INDIVIDUAL*individual_a=(INDIVIDUAL*)a;
    INDIVIDUAL*individual_b=(INDIVIDUAL*)b;
    if(individual_a->arrival_target&&!individual_b->arrival_target){
        return -1;
    }
    if(!individual_a->arrival_target&&individual_b->arrival_target){
        return 1;
    }
    return individual_a->fitness-individual_b->fitness;
}

void find_best_individual(POPULATION*population){
    qsort(population->individual,POPULATION_SIZE,sizeof(INDIVIDUAL),compare_individual);
    if(population->generation==0||compare_individual(&population->individual[0],&population->best_individual)<0){
        population->best_individual=population->individual[0];
    }
}

void section(POPULATION*population){
    INDIVIDUAL new_population[POPULATION_SIZE];
    for(int i=0;i<ELITE_COUNT;i++){
        new_population[i]=population->individual[i];
    }
    for(int i=ELITE_COUNT;i<POPULATION_SIZE;i++){
        int candidate_1=rand()%POPULATION_SIZE;
        int candidate_2=rand()%POPULATION_SIZE;
        if(compare_individual(&population->individual[candidate_1].fitness,&population->individual[candidate_2].fitness)<0){
            new_population[i]=population->individual[candidate_1];
        }else{
            new_population[i]=population->individual[candidate_2];
        }
    }
    for(int i=0;i<POPULATION_SIZE;i++){
        population->individual[i]=new_population[i];
    }
}

void evaluate_population(POPULATION*population){
    for(int i=0;i<POPULATION_SIZE;i++){
        fitness_evaluate(&population->individual[i]);
    }
}













//


int main(){
    srand((unsigned)time(NULL));
    mate_initialization();
    while(mate_generate());
    hide_cursor();
    game_time();
    return 0;
}
/*
//GA
#define GENE_LENGTH 2000
#define POPULATION_SIZE 200
#define CROSSOVER_RATE 85
#define MUTATE_RATE 5

typedef struct{
    int genes[GENE_LENGTH];
    int fitness;
    int path_length;
    bool arrival_target;
}INDIVIDUAL;
typedef struct{
    INDIVIDUAL individual[POPULATION_SIZE];
    INDIVIDUAL best_individual;
    int generation;
}POPULATION;
typedef enum{left=0,right,up,down}WAY;

void population_initialization(POPULATION*population);
void fitness_individual(INDIVIDUAL*individual);
void crossover(INDIVIDUAL*parent1,INDIVIDUAL*parent2,INDIVIDUAL*child);
void mutate(INDIVIDUAL*individual);
void selction(POPULATION*population);

void population_initialization(POPULATION*population){
    for(int i=0;i<POPULATION_SIZE;i++){
        for(int j=0;j<GENE_LENGTH;j++){
            int way=rand()%4;
            population->individual[i].genes[j]=way;
        }
        population->individual[i].arrival_target=false;
        population->individual[i].path_length=0;
        population->individual[i].fitness=0;
    }
}
void fitness_individual(INDIVIDUAL*individual){
    int simulate_line=OrginalLine,simulate_column=OrginalColumn;
    int visit[LINE][COLUMN]={0};
    visit[simulate_line][simulate_column]=1;
    for(int i=0;i<GENE_LENGTH;i++){
        switch(individual->genes[i]){
            case left:
                if(mate[simulate_line][simulate_column-1]==ROAD){
                    visit[simulate_line][simulate_column-1]++;
                    simulate_column--;
                }else if(mate[simulate_line][simulate_column-1]==Target){
                    individual->arrival_target=true;
                    visit[simulate_line][simulate_column-1]++;
                    simulate_column--;
                    goto next;
                }else{
                    visit[simulate_line][simulate_column]++;
                }
                break;
            case right:
                if(mate[simulate_line][simulate_column+1]==ROAD){
                    visit[simulate_line][simulate_column+1]++;
                    simulate_column++;
                }else if(mate[simulate_line][simulate_column-1]==Target){
                    individual->arrival_target=true;
                    visit[simulate_line][simulate_column+1]++;
                    simulate_column++;
                    goto next;
                }else{
                    visit[simulate_line][simulate_column]++;
                }
                break;
            case up:
                if(mate[simulate_line-1][simulate_column]==ROAD){
                    visit[simulate_line-1][simulate_column]++;
                    simulate_column--;
                }else if(mate[simulate_line-1][simulate_column]==Target){
                    individual->arrival_target=true;
                    visit[simulate_line-1][simulate_column]++;
                    simulate_column--;
                    goto next;
                }else{
                    visit[simulate_line][simulate_column]++;
                }
                break;
            case down:
                if(mate[simulate_line+1][simulate_column]==ROAD){
                    visit[simulate_line+1][simulate_column]++;
                    simulate_column--;
                }else if(mate[simulate_line+1][simulate_column]==Target){
                    individual->arrival_target=true;
                    visit[simulate_line+1][simulate_column]++;
                    simulate_column--;
                    goto next;
                }else{
                    visit[simulate_line][simulate_column]++;
                }
                break;
                next : ;
        }
    }
    int revisit=0;
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            if(visit[i][j]>1){
                revisit++;
            }
        }
    }
    individual->path_length=GENE_LENGTH-revisit;
    int distance_to_target=pow((COLUMN-2-simulate_column),2)+((LINE-2-simulate_line),2);
    individual->fitness=1000000-distance_to_target-revisit*20+individual->path_length;
}
void crossover(INDIVIDUAL*parent1,INDIVIDUAL*parent2,INDIVIDUAL*child){
    int whether_crossover=rand()%100;
    if(whether_crossover>CROSSOVER_RATE){
        for(int i=0;i<GENE_LENGTH;i++){
            child->genes[i]=parent1->genes[i];
            return;
        }
    }
    int point1=rand()%(GENE_LENGTH/2);
    int point2=point1+rand()%(GENE_LENGTH-point1);
    for(int i=0;i<GENE_LENGTH;i++){
        if(i<point1||i>point2){
            child->genes[i]=parent1->genes[i];
        }else{
            child->genes[i]=parent2->genes[i];
        }
    }
}   
void mutate(INDIVIDUAL*individual){
    for(int i=0;i<GENE_LENGTH;i++){
        int whether_mutate=rand()%100;
        if(whether_mutate<MUTATE_RATE){
            int re_way=rand()%4;
            individual->genes[i]=re_way;
        }
    }
}
void selction(POPULATION*population){
    
}

//
*/