#include <stdio.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
void print_board(char board[][40]);
void initilize_board(char board[][40]);
void search(char board[][40],char board2[][40]);
int rules(char board[][40], int x, int y);
void board_to_board(char board[][40], char board2[][40]);

int main(int argc, char *argv[]){
    char board[40][40], board2[40][40],command;
    int i,j,count =0,x,y;
    FILE *fp;
    //fscanf(fp,"%c%d%d",&command,&x&y != EOF);

    initilize_board(board); 
    board_to_board(board,board2);
    print_board(board);
    printf("\n");

    if(argc < 2){
        while(count < 1000){    
            scanf("%c",&command);
            switch(command){
                case 'a':
                    scanf("%d",&x);
                    scanf("%d",&y);
                    board2[y][x] = 'X';
                    board_to_board(board2,board);
                    print_board(board);
                    printf("\n");
                    break;
                case 'r':
                    scanf("%d%d",&x,&y);
                    board2[y][x] = ' ';
                    board_to_board(board2,board);
                    print_board(board);
                    break;
                case 'n':
                    search(board,board2);
                    board_to_board(board2,board); 

                    print_board(board);
                    printf("\n");
                    break;
                case 'q':
                    return 0;
                    break;
                case'p':
                    while(count < 1000){

                        print_board(board);
                        search(board,board2);
                        board_to_board(board2,board); 
                        printf("\n");

                        usleep(80000);
                        system("clear");

                    }     
                    break;
            }
        }
    }else{
        fp = fopen( argv[1],"r");
        while(1000){    
            fscanf(fp,"%c",&command);
            switch(command){
                case 'a':
                    fscanf(fp,"%d",&x);
                    fscanf(fp,"%d",&y);
                    board2[y][x] = 'X';
                    board_to_board(board2,board);
                    print_board(board);
                    printf("\n");
                    break;
                case 'r':
                    fscanf(fp,"%d%d",&x,&y);
                    board2[y][x] = ' ';
                    board_to_board(board2,board);
                    print_board(board);
                    break;
                case 'n':
                    search(board,board2);
                    board_to_board(board2,board); 

                    print_board(board);
                    printf("\n");
                    break;
                case 'q':
                    return 0;
                    break;
                case'p':
                    while(count < 1000){

                        print_board(board);
                        search(board,board2);
                        board_to_board(board2,board); 
                        printf("\n");

                        usleep(90000);
                        system("clear");

                    }     
                    break;
            }
        }
    }
    initilize_board(board); 
    board_to_board(board,board2);
}

void search(char board[][40], char board2[][40]){
    int i,j;
    for(i=1;i<39;i++){
        for(j=1;j<39;j++){
            if(rules(board,i,j) == 1){
                board2[i][j] = ' ';        
            }else if(rules(board,i,j) == 2){
                board2[i][j] = board[i][j];
            }else if(rules(board,i,j) == 3){
                board2[i][j] = ' ';
            }else if(rules(board,i,j) == 4){
                board2[i][j] = 'X';
            }
        }
    }
}

void board_to_board(char board[][40], char board2[][40]){
    int i,j;

    for(i=0;i<40;i++){
        for(j=0;j<40;j++){
            board2[i][j] = board[i][j];
        }
    }
}

// rules 1-3 (not about adding a life
int rules(char board[][40],int i, int j){
    int count = 0;
    if(board[i+1][j] == 'X'){
        count = count + 1;
    }
    if(board[i+1][j+1] == 'X'){
        count = count + 1;
    }
    if(board[i+1][j-1] == 'X'){
        count = count + 1;
    } 
    if(board[i-1][j] == 'X'){
        count = count + 1;
    }
    if(board[i-1][j+1] == 'X'){
        count = count + 1;
    }
    if(board[i-1][j-1] == 'X'){
        count = count + 1;
    }
    if(board[i][j+1] == 'X'){
        count = count + 1;  
    }
    if(board[i][j-1] == 'X'){
        count = count + 1;
    }
    if(count < 2){
        //rule 1
        return 1;
    }else if(count == 2){
        return 2;
    }else if(count >3){
        return 3;
    }else if(count == 3){
        return 4;
    }
}

void print_board(char board[][40]){
    int i,j;
    for(i=0;i<40;i++){
        printf("\n");
        for(j=0;j<40;j++){
            printf("%c",board[i][j]);
        }
    }
}

void initilize_board(char board[][40]){
    int i,j;

    for(i=0;i<40;i++){
        for(j=0;j<40;j++){
            board[i][j] = ' ';
        }
    }
    for(i=0;i<40;i++){
        board[i][0] = '-';
    }
    for(i=0;i<40;i++){
        board[i][39] = '-';
    }
    for(i=0;i<40;i++){
        board[0][i] = '-';
    }
    for(i=0;i<40;i++){
        board[39][i] = '-';
    }
}
