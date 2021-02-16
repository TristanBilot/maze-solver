#include "include/game.hpp"

#define MAP2 "\
wwwwwwwwwwwwww\
wT I w       w\
w     ww  ww w\
w     w ww w w\
w     w    w w\
w  H  w    w w\
w     wwwwwwww\
w           Tw\
w            w\
w     t      w\
w       w    w\
w       w    w\
w       w O  w\
wwwwwwwwwwwwww"

#define MAP1 "\
wwwww\
wIOHw\
w  Tw\
wtwww\
wwwww"

#define START "Choose your game mode :\nm= manual\na= ai player\n\n"

int main()
{
    std::string str2 = MAP2;
    // std::cout << str2.length();

    std::string str;

    bool correct_input = false;
    while (!correct_input)
    {
        std::cout << START;
        std::cin >> str;
        correct_input = true;
        if (str.compare("m") == 0)
        {
            manual_game game = manual_game(str2, str2.length());
            game.start_game();
        }
        else if (str.compare("a") == 0)
        {
            std::cout << "-------------- AAAAAAA -----------------";
            ai_game game = ai_game(str2, str2.length());
            game.start_game();
        }
        else {
            correct_input = false;
            std::cout << "Incorrect input, try again with m/a \n\n";
        }
    }
    return 0;
}