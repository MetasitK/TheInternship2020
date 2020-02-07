#include<stdio.h>
#include<string.h>
#include<ctype.h>


struct NAME{
    char name[100] ;
    int abbreviationNumber;
};

void reduceName(char *name);
void sortName(struct NAME *_info,int nameLen);
void swapChar(char *a, char *b);
void swapNAME(struct NAME *_infoA,struct NAME *_infoB);

int main(){
    int n;
    scanf("%d",&n);
    struct NAME info[n];
    char name[n][100];
    getchar();
    for(int i = 0 ; i < n ; i++){
        fgets(name[i],100,stdin);
        if(name[i][strlen(name[i]) - 1] == '\n'){
            name[i][strlen(name[i]) - 1] = '\0';
        }
        reduceName(name[i]);
        strcpy(info[i].name,name[i]);
        info[i].abbreviationNumber = strlen(name[i]);
    }
    for(int i = 0 ; i < n ; i++){
    }
    sortName(info,n);
    for(int i = 0 ; i < n ; i++){
        printf("%s",info[i].name,info[i].abbreviationNumber);
        if(i < n - 1){
            printf("\n");
        }
    }

    return 0;
}
void reduceName(char *name){
    for(int i = 0 ; i < strlen(name) ; i++){
        if(islower(name[i])){
            name[i] = ' ';
        }
        else{
            if(i > 0 && name[i-1] != ' '){
                name[i] = ' ';
            }
        }
    }
    int swapPoint=0;
    int i = 0;
    while(name[i] != '\0'){
        if(name[i] != ' '){
            swapChar(&name[i],&name[swapPoint]);
            swapPoint++;
        }
        i++;
    }
    i=0;
    while(1){
        if(name[i] == ' '){
            name[i] = '\0';
            break;
        }
        i++;
    }
}
void sortName(struct NAME *_info, int n){
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n-1;j++){
            if(_info[j].abbreviationNumber < _info[j+1].abbreviationNumber){
                swapNAME(&_info[j],&_info[j+1]);
            }
            if(_info[j].abbreviationNumber == _info[j+1].abbreviationNumber){
                if(strcmp(_info[j].name,_info[j+1].name)){
                    swapNAME(&_info[j],&_info[j+1]);
                }
            }
        }
    }
}
void swapChar(char *a,char *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void swapNAME(struct NAME *_infoA,struct NAME *_infoB){
    struct NAME tmp = *_infoA;
    *_infoA = *_infoB;
    *_infoB = tmp;
}
