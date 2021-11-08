//
// Created by nik on 04.10.2021.
//
#include "TBackground.h"


TBackground::TBackground(int iWinWidth, int iWinHeight, const std::vector<std::string> &iFileNames) {
  for (const auto& fileName : iFileNames){
    sf::Image img;
    img.loadFromFile(fileName);
    auto textPtr = std::make_shared<sf::Texture>();
    auto spritePtr = std::make_shared<sf::Sprite>();
    textPtr->loadFromImage(img);
    spritePtr->setTexture(*textPtr);
    float factorX = float(iWinWidth)/float(spritePtr->getLocalBounds().width);
    float factorY = float(iWinHeight)/float(spritePtr->getLocalBounds().height);
    spritePtr->setScale(factorX,factorY);
    textures.push_back(textPtr);
    sprites.push_back(spritePtr);
  }
}

void TBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto& back: sprites)
    target.draw(*back);
}

void TBackground::processEvent(int iEventIdx) {

}

TBackground::~TBackground() {

}
