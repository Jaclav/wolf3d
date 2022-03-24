#include <iostream>
#include <cmath>

int main() {
    int playerX = 1, playerY = 4;

    std::string mapa[] = {"########",
                          "#   #  #",
                          "#   #  #",
                          "#  ##  #",
                          "#!     #",
                          "########"
                         };

    std::string tmp[] = {"########",
                         "#   #  #",
                         "#   #  #",
                         "#  ##  #",
                         "#!     #",
                         "########"
                        };


    for(uint i = 0; i < 8; i++) {
        for(uint y = 0; y < 6; y++) {
            for(uint x = 0; x < mapa[y].size(); x++) {

                if(std::sqrt(((playerX - x) * (playerX - x)) + ((playerY - y) * (playerY - y))) < (float)(i + 0.5) && float(i - 0.5) < std::sqrt(((playerX - x) * (playerX - x)) + ((playerY - y) * (playerY - y)))) {
                    tmp[y][x] = 8 - i + '0';
                }
            }
        }
    }

    for(uint y = 0; y < 6; y++) {
        for(uint x = 0; x < mapa[y].size(); x++) {
            std::cout << tmp[y][x];
        }
        std::cout << '\n';
    }
}