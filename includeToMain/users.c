#include"users.h"

void loadUsers(){
    FILE* usersFile=fopen("users.dat","r");
    if(usersFile==NULL){
        return;
    }
    user temp;
    while(fread(&temp,sizeof(user),1,usersFile)){
        numOfUsers++;
        if(numOfUsers==1){
            users=(user*)malloc(numOfUsers*sizeof(user));
        }
        else{
            users=(user*)realloc(users,numOfUsers*sizeof(user));
        }
        users[numOfUsers-1].name[0]='\0';
        strcat(users[numOfUsers-1].name,temp.name);
        users[numOfUsers-1].score=temp.score;
    }
    fclose(usersFile);
}

int add_new_user(char name[51]){
    loadUsers();
    for(long long int i=0; i<numOfUsers; i++){
        if(strcmp(users[i].name,name)==0){
            return i;
        }
    }
    numOfUsers++;
    if(numOfUsers==1){
        users=(user*)malloc(numOfUsers*sizeof(user));
    }
    else{
        users=(user*)realloc(users,numOfUsers*sizeof(user));
    }
    users[numOfUsers-1].name[0]='\0';
    strcat(users[numOfUsers-1].name,name);
    users[numOfUsers-1].score=0;
    FILE* usersFile=fopen("users.dat","w");
    fwrite(users,sizeof(user),numOfUsers,usersFile);
    fclose(usersFile);
    return numOfUsers-1;
}

void swap(long long int i, long long int j){
    user temp;
    temp.name[0]='\0';
    strcat(temp.name,users[i].name);
    temp.score=users[i].score;
    users[i].name[0]='\0';
    strcat(users[i].name,users[j].name);
    users[i].score=users[j].score;
    users[j].name[0]='\0';
    strcat(users[j].name,temp.name);
    users[j].score=temp.score;
}

void bubble_sort_users(){
    for(long long int i=0; i<numOfUsers; i++){
        for(long long int j=0; j<numOfUsers-i-1; j++){
            if(users[j].score<users[j+1].score){
                swap(j,j+1);
            }
        }
    }
}

void updateUsers(){
    FILE* usersFile=fopen("users.dat","w");
    fwrite(users,sizeof(user),numOfUsers,usersFile);
    fclose(usersFile);
}



