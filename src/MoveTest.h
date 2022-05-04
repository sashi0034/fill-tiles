//
// Created by sashi0034 on 2022/04/29.
//

#ifndef SDL2_IMAGE_SAMPLE_MOVETEST_H
#define SDL2_IMAGE_SAMPLE_MOVETEST_H


#include <SDL_surface.h>


class MoveTest {
private:
    const int animeCycle = 200;
    const int imageWidth = 24;
    const int imageHeight = 24;

    SDL_Surface* m_Image = nullptr;
    SDL_Texture* m_ImageTexture = nullptr;
    SDL_Renderer *m_Renderer;
    int m_Frame = 0;

    double m_X=0;
    double m_Y=0;

    void changeFrame(int deltaTime);
public:
    MoveTest(SDL_Renderer *renderer);
    ~MoveTest();

    void Test();


    void Update(int deltaTime, const Uint8* state);
    void Render();

};


#endif //SDL2_IMAGE_SAMPLE_MOVETEST_H
