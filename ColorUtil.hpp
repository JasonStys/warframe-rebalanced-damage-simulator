#ifndef COLOR_UTIL_HPP
#define COLOR_UTIL_HPP

#include <iostream>

class ColorUtil {
public:
    enum Color {
        LIGHT_GRAY,
        YELLOW,
        ORANGE,
        RED,
        BLUE
    };

    static void setColor(Color color) {
        switch (color) {
            case LIGHT_GRAY:
                std::cout << "\033[37m";
                break;
            case YELLOW:
                std::cout << "\033[33m";
                break;
            case ORANGE:
                std::cout << "\033[38;5;208m";
                break;
            case RED:
                std::cout << "\033[31m";
                break;
            case BLUE:
                std::cout << "\033[34m";
                break;
        }
    }

    static void resetColor() {
        std::cout << "\033[0m";
    }
};

#endif // COLOR_UTIL_HPP
