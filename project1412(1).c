/*
In this game, a player rolls two dice. Each dice has six faces.
Each face contains 1, 2, 3, 4, 5 and 6 spots. After the dice have come to rest, the sum of
the spots on the two top faces is calculated. If the sum is 7 or 11 on the first throw the
player wins. If the sum is 2, 3, or 12 on the first throw, the player loses. If the sum is 4, 5,
6, 8, 9 or 10 on the first throw, that sum becomes the player’s “point.” To win, a player
must continue rolling the dice until the player rolls the point value. The player loses by
rolling a 7 before rolling the point.
If a player wins one game, s/he will earn $10. Otherwise, s/he will lose $1. A player can
keep playing the game until s/he chooses to quit or his/her balance becomes 0 or less.
*/

/******************
Just need to fix that gain weird thing on the game
*****************/

//Ricardo Ruiz
//Project 1412

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global structure since we use it through the file
/****MAIN structure ****/
typedef struct{

    char name[25];
    int balance;
    int gain;
    int player_points;

} Person;

//Person person[10];
int person_length;

///////

//this Function initiates the Structure according to what its on the file
//the function iterates through a file,
//if there is something written, it will save the name and balance on the structure
//if the next line is empty, then breaks
void init_file(Person person[10]){

    FILE *file;
    
    //we just need to read here
    file = fopen("player.txt", "r");
    
    //save each element of the file if there is any
    for(int i = 0; i<100; i++){

        //save the first thing into the name, no matter if empty or not
        fscanf(file, "%s", &person[i].name);

        if(strcmp(person[i].name, "\0") == 0){

            //if i is equal to zero, then it's the first iteration, so we set the name to nothing and break
            if(i == 0){

                //current length of array
                person_length = 0;
                break;

            }else{ 

                //the legth that we want to work on the array is i
                 person_length = i;
                 break;

            }

        }

        //save balance and gain if any
        fscanf(file, "%d", &person[i].balance);
        fscanf(file, "%d", &person[i].gain);

    }

    fclose(file);
}

//This function updates the file
void update_file(Person person[10]){

    FILE *file;

    //use this two line to clear the file
    file = fopen("player.txt", "w");
    fclose(file);

    file = fopen("player.txt", "a");

    //now write in the file with the actual data
    for(int i = 0; i<person_length; i++){

        fprintf(file, "%s ",person[i].name);
        fprintf(file, "%d ",person[i].balance);
        fprintf(file, "%d\n",person[i].gain);

    }

    //close file to save changes
    fclose(file);

}

//this function returns an index of person[100] given a name
int nameIndex(char name[25], FILE *file, Person person[10]){

    //if the length is zero, then we return -1 as error, since there are no names on file
    if(person_length == 0){

        return -1;

    }else{
        
        //iterates through all the names on Structure
        for(int i = 0; i<person_length; i++){

            //if the comparison of one of them is zero, then we return its index as i
            if(strcmp(person[i].name, name) == 0){
                return i;
            }

            //if we get here, then the name is not on the file, so we return the length as index
            if(i == person_length-1){
                return person_length;
            }
        }

    }

}

//this function return 1 if the value entered is one and 2 if the value entered is 2
int yes_no(int value){

  if(value == 1){
      return 1;
  }else if(value == 2){
      return 0;
  }

}

/***TOP BALANCE***/
void top_balance(Person person[10]){

    //Write on file
    FILE *file;

    //this var saves the name temporarily
    char name[25];
 
    //open to read and write
    file = fopen("player.txt", "a");

    //get name 
    printf("What is your first name: ");
    scanf("%s", &name);

    //look for the name in file and get index using nameIndex function
    int index = nameIndex(name, file, person);
    printf("index: %d person_length: %d\n", index, person_length);

    if(index == -1){ //no names in file

        //we just add the name
        fprintf(file, "%s", name);

        //we also need to get and print the balance
        //get balance
        printf("what is your top balance: ");
        scanf("%d", &person[index].balance);

        //print balance on file
        fprintf(file, " %d",person[index].balance);

        //the length of the array changes
        person_length = 1;

        //close file to save changes
        fclose(file);

        //update the structure
        init_file(person);

    }
    //if index is equal to the person legth, we know the name is not on the file, so we add it
    else if(index == person_length && person_length != 10){ //name not in file and still space available

            //set person name to name
            strcpy(person[index].name, name);

            //print name on file with a line before
            fprintf(file, "\n%s",person[index].name);

            /***we can also ask if the name is on the file want to add balance***/

            //we also need to get and print the balance
            //get balance
             printf("\nwhat is your top balance: ");
             scanf("%d", &person[index].balance);

            //print balance on file
            fprintf(file, " %d",person[index].balance);

            //close file to save changes
            fclose(file);

             //update the structure
            init_file(person);

    }else if(index >= 0 && index <= 9){ //we have the user on file

        int val;

        //tell the user we already have it on file and ask if he/she want to are more money
        printf("\nWe already have you on file. Would you like to add more balance\?\n"\
                "Your current balance is: %d\n1)Yes\n2)No\n", person[index].balance);
        
        scanf("%d", &val);
        
        //if Yes: ask for the balance he/she wants to add
        if(yes_no(val) == 1){

            int n;

            //ask how much to add
            printf("\nHow much more balance do you want to add: ");
            scanf("%d", &n);

            //add it to his/her balance
            person[index].balance += n;

            //prompt message with their new balance
            printf("\nYour new balance is: %d",person[index].balance);

            //update the file
            update_file(person);

        }

    }else if(person_length >= 10){ //there are already ten names on file

            //if the array is full we cannot have more people
            printf("Sorry we cannot hold any more people, here are the names you can pick from: \n");

            //print all the names
            for(int j = 0; j<person_length; j++){

                printf("%s\n", person[j].name);

            }
    }

    //close file to save changes.
    fclose(file);

}

/****
GAME LOGIC ///Incomplete
****/

//this function simulates the dice throw and returns the sum of the two dices
int throw_dice(){

     printf("\npress enter to roll dice");

        //wait for enter
         getchar(); getchar();

         //simulate dice throw
        int dice1 = rand()%6 + 1;
        int dice2 = rand()%6 + 1;

         //get sum
         int sum = dice1+dice2;

        //print the values obtained from the dice and the sum of them
        printf("\nthe values of the dices are %d and %d whose sum is %d\n", dice1, dice2, sum);

        return sum;
}

//this function has three inputs: 
void play_game(int first_turn, int once, int index, Person person[10]){

    //open for this function
    FILE *file;
    file = fopen("player.txt", "a");

    //int index;

    char name[25];

    //control if user is playing or not
    int still_playing = 1;
    
    //changes after win or lose
    int new_game = 0;

    //value of keep playing selection
    int value = 0;

    while(person[index].balance>0 && still_playing == 1){

        //we only do this once
        if(once == 1){

            //get name 
            printf("\nWhat is your first name: ");

             //save in char name
            scanf("%s", &name);

            //get the index of the name
            index = nameIndex(name, file, person);
            //printf("%d", index);

            //print error message if the name is not on file
            if(index == person_length){
                printf("Your name is not on file, please top your balance first\n");
                getchar();
                break;
            }else if(person[index].balance <= 0){ //if the balance is 0 or less, then ask to add more balance
                printf("please add balance to play\n");
                break;
            }
            
            //change the var to avoid it in the next iteration
            once = 0;
        }

        //now we go to the game logic 
        int sum = throw_dice();

        //check if win or lose and if it is the first turn
        if(((sum==7||sum==11) && first_turn == 1) || (person[index].player_points == sum && first_turn != 1 && sum != 7)){

            //balance and gain increase
            person[index].balance += 10;
            person[index].gain += 10;

            //tell user the new balance
            printf("\nYou win. Your current balance is %d", person[index].balance);
            getchar();

            new_game = 1;
            
            printf("person's balance is %d", person[index].balance);
            //update the file
            update_file(person);

        }else if(((sum==2||sum==3||sum==12) && first_turn == 1) || (sum == 7 && first_turn != 1)){

            person[index].balance -= 1;
            person[index].gain -= 1;
            printf("\nYou lose. Your current balance is %d", person[index].balance);
            getchar();

            if(person[index].balance == 0){
                printf("You ran out of balance.");
                getchar();
                fclose(file);
                still_playing = -1;
                break;
            }

            new_game = 1;

            //update file
            update_file(person);

        }else if(first_turn == 1){

            person[index].player_points = sum;
            printf("Now you have to roll %d to win\n", person[index].player_points);

        }

        //ask the user if she/he wants to keep playing
        value = 0;

        //prompt the options
        printf("\n1) Keep playing.\n"\
                "2) Quit to game menu\n");
        //get the value
         scanf("%d", &value);
         printf("value is %d\n", value);
        
        //check if the user wants to keep playing
        if(value == 1 && new_game == 1){
            
            //call play game as new instance with known index and after once
            play_game(1,0,index,person);

        }else if(value == 1){

            //play_game(first_turn,once,index)
            play_game(0,0,index,person);

        }
        else if(value == 2){
            
            printf("quit game\n");
            //getchar();
            fclose(file);
            return;
            still_playing = -1;
            //break;

        }   

        printf("\n%d\n", still_playing);

    }

}

/////End of GAME LOGIC

void top_five(int balance_price, Person person[10]){
    //This function does the same as top five by balance and top five by price
    typedef struct{

        char name[25];
        int balance;
        int gain;

    } TOP_FIVE;

    typedef struct{
        
        char name[25];
        int balance;
        int gain;

    }AUX;

    TOP_FIVE top_balance[5];
    TOP_FIVE top_price[5];
    AUX aux[10];

    int count = 0;
    
    //copy main struct person into aux
    for(int i = 0; i<person_length; i++){

        strcpy(aux[i].name, person[i].name);
        aux[i].balance = person[i].balance;
        aux[i].gain = person[i].gain;

    }
    
    //if balance_price == 1, the top five balance
    if(balance_price == 1){

         //at the end of the loop, top five will be populated with the top players by balance
         while(count<5){

             //pass the biggest value to top five
            int greatest = 0;
        
            //this contains the index of the highest number
            int g_index;
       
            for(int i = 0; i<person_length; i++){

                 if(aux[i].balance>greatest){

                    greatest = aux[i].balance;
                    g_index = i;

                }

             }

            //set the greatest value on the top five 
            strcpy(top_balance[count].name , aux[g_index].name);
            top_balance[count].balance = aux[g_index].balance;

            //set it to zero for next iteration
            aux[g_index].balance = 0;

            //move the count
            count++;

        }

        //then print the top five structure array
        for(int i = 0; i<5; i++){

            printf("%s", top_balance[i].name);
            printf(" %d\n", top_balance[i].balance);

        }
    }
   
    else if(balance_price == 2){
        //at the end of the loop, top five will be populated with the top players by balance
        while(count<5){

            //pass the biggest value to top five
            int greatest = 0;
        
            //this contains the index of the highest number
            int g_index;
       
            for(int i = 0; i<person_length; i++){

                 if(aux[i].gain>greatest){

                    greatest = aux[i].gain;
                    g_index = i;

                }

            }

            //set the greatest value on the top five 
            strcpy(top_price[count].name , aux[g_index].name);
            top_price[count].gain = aux[g_index].gain;

            //set it to zero for next iteration
            aux[g_index].gain = 0;

            //move the count
            count++;

    }

        //then print the top five structure array
        for(int i = 0; i<5; i++){

            printf("%s", top_price[i].name);
            printf(" %d\n", top_price[i].gain);

        }
    }
}

int main(void){

    Person person[20];

    //initialize structure
    init_file(person);
    
    //main menu
    int menu_var;

    while(1){

        //print menu
        printf("\nPlease select and option:\n"\
        "0) top up your balance\n"\
        "1) play game\n"\
        "2) top 5 players by balance\n"\
        "3) top 5 winners by what they have won\n" \
        "4) exit the game.\n");
    
        //scan var
        scanf("%d", &menu_var);

        
        //menu control
        switch(menu_var){

            case 0: top_balance(person);
            break;

            case 1: play_game(1,1,0,person);
            break;

            case 2: top_five(1,person);
            break;

            case 3: top_five(2,person);
            break;

            case 4: exit(0);
            break;

            default: printf("wrong option\n");
            break;

        }
    
    }

    return 0;
}
