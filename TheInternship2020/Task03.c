#include<stdio.h>
#define TASKNUM 12
#define ANSNUM 5

struct ANS{
    int num;
    int value;
};

int main(){
    int task[TASKNUM];
    struct ANS answer[ANSNUM];
    int score = 0;
    int result = 0;
    int wrongNumDisplay = 0;
    char scoreBoard[ANSNUM][TASKNUM+5];
    for(int i = 0 ; i < TASKNUM; i++){
        scanf("%d",&task[i]);
    }
    for(int i = ANSNUM-1 ; i >= 0  ;i--){
        scanf("%d",&answer[i].num);
        answer[i].value = i + 1;
        for(int j = 0 ; j < TASKNUM + 5 ; j++){
            if(j < TASKNUM){
                scoreBoard[i][j] = '_';
            }
            else{
                scoreBoard[i][j] = ' ';
            }
        }
    }
    for(int i = ANSNUM ; i >= 0; i--){
        int rightAnswer = 0;
        for(int j = 0 ; j < TASKNUM;j++){
            if(i == ANSNUM){
                printf("_ ");
            }
            else{
                if(answer[i].value >= i && answer[i].num == task[j]){
                    scoreBoard[i][j] = answer[i].num;
                    score++;
                    for(int k = 0; k <= i ; k++){
                        scoreBoard[k][j] = answer[i].num;
                    }
                    rightAnswer = 1;
                }
            }
        }
        if(!rightAnswer){
            if(answer[i].value >= i){
                scoreBoard[i][TASKNUM+wrongNumDisplay] = answer[i].num;
                for(int k = 0; k <= i ; k++){
                    scoreBoard[k][TASKNUM+wrongNumDisplay] = answer[i].num;
                }
                wrongNumDisplay++;
            }
        }
    }
    printf("\n");
    for(int i = ANSNUM-1 ; i >= 0  ;i--){
        for(int j = 0 ; j < TASKNUM ; j++){
            if(scoreBoard[i][j] >= 0 && scoreBoard[i][j] <= 9 ){
                printf("%d",scoreBoard[i][j]);
            }
            else{
                printf("_",scoreBoard[i][j]);
            }
            printf(" ");
        }
        for(int j = TASKNUM ;j < TASKNUM + 5; j++){
            if(scoreBoard[i][j] >= 0 && scoreBoard[i][j] <= 9 ){
                printf("%d",scoreBoard[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("%d",score);
    return 0;
}
