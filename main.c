/* Name: Yeison Rodriguez
 * Class: CS 1324.001
 * Date Due: December 8th, 2019
 * Description:  given a set of text documents with clinical trial data, with a number of drug
& dose information on each trial patient, this program will be able to compute and predict drug absorption.
Elimination, and concentration at time t for a particular drug on a particular patient with given drug ID and patient ID.
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
// PATHSIZE preprocessor is used for the file path array size
#define PATHSIZE 200
// SIZE preprocessor is used for the size of any other array
#define SIZE 30

// Create a struct called patient, which will hold variable types D, V, C, F, A, E, & t. The values of these variables for each
// patient will be read in from the info file
struct patient{
    // we made each variable a float data type as a precaution, and then created three more float variables to store the
    // absorption part, elimination part, and the concentration at time t equation
   float D, V, C, F, A, E, t, absorptionPart, eliminationPart, concentrationT;


};
// Create char function printMenu() which will be used to print the menu each time it's called, and return the choice of the user from the menu
char printMenu()
{
    char choice;
    printf("Choose an option from the main menu: \n");
    printf("Option a: \"Enter the data file Location\" \n");
    printf("Option b: \"Enter a Drug ID & Patient ID\" \n");
    printf("Option c: \"Display Drug info\" \n");
    printf("Option d: \"Get time\" \n");
    printf("Option e: \"Get Pharmacokinetics Info\" \n");
    printf("Option f: \"Get drug concentration at time t\" \n");
    printf("Option g: \"Done inputing code, exit the programs\" \n");
    scanf("%c", &choice);
    return choice;

}
int main() {
    // Create file pointer which will be used to point a patient info file
    FILE *cfPtr;
    // Create char choice to hold the user's choice from whenever the printMenu function is called
    // Create char arrays filePath & fileName to hold the strings for the file path/location & the name of the file
    char choice, filePath[PATHSIZE], fileName[SIZE];
    // Declare pat of variable type patient, pat will be used to store the values read in from the file
    struct patient pat;
    // Create int variables drugID & patID, which will be used to hold the user entered drug ID & patient ID respectively
    int drugID, patID, count = 0;
    // Create a do while loop, which will loop until the user wishes to exit the program (choice g)
    do {
        // Call the printMenu function at the start of each loop, and hold the returned value in choice variable
        choice = printMenu();
        // Create a switch dependent on variable choice, which will have different cases for each option available in the menu
        switch (choice) {
            // This switch statement will not be case sensitive to mitigate some user error
            case 'A':
            case 'a':

                count = 0;
                // If the user chose case A prompt them for the file location (full path) and store user input in filePath char array
                printf("Enter the file location (full path): ");
                scanf("%s", filePath);

                // Increment the count, so that the program knows the user has already chosen option a
                count++;
                // then break
                break;

            case 'B':
            case 'b':
                // If the user chose case b, Prompt them to enter in the drug ID and store it within the drugID variable
                printf("Enter in the drug ID: ");
                scanf("%04d", &drugID);
                // Then prompt them to enter in the patient ID and store their input in the patID variable
                printf("Enter in the patient ID: ");
                scanf("%02d", &patID);
                //Increment the count so that our code is aware that we have already chosen option b
                count++;
                // then break
                break;

            case 'C':
            case 'c':
                // IF the count is less than 2, then we know that we haven't done option a or option b, so we can not continue and alert the user
                if(count < 2)
                {
                    printf("Option c is dependent on options a & b, please first complete these two \n");
                    break;
                }
                // If the user chose option c, use the sprintf() function to combine the drugID & patID variables into the
                // file name variable (i used  sprintf and not itoa because my compiler would not recognize the itoa function
                sprintf(fileName, "\\%04d_%02d_info.txt", drugID, patID);
                // Then use the strcat() function to combine the filepath string & the fileName string into one string in filePath
                strcat(filePath, fileName);
                // Then check if the file filePath could not be opened, if it couldn't print out that the file could not be opened
                if ((cfPtr = fopen(filePath, "r")) == NULL) {
                    printf("%s could not be opened\n Please try entering the file path, Drug ID & patient ID again. Or exit the program \n", filePath);
                    break;
                }
                    // Else
                else {
                    // Scan in the first line character by character until we reach a new line, and discard everything read in
                    // This will discard the first line so that we may access the data provided in the files
                    fscanf(cfPtr, "%*[^\n]");
                    fgetc(cfPtr);
                    // Then while we do not read in an end of file from our file
                    while (!feof(cfPtr)) {
                        // Read in the data and then print out the values stored in each variables
                        fscanf(cfPtr, "%f%f%f%f%f%f%f", &pat.D, &pat.V, &pat.C, &pat.F, &pat.A, &pat.E, &pat.t);
                        // reading in character by character, so that if there is a missing value in the text file, it will be filled in by zero
                        fgetc(cfPtr);
                        // If the file returned a value of 0.0 for pat.E, it was one of the files missing E & t, so we will print an error statement alerting the user
                        if (pat.E == 0.0 || pat.t < 0) {
                            printf("This file has incorrect formatting or data, exit the program or enter a new file \n");

                        } else {
                            printf("%6.1f%6.1f%6.3f%6.3f%6.3f%6.3f%6.1f \n", pat.D, pat.V, pat.C, pat.F, pat.A, pat.E,pat.t);
                        }

                    }
                    // Close the file after we read in an end of file marker
                    fclose(cfPtr);
                }
                //Increment count by one
                count ++;
         // then break
                break;
            case 'D':
            case 'd':
                // IF the count is less than 3, then we know that we haven't done option a, b or c, so we can not continue and alert the user
                if(count < 3)
                {
                    printf("Option d is dependent on options a, b & c, please first complete these three \n");
                    break;
                }
                // For case d, prompt the user to enter the time at which to compute pharmacokinetics info
                printf("Enter the time at which to compute pharacokinetic info: ");
                // store the value entered in time variable
                scanf("%f", &pat.t);
                // Increment count, and then break.
                count++;
                break;
            case 'E':
            case 'e':
                // IF the count is less than 4, then we know that we haven't done option a, b, c, or d so we can not continue and alert the user
                if(count < 4)
                {
                    printf("Option e is dependent on options a, b, c, & d, please first complete these four \n");
                    break;
                }
                // Print a table of the data we read in from the file
                printf("   D     V     C     F     A     E     t \n");
                printf("%6.1f%6.1f%6.3f%6.3f%6.3f%6.3f%6.1f \n \n", pat.D, pat.V, pat.C, pat.F, pat.A, pat.E, pat.t);
                // Use the equation given in the rubric, absorption part = A * F * D * e^(-At), to find the absorption part at time t
                pat.absorptionPart = pat.A*pat.F*pat.D*exp(-pat.A*pat.t);
                // print out the absorption part
                printf("%.3f is the absorption part at time t = %.1f \n", pat.absorptionPart, pat.t);
                // then use the equation given by the rubric, Elimination part =  = E * V * C, to find the elimination part at time t
                pat.eliminationPart = pat.E*pat.V*pat.C;
                printf("%.3f is the elimination part at time t = %.1f \n", pat.eliminationPart, pat.t);
                // Increment count & break.

                break;
            case 'F':
            case 'f':
                // option f is also dependent on a, b, c, & d. So if count is still less than four, we can not do option f either and alert the user
                if(count < 4)
                {
                    printf("Option f is dependent on options a, b, c, & d. Please first complete these four \n");
                    break;
                }
                 // Use the equation given by the rubric, Concentration(t) = 533.3*(e^(-.4t) - e^(-.5t)), to find the concentration at time t
                 pat.concentrationT = 533.3*(exp(-.4*pat.t) - exp(-.5*pat.t));
                 // Then print out the concentration at time t
                 printf("%.3f is the concentration at time t = %.1f \n", pat.concentrationT, pat.t);
                 break;
            case 'G':
            case 'g': // Case g was used as an exit case, where if the user was done inputting code they may exit the program
                printf("You have chosen to exit the program! \n");
                break;
            default: // The default case was used to catch any incorrect input at the option menu, prompting the user to try again
               printf("You have chosen an incorrect input, please try to enter a correct input ");
               break;

        }
        // The loop will run while the user has not chosen the exit program choice
    }while(choice != 'g' && choice != 'G');
    return 0;
}