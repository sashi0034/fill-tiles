//
// Created by sashi on 2022/04/29.
//

#include <SDL_image.h>
#include <iostream>
#include "MoveTest.h"

mainScene::MoveTest::MoveTest(SDL_Renderer* renderer) {
    m_Renderer = renderer;

    m_Image = IMG_Load("assets/dango_wolf_24x24.png");

    m_ImageTexture = SDL_CreateTextureFromSurface(renderer, m_Image);
    SDL_SetTextureAlphaMod(m_ImageTexture, 200);

    if (!m_Image) {
        std::cerr << "IMG_Load: %s\n", IMG_GetError();
    }
}

void mainScene::MoveTest::Test() {
    std::cout << "Nemui Nemui." << std::endl;
}

void mainScene::MoveTest::Update(int deltaTime, const Uint8* state) {
    const int speed = 1 * deltaTime;

    if (state[SDL_Scancode::SDL_SCANCODE_A])
    {
        m_X -= speed;
    }
    if (state[SDL_Scancode::SDL_SCANCODE_D])
    {
        m_X += speed;
    }
    if (state[SDL_Scancode::SDL_SCANCODE_W])
    {
        m_Y -= speed;
    }
    if (state[SDL_Scancode::SDL_SCANCODE_S])
    {
        m_Y += speed;
    }

    changeFrame(deltaTime);
}

void mainScene::MoveTest::changeFrame(int deltaTime) {

    m_Frame += deltaTime;

    if (m_Frame > animeCycle * 4) {
        m_Frame = 0;
    }
}


void mainScene::MoveTest::Render() {

    const int x = ((m_Frame / animeCycle) % 4) * 24;
    const int pixelPerUnit = 3;

    SDL_Rect imageRect = SDL_Rect{ x,0,imageWidth, imageHeight };
    SDL_Rect drawRect = SDL_Rect{ int(m_X),int(m_Y),imageWidth*pixelPerUnit, imageHeight*pixelPerUnit };

    //SDL_RenderCopy(m_Renderer, m_ImageTexture, &imageRect, &drawRect);

    const double angle = 15.0;
    const SDL_Point centerPoint{imageWidth / 4, imageHeight / 4};
    SDL_RenderCopyEx(m_Renderer, m_ImageTexture, &imageRect, &drawRect, angle, &centerPoint, SDL_FLIP_VERTICAL);
}

mainScene::MoveTest::~MoveTest() {
    SDL_FreeSurface(m_Image);
    SDL_DestroyTexture(m_ImageTexture);
}











