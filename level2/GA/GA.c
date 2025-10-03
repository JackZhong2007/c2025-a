//0 is wall;1 is node;2 is can be chosen road;3 is road;4 is target;5 is man
//找不到路的话最终会运行九十秒左右

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<math.h>

#define LINE 15
#define COLUMN 15
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
int mate[LINE][COLUMN];
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
#define POPULATION_SIZE 200  
#define GENE_LENGTH 600     
#define CROSSOVER_RATE 90    
#define MUTATE_RATE 15       
#define POPULATION_GENERATION_MAX 50000  
#define PRINT_CURRENT_GA_PATH_TIME 200   
const int PARENT_SOURCE = 0.5 * POPULATION_SIZE;  
const int ELITE_COUNT = 0.05 * POPULATION_SIZE;   
typedef enum{left=0,right,up,down}WAY;
typedef enum{path=6,from,to}GA_path;
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

void population_initialization(POPULATION*population);
void fitness_evaluate(INDIVIDUAL*individual);
void crossover(INDIVIDUAL*parent_1,INDIVIDUAL*parent_2,INDIVIDUAL*child);
void mutate(INDIVIDUAL*individual);
int compare_individual(const void*a,const void*b);
void find_best_individual(POPULATION*population);
void selction(POPULATION*population);
void evaluate_population(POPULATION*population);
void print_GA_path(INDIVIDUAL*individual);
void genetic_algorithm(POPULATION*population);

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
void fitness_evaluate(INDIVIDUAL* individual){
    int visit[LINE][COLUMN] = {0};
    int simulate_line = OrginalLine, simulate_column = OrginalColumn;
    visit[simulate_line][simulate_column] = 1;
    int path_length = 0;
    path_length++;
    for(int i = 0; i < GENE_LENGTH; i++){
        int temp_line = simulate_line, temp_column = simulate_column;
        switch(individual->genes[i]){
            case left:  temp_column--;  break;
            case right: temp_column++;  break;
            case up:    temp_line--;    break;
            case down:  temp_line++;    break;
        }
        if(temp_line < 0 || temp_line >= LINE || temp_column < 0 || temp_column >= COLUMN) {
            break;
        }
        if(mate[temp_line][temp_column] == ROAD || mate[temp_line][temp_column] == Target){
            simulate_line = temp_line;
            simulate_column = temp_column;
            visit[simulate_line][simulate_column]++;
            path_length++;
            if(mate[simulate_line][simulate_column] == Target){
                individual->arrival_target = true;
                break; 
            }
        } else {
            break; 
        }
    }
    individual->eventual_line = simulate_line;
    individual->eventual_column = simulate_column;
    int revisit = 0, uniquevisit = 0;
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            if(visit[i][j] > 0){
                uniquevisit++;
                if(visit[i][j] > 1){
                    revisit += visit[i][j] - 1;
                }
            }
        }
    }
    individual->path_length = uniquevisit;
    int distance = abs(COLUMN - 2 - simulate_column) + abs(LINE - 2 - simulate_column);
    if(individual->arrival_target){
        individual->fitness = 10000 + (GENE_LENGTH - individual->path_length) * 10 - revisit * 5;
    } else {
        double distance_factor = 1.0 / (distance + 1); // 避免除零
        individual->fitness = (int)(distance_factor * 5000) + uniquevisit * 2 - revisit * 10;
        if(distance < 20){
            individual->fitness += (20 - distance) * 10;
        }
    }
}
void crossover(INDIVIDUAL* parent_1, INDIVIDUAL* parent_2, INDIVIDUAL* child){
    int whether_crossover = rand() % 100;
    if(whether_crossover > CROSSOVER_RATE){
        if(parent_1->fitness >= parent_2->fitness){
            memcpy(child->genes, parent_1->genes, GENE_LENGTH * sizeof(int));
        } else {
            memcpy(child->genes, parent_2->genes, GENE_LENGTH * sizeof(int));
        }
        return;
    }
    int crossover_points = 3 + rand() % 5; // 3-7个交叉点
    bool use_parent_1 = true;
    int last_point = 0;
    for(int i = 0; i < crossover_points; i++){
        int point = last_point + rand() % (GENE_LENGTH / crossover_points);
        if(point >= GENE_LENGTH) point = GENE_LENGTH - 1;
        
        for(int j = last_point; j < point; j++){
            if(use_parent_1){
                child->genes[j] = parent_1->genes[j];
            } else {
                child->genes[j] = parent_2->genes[j];
            }
        }
        use_parent_1 = !use_parent_1;
        last_point = point;
    }
    for(int j = last_point; j < GENE_LENGTH; j++){
        if(use_parent_1){
            child->genes[j] = parent_1->genes[j];
        } else {
            child->genes[j] = parent_2->genes[j];
        }
    }
}
void mutate(INDIVIDUAL* individual){
    double base_mutation_rate = MUTATE_RATE / 100.0;
    for(int i = 0; i < GENE_LENGTH; i++){
        // 自适应变异：在路径后期增加变异概率
        double adaptive_rate = base_mutation_rate * (1.0 + (double)i / GENE_LENGTH);
        if((double)rand() / RAND_MAX < adaptive_rate){
            int new_way = rand() % 4;
            individual->genes[i] = new_way;
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
    return individual_b->fitness-individual_a->fitness;
}
void find_best_individual(POPULATION*population){
    qsort(population->individual,POPULATION_SIZE,sizeof(INDIVIDUAL),compare_individual);
    if(population->generation==0||compare_individual(&population->individual[0],&population->best_individual)<0){
        population->best_individual=population->individual[0];
    }
}
void selction(POPULATION* population){
    printf("Performing selection...\n");
    double total_fitness = 0;
    for(int i = 0; i < POPULATION_SIZE; i++){
        double fitness = population->individual[i].fitness;
        if(fitness < 0) fitness = 1; 
        total_fitness += fitness;
    }
    INDIVIDUAL *new_population = (INDIVIDUAL*)malloc(POPULATION_SIZE * sizeof(INDIVIDUAL));
    if(new_population == NULL) {
        printf("Memory allocation failed in selection!\n");
        return;
    }
    for(int i = 0; i < ELITE_COUNT; i++){
        new_population[i] = population->individual[i];
    }
    for(int i = ELITE_COUNT; i < POPULATION_SIZE; i++){
        double random_value = (double)rand() / RAND_MAX * total_fitness;
        double cumulative_fitness = 0;
        for(int j = 0; j < POPULATION_SIZE; j++){
            double fitness = population->individual[j].fitness;
            if(fitness < 0){
                fitness = 1;
            }
            cumulative_fitness += fitness;
            if(cumulative_fitness >= random_value){
                new_population[i] = population->individual[j];
                break;
            }
        }
    }
    for(int i = 0; i < POPULATION_SIZE; i++){
        population->individual[i] = new_population[i];
    }
    free(new_population);
    printf("Selection completed.\n");
}
void evaluate_population(POPULATION*population){
    for(int i=0;i<POPULATION_SIZE;i++){
        fitness_evaluate(&population->individual[i]);
    }
}
void print_GA_path(INDIVIDUAL*individual){
    int simulate_line=OrginalLine,simulate_column=OrginalColumn;
    int temp_mate[LINE][COLUMN];
    temp_mate[simulate_line][simulate_column]=from;
    memcpy(temp_mate,mate,sizeof(mate));
    for(int i=0;i<GENE_LENGTH;i++){
        int temp_line=simulate_line,temp_column=simulate_column;
        switch(individual->genes[i]){
            case left:  temp_column--;  break;
            case right: temp_column++;  break;
            case up:    temp_line--;    break;
            case down:  temp_line++;    break;
        }    
        if(temp_mate[temp_line][temp_column]==ROAD){
            simulate_line=temp_line,simulate_column=temp_column;
            temp_mate[simulate_line][simulate_column]=path;
        }else if(temp_mate[temp_line][temp_column]==Target){
            simulate_line=temp_line,simulate_column=temp_column;
            temp_mate[simulate_line][simulate_column]=to;
            goto next;
        }
    }
    temp_mate[individual->eventual_line][individual->eventual_column]=to;
    next: ;
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            if(i==1&&j==1){
                printf("\033[1;35mO\033[0m");
                goto next1;
            }
            switch(temp_mate[i][j]){
                case WALL:              printf("\033[1;34m0\033[0m");   break;
                case ROAD:              printf(" ");                    break;
                case CanBeChosenRoad:   printf("\033[1;34m0\033[0m");   break;
                case path:              printf("\033[1;33m*\033[0m");   break;
                case from:              printf("\033[1;32mS\033[0m");   break;
                case to:                printf("\033[1;35mE\033[0m");   break;
                case Target:            printf("\033[1;35mT\033[0m");   break;
            }
            next1: ;
        }
        printf("\n");
    }
}
void genetic_algorithm(POPULATION*population){
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&time_start);
    QueryPerformanceFrequency(&frequency);
    population_initialization(population);
    population->generation=0;
    population->best_individual.fitness=-99999;
    population->best_individual.arrival_target=false;
    printf("Please press any key to start running the Genetic Algorithm...\n");
    getch();
    while(population->generation<POPULATION_GENERATION_MAX){
        evaluate_population(population);
        find_best_individual(population);
        /*
        if(population->generation%PRINT_CURRENT_GA_PATH_TIME== 0){
            system("cls");
            printf("Generation: %d\n", population->generation);
            printf("Best Fitness: %d\n", population->best_individual.fitness);
            printf("Path Length: %d\n", population->best_individual.path_length);
            printf("Reached Target: %s\n", population->best_individual.arrival_target ? "Yes" : "No");
            printf("Final Position: (%d, %d)\n", population->best_individual.eventual_line, population->best_individual.eventual_column);
            printf("Target Position: (%d, %d)\n", LINE-2, COLUMN-2);
            printf("\nPath Map (S=Start, E=End, *=Path, T=Target):\n");
            print_GA_path(&population->best_individual);
            Sleep(1000);
        }
            */
        if(population->best_individual.arrival_target){
            break;
        }
        INDIVIDUAL new_population[POPULATION_SIZE];
        selction(population);
        for(int i=0;i<ELITE_COUNT;i++){
            new_population[i]=population->individual[i];
        }
        for(int i=ELITE_COUNT;i<POPULATION_SIZE;i++){
            int parent_1=rand()%PARENT_SOURCE;
            int parent_2=rand()%PARENT_SOURCE;
            INDIVIDUAL child;
            crossover(&population->individual[parent_1],&population->individual[parent_2],&child);
            mutate(&child);
            new_population[i]=child;
        }
        for(int i=0;i<POPULATION_SIZE;i++){
            population->individual[i]=new_population[i];
        }
        population->generation++;
    }
    system("cls");
    printf("=== FINAL RESULT ===\n");
    printf("Generation: %d\n", population->generation);
    printf("Best Fitness: %d\n", population->best_individual.fitness);
    printf("Path Length: %d\n", population->best_individual.path_length);
    printf("Reached Target: %s\n", population->best_individual.arrival_target ? "Yes" : "No");
    printf("Final Position: (%d, %d)\n", population->best_individual.eventual_line, population->best_individual.eventual_column);
    printf("Target Position: (%d, %d)\n", LINE-2, COLUMN-2);
    printf("\nFinal Path Map:\n");
    print_GA_path(&population->best_individual);
    if(population->best_individual.arrival_target){
        printf("\nSuccess! Found path to target in %d generations!\n", population->generation);
    } else {
        printf("\nFailed to find path within generation limit.\n");
    }
    QueryPerformanceCounter(&time_over);
    float time_in_second=1.0*(time_over.QuadPart-time_start.QuadPart)/frequency.QuadPart;
    printf("The running time is : %f seconds",time_in_second);
    printf("\nPress any key to exit...");
    getch();
}
int main(){
    srand((unsigned)time(NULL));
    mate_initialization();
    while(mate_generate());
    hide_cursor();
    mate[LINE-2][COLUMN-2]=Target;
    printf("If you wanna to play the mate,please push any key except '1',because push it will turn to the chaeting mod.");
    char choice=getch();
    system("cls");
    if(choice=='1'){
        POPULATION*population=(POPULATION*)malloc(sizeof(POPULATION));
        genetic_algorithm(population);
    }else{
        game_time();
    }
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