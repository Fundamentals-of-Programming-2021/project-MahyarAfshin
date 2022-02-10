#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct user{
    char name[51];
    long long int score;
}user;

extern user* users;
extern long long int numOfUsers;

void loadUsers();
int add_new_user(char name[51]);
void printUser();
void swap(long long int i, long long int j);
void bubble_sort_users();
void updateUsers();

