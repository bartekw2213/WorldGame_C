#include <cstdio>
#include "Input.h"

// ===============
//      Linux
// ===============

Input::Input() {
    tcgetattr(0, &echoMode); 
    noEchoMode = echoMode; 
    noEchoMode.c_lflag &= ~ICANON;
    noEchoMode.c_lflag &= ~ECHO;
}

void Input::SetEchoMode() {
    tcsetattr(0, TCSANOW, &echoMode);
}

void Input::SetNoEchoMode() {
    tcsetattr(0, TCSANOW, &noEchoMode);
}

int Input::GetGameKeyPresses() {
    SetNoEchoMode();

    char c = getchar();
    int keyPress = NO_PROPER_KEY;

    if(c == 'q' || c == 'Q')
        keyPress = KEY_QUIT;
    else if(c == 's' || c == 'S')
        keyPress = KEY_SUPER_POWER;
    else if(c == '\033') {
        getchar();
        switch(getchar()) { 
            case 'A': keyPress = KEY_UP; break;
            case 'B': keyPress = KEY_DOWN; break;
            case 'C': keyPress = KEY_RIGHT; break;
            case 'D': keyPress = KEY_LEFT; break;
        }
    }

    SetEchoMode();
    return keyPress;
}

// =================
//      Windows
// =================
// Input::Input() { }
// void Input::SetEchoMode() { }
// void Input::SetNoEchoMode() { } 

// int Input::GetGameKeyPresses() {
//     char c = getch();
//     int keyPress = NO_PROPER_KEY;


//     if(c == 'q' || c == 'Q')
//         keyPress = KEY_QUIT;
//     else if(c == 's' || c == 'S')
//         keyPress = KEY_SUPER_POWER;
//     else if(c == -32) {
//         switch(getchar()) { 
//             case 72: keyPress = KEY_UP; break;
//             case 80: keyPress = KEY_DOWN; break;
//             case 77: keyPress = KEY_RIGHT; break;
//             case 75: keyPress = KEY_LEFT; break;
//         }
//     }

//     return keyPress;
// }
