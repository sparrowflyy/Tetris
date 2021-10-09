//
// Created by nik on 04.10.2021.
//
#ifndef TETRIS_TBACKGROUND_H
#define TETRIS_TBACKGROUND_H
#endif //TETRIS_TBACKGROUND_H
#include "../GObj.h"
class TBackground: public GObj {
public:
    TBackground(int iWinWidth, int iWinHeight, const std::vector<std::string>& iFileNames);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processEvent(float iTime, int iEventIdx) override;
    void revertLastEvent() override;
    ~TBackground() final;
};