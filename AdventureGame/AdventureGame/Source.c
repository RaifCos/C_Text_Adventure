// #define included to ensure sscanf works.
#define _CRT_SECURE_NO_DEPRECATE  

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void readLocations();
void playerTurn();
void playerInput();
void processInput();
int getArraySize(int arr[]);

struct location {
    int id;
    int destination[3];
    char name[99];
    char description[99];
};
struct location l[4];

FILE* ptr;
int local = 3;
int endCondition = 0;
char input[15];

void main()
{
    //Opening Location File.
    fopen_s(&ptr, "adventure_locations.txt", "r");
    if (ptr == NULL) { printf("Failed to read in Locations."); } 
    else {
        //If Condition is Passed. Locations are read in and the File is closed.
        readLocations();
        fclose(ptr);

        //Game runs on a Loop until the player quits.
        printf("\n=== Welcome to my Text Adventure Test. Take a look around! ===\n");
        while (endCondition == 0) { playerTurn(); }
        printf("\n=== Come Back Soon! ===\n");
    }
}

//readLocations reads in each location and stores it in the established Array.
void readLocations()
{
    int i = 0;
    char line[200];
    while (fgets(line, 99, ptr) != NULL) {
        //Reads all Location Lines and their respective values, and saves them in the Struct Array
        if (i >= 2) {
            char tempString[99];
            int j = 0;
            sscanf(line, "%d\t %[^\t] %[^\t] %[^\n]", &l[i - 2].id, &tempString, &l[i - 2].name, &l[i - 2].description);

            char* token = strtok(tempString, " ");
            while (token != NULL) {
                l[i - 2].destination[j] = atoi(token); // Convert token to integer and store in array
                token = strtok(NULL, " ");
                j++;
            }
        } i++;
    } printf("Read in %d Locations.\n", i - 3);
}

void playerTurn() {
    // Display the Player's current information
    printf("\nYou are at the %s.\nWhat do you want to do?", l[local].name);
    // Call for the Player's Input, and process said input into a Command. 
    playerInput();
    processInput();
}

void playerInput() {
    // Get a String Input from the Player.
    printf("\n> ");
    gets(&input);

    // Convert Input into Uppercase to simplify comparisons. 
    for (int i = 0; i < strlen(input); i++) {
        input[i] = toupper(input[i]);
    }
}

// processInput carries out an action based on the Players Input (Moving, Items, Help, Etc.)
void processInput()
{
    // Input is compared with each Command, and returns a failure message if there is no match.
    // MOVE: Allows the Player to move between Locations.
    if (strcmp(input, "MOVE") == 0 || strcmp(input, "M") == 0) {
        // List all Possible Destinations the player can travel to from their current Location. 
        printf("\nSelect a loction to travel to, or BACK to return:\n");
        for (int i = 0; i < getArraySize(l[local].destination); i++) {
            if (l[local].destination[i] != 0) { printf("-%s\n", l[l[local].destination[i]].name); }
        }
        playerInput();
        if (strcmp(input, "BACK") == 0) { return; }
        for (int i = 0; i < getArraySize(l[local].destination); i++) {
            if (strcmp(input, (l[l[local].destination[i]].name)) == 0) { local = l[l[local].destination[i]].id; return; }
        } printf("Not a Valid Location!");
    } // ERROR: The Input is not a valid Command. 

    if (strcmp(input, "LOOK") == 0 || strcmp(input, "L") == 0) {
        printf("\n%s", l[local].description);
        return;
    }

    if (strcmp(input, "QUIT") == 0 || strcmp(input, "Q") == 0) {
        printf("\nAre you sure you want to Quit? All Progess will be lost. Type QUIT again to confirm. ");
        playerInput();
        if (strcmp(input, "QUIT") == 0) { endCondition = 1; }
        return;
    }

    if (strcmp(input, "HELP") == 0 || strcmp(input, "H") == 0) {
        printf("\nHere's a list of all Commands you can use:\n");
        printf("MOVE (M): Travel to a nearby Location.\n");
        printf("LOOK (L): Look around your current Location.\n");
        printf("QUIT (Q): Exit the Game.\n");
        printf("HELP (H): Get a List of Commands.\n");
    }

    else { printf("\nNot a valid Input! Type HELP for a list of Commands."); }
}

int getArraySize(int arr[]) {
    return (sizeof(arr) / sizeof(arr)[0]);
}