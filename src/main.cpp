
#include "Time.h"

#include "GameKernel.h"


int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    int res = GameKernel::StartGame();

    return res;

}
