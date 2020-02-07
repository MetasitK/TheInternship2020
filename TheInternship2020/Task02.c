#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct LIST{
    char result[5];
    struct LIST *next;
};

void initList(struct LIST *_numList,double num);
void addNumList(struct LIST *_numList,double num);
void printList(struct LIST *_numList);
int findPrime(int num);

int main(){
    struct LIST numList;
    double num;
    scanf("%lf",&num);
    initList(&numList,num);
    do{
        scanf("%lf",&num);
        if(num == 0.0){
            break;
        }
        addNumList(&numList,num);
    }while(1);
    printList(&numList);
    return 0;
}

void initList(struct LIST *_numList,double num){
    for(int i = 0 ; i < 3 ; i++){
        int intNum = num * pow(10,i+1);
        if(findPrime(intNum)){
            strcpy(_numList->result,"TRUE");
        }
        else{
            strcpy(_numList->result,"FALSE");
        }
    }
    _numList->next = NULL;
}
void addNumList(struct LIST *_numList,double num){
    struct LIST *newList = (struct LIST*)malloc(sizeof(struct LIST));
    for(int i = 0 ; i < 3 ; i++){
        int intNum = num * pow(10,i+1);
        if(findPrime(intNum)){
            strcpy(newList->result,"TRUE");
            break;
        }
        else{
            strcpy(newList->result,"FALSE");
        }
    }
    newList->next = NULL;

    while(_numList->next != NULL){
        _numList = _numList->next;
    }
    _numList->next = newList;
}
void printList(struct LIST *_numList){
    int i = 0;
    do{
        printf("%d:%s\n",i,_numList->result);
        _numList = _numList->next;
        i++;
    }while(_numList != NULL);
}
int findPrime(int num){
    int logicValue = 0;
    if(num % 2 != 0){
        for(int i = 3; i <= sqrt(num); i+=2){
            if(num % i == 0){
                logicValue = 0;
                break;
            }
            else{
                logicValue = 1;
            }
        }
    }
    return logicValue;
}
