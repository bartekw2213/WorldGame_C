#pragma once
#include <termios.h>    // Linux
// #include <conio.h>      // Windows
#include "GameUtils.h"

class Input {
    private: 
        // ===============
        //      Linux
        // ===============
        struct termios echoMode;
        struct termios noEchoMode;
    public:
        Input();
        int GetGameKeyPresses();
    private:
        void SetEchoMode();
        void SetNoEchoMode();
};
