//
// Created by nik on 10.10.2021.
//

#ifndef TETRIS_TWIDGET_H
#define TETRIS_TWIDGET_H

#include "../GObj.h"
#include "TField.h"

class TWidget: public GObj {
public:
    TWidget(int iLeft, int iTop, int iWidth, int iHeight, float iRectSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processEvent(float iTime, int iEventIdx) override;;
    void setNextTShape(std::shared_ptr<TShape> iNextShape);
    ~TWidget() final = default;
private:
    enum Text{
        GameName,
        ScoreName,
        Score,
        GameOver,
        Start,
        TryAgain
    };
    void initMiniGrid();
    void markNextShape();
    float rectSize;
    float squareFieldSize;
    std::shared_ptr<TShape> nextShape;
    std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> miniGrid;
    const int fontSize = 24;
    std::vector<sf::Text> texts;
    sf::IntRect rect;
    sf::Font font;
    //TODO: add proper filename
    const std::string fontFilename = "/home/nik/c++/Tetris/Tetris/Tetris/TetrisGame/Data/retro.ttf";
};


#endif //TETRIS_TWIDGET_H
