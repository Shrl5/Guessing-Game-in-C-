#include <iostream>//for standard input and output.
#include <cstdlib>//for random number generating : srand() , rand() 
#include <ctime>//for gathering the local time used for number generator.
#include <stdlib.h>//for compatibility reasons only..
//#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

int random,lifes;
//random publically declared so it can be used inside multi functions, lifes too.
//random stands for random number generated, lifes for the amount of tries.
bool onetime = true;
//this variable declared publically so that it can be used without getting into game's function.
//the below function is for compatible clearing console on all platforms.
void cls() {
#ifdef _WIN32
    system("cls");
#elif _WIN64
    system("cls");
#elif __APPLE__
    system("clear");
#else
    system("clear");
#endif
}
//this is the welcome message, made it as a function so it doesn't take space from int main().
void hello() {
    cout << "This is a number guessing game, which means you have to guess a number";
    cout << "\nbetween (0 - 150), and each time you guess wrong that'll count as a mistake.";
    cout << "\nthough the system will tell you if you're close or not by some comments like";
    cout << "\n\n(Very Cold, Cold, Hot, Very Hot or EXTREMLY HOT! and that's the closest.)";
    cout << "\n\nThis game's made by Ghazwan, I'll appreciate any feedback or suggestions.";
    cout << "\n\nMy Telegram's user : @Shrlbo5 .";
    cout << "\nHave a good time :)" << endl << endl;
}
//this function is used to print arrays, used like this: print_array(array name, size of an array);
void print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << "\t";
        if ((i+1) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}
//this function is used to randomly generate a number.
void random_generator() {
    srand(time(0));
    random = rand() % 150;//150 means the number is from 150 to 0.
}
//the following function is to ask the player to enter a number of lifes.
void lifes_decider(int& lifes) {
    //remove the (//) below if you want the player to decide the tries only 1 time.
    //onetime = false;
    cout << "Enter your tries amount, Type (0) for unlimited: ";
    while (true) {//as usual, the input checking loop.
        cin >> lifes;
        if (cin.fail()) {
            cout << "Please enter numbers only: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (lifes < 0) {
            cout << "You can't enter nigative numbers.. Re-enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    //cls();
    if (lifes == 0) {
        cout << "You've set amount of tries to unlimited." << endl;
        lifes = 150;//150 means unlimited.
    }
    else if(lifes > 150) {
        lifes = 150;
        cout << "You can't go past (150), so your tries amount is unlimited." << endl;
    }
    else{
        cout << "You've set amount of tries to: " << lifes << endl;
    }
}
//this function is where the game's script is stored at.
void game_starting(int lifes) {
    int gss[151], size = 0, x,elnum;
    bool found, failed = false;
    /*
    every variable and what it's use :
    elnum = used to make a shortcut in line 160.
    gss = the guesses array, it's where all of the users inputs are stored at.
    size = the size of the gss array, also it's the time numbers of inputs.
    x = it's where the input stored at before the checking process is complete,
    then it's stored into gss next element.
    found = used to check if the input is duplicated or not..
    failed = used to tell that the player has ran out of tries.
    */
    if (lifes == 150) {
        cout << "You're on Unlimited tries..\n" << endl;
    }
    cout << "Try to guess the number. ^^" << endl;
    for (int i = 0; i <= lifes; i++) {
        if (i == lifes) {
            failed = true;
        }
        else {
            if (lifes != 150) {
                cout << lifes - i << " tries left.\n" << endl;
            }
            while (true) {//this loop is just for cin error checking
                cin >> x;
                if (cin.fail()) {
                    cout << "Error ! please enter numbers only: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else if (x < 0 || x > 150) {//the range checker
                    cout << "Enter a number between (0 - 150) only: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else { //if everything goes fine and no input errors. this loop will end.

                    break;
                }
            }
            found = false; //this bool function to check if input is duplicated
            for (int j = 0; j < i; j++) {
                //this for loop to make sure no element in the array equals to inputted num.
                if (gss[j] == x) {
                    //if input's duplicated then it'll change found variable into true.
                    found = true;
                    break;
                }
            }
            if (found) {
                //this if statment is here if found variable is true, it'll reset the main for loop and ignore
                //the inputted number.
                cout << "You've entered this guess already, please enter another guess: ";
                i--;
            } else {
                gss[i] = x;
                size++;
                //these are the if's that makes the game, everything above is just for checking.
                if (gss[i] == random) {
                    // when guess is correct this will happen.
                    cls();
                    cout << "Hurray !! you're correct.." << endl;
                    cout << "You've guessed " << size << " times to reach the correct answer." << endl;
                    cout << "\nYour guesses : \n";
                    print_array(gss, size);
                    break;
                } else if (gss[i] > random || gss[i] < random) {
                    //here's the higher statement.
                    elnum = gss[i] - random;
                    if (elnum <= 2 && elnum >= 1 || elnum >= -2 && elnum <= -1) {
                        //if the number is within the range of 2 from the correct guess, it'll print "Fuming !!!".
                        cout << "(" << gss[i] << ") is EXTREMELY HOT!" << endl;
                    } else if (elnum <= 12 && elnum >= 1 || elnum >= -12 && elnum <= -1) {
                        //if the number is within the range of 12 from the correct guess, it'll print "Hotter".
                        cout << "(" << gss[i] << ") is Very Hot" << endl;
                    } else if (elnum <= 20 && elnum >= 1 || elnum >= -20 && elnum <= -1) {
                        //if the entered number is between 6 - 20 numbers than correct guess, it'll print "Hot".
                        cout << "(" << gss[i] << ") is Hot" << endl;
                    } else if (elnum > 20 && elnum <= 60 || elnum < -20 && elnum >= -60) {
                        //if the entered number is in range between 21-60, it'll print "Cold".
                        cout << "(" << gss[i] << ") is Cold" << endl;
                    } else {
                        //if the entered number is higher than a minimum of 20 numbers from the correct guess, it'll print "Very Cold".
                        cout << "(" << gss[i] << ") is Very Cold" << endl;
                    }
                }
            }
        }
    }
    //if out of tries.
    if (failed) {
        cls();
        cout << "You've Failed .." << endl;
        cout << "The correct answer is: " << random << endl;
        cout << "Good luck with the next games..\n" << endl;
    }
    //for stopping console at the end of a valid execution.
    system("pause");
    cls();
}
//this function used if the player's chosed to hack the game.
void hack() {
    char ct;
    cout << "Do you want to play wih answer hacking activated? (y,n)" << endl;
    while (true) {
        cin >> ct;
        //to ensure that "ct" is a right input.
        if (cin.fail() || ct != 'Y' && ct != 'y' && ct != 'N' && ct != 'n') {
            cout << "Error ! please type either (y/n) : ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            //to ignore every character after a successful y or n input.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    cls();
    switch (ct) {
    case 'y':
    case 'Y':
        cout << "The correct number is : " << random << "\n\n";
        break;
    case 'n':
    case 'N':
        break;
    }
    
}
//this function used to replace int main() function, so the game can be put inside of a loop.
void main_logic(bool &quitter) {
    char st;
    random_generator();//this'll generates a random number.
    
    hello();
    cout << "\nType (S) to start the game, (Q) for quitting." << endl;
    while (true) { //the cin for starting the game or quitting.
        cin >> st;
        //to ensure that "st" is a right input.
        if (cin.fail() || st != 'S' && st != 's' && st != 'Q' && st != 'q') {
            cout << "Error ! please type either (S/Q) : ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            //to ignore every character after a successful s or q input.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    //if quitting is chosed, this'll end the program.
    if (st == 'Q' || st == 'q') {
        quitter = true;
        return;
    }
    //starting the game.

    cls();

    if (onetime) {
        lifes_decider(lifes);
    }
    
    //activate the cout below for hacking.(remove //)
    hack();
    game_starting(lifes);  //the actual game function.

}
//this is the main function.
int main() {
    bool quitter = false;
    while (true) {
        main_logic(quitter);
        if (quitter)
            break;
    }
    return 0;
}