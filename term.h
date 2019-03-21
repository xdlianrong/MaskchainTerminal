#include <iostream>
#include <string>
#include <stdlib.h>

namespace msk {
    #define CLEAR() printf("\033[2J")
    // 上移光标
    #define MOVEUP(x) printf("\033[%dA", (x))
    // 下移光标
    #define MOVEDOWN(x) printf("\033[%dB", (x))
    // 左移光标
    #define MOVELEFT(y) printf("\033[%dD", (y))
    // 右移光标
    #define MOVERIGHT(y) printf("\033[%dC",(y))

    #define GrayBold "\x1b[1;37m"   // text style
    #define StyleReset "\x1b[0m"          
    #define GreenBold "\x1b[1;32m"

    #define Black "\x1b[30m"        // Black
    #define Coal "\x1b[90m"       // Black
    #define Gray "\x1b[37m"        // White
    #define White "\x1b[97m"       // White
    #define Maroon "\x1b[31m"          // Red
    #define Red "\x1b[91m"         // Red
    #define Green "\x1b[32m"        // Green
    #define Lime "\x1b[92m"       // Green
    #define Orange "\x1b[33m"       // Yellow
    #define Yellow "\x1b[93m"      // Yellow
    #define Navy "\x1b[34m"         // Blue
    #define Blue "\x1b[94m"        // Blue
    #define Violet "\x1b[35m"       // Purple
    #define Purple "\x1b[95m"      // Purple
    #define Teal "\x1b[36m"         // Cyan
    #define Cyan "\x1b[96m"        // Cyan

    #define BlackBold "\x1b[1;30m"       // Black
    #define CoalBold "\x1b[1;90m"      // Black
    #define WhiteBold "\x1b[1;97m"      // White
    #define MaroonBold "\x1b[1;31m"         // Red
    #define RedBold "\x1b[1;91m"        // Red
    #define LimeBold "\x1b[1;92m"      // Green
    #define OrangeBold "\x1b[1;33m"      // Yellow
    #define YellowBold "\x1b[1;93m"     // Yellow
    #define NavyBold "\x1b[1;34m"        // Blue
    #define BlueBold "\x1b[1;94m"       // Blue
    #define VioletBold "\x1b[1;35m"      // Purple
    #define PurpleBold "\x1b[1;95m"     // Purple
    #define TealBold "\x1b[1;36m"        // Cyan
    #define CyanBold "\x1b[1;96m"       // Cyan
}