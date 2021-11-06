//
// Created by nik on 10.10.2021.
//
#ifndef TETRIS_TWIDGET_H
#define TETRIS_TWIDGET_H

#include "../GObj.h"
#include "TField.h"

class TWidget: public GObj {
public:
    enum State {
        GameStart,
        Game,
        GameIsOver
    };
    TWidget(int iWinWidth, int iWinHeight, int iScoreWidgetWidth, float iRectSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processEvent(float iTime, int iEventIdx) override;
    void setNextTShape(std::shared_ptr<TShape> iNextShape);
    void setState(int iState);
    ~TWidget() final = default;
private:
    enum Text{
        GameName,
        ScoreName,
        Score,
        GameOver,
        Start,
    };
    void initMiniGrid();
    void markNextShape();
    int state;
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
