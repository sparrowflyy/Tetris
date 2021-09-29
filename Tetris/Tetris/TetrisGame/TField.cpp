#include "TField.h"
#include "../GUtils.h"

void TShape::init() {
    const sf::Color& shapeColor = getRandColor();
    indices.resize(4);
}

TShape::TShape(int iType, const sf::Vector2i& iMaxPoint) {
    type = iType;
    maxPoint = iMaxPoint;
    init();
    switch (iType)
    {
        case TShapes::Type::I:
        {
            initI();
            break;
        }
        case TShapes::Type::O:
        {
            initO();
            break;
        }
        case TShapes::Type::T:
        {
            initT();
            break;
        }
        case TShapes::Type::Z:
        {
            initZ();
            break;
        }
        case TShapes::Type::S:
        {
            initS();
            break;
        }
        case TShapes::J:
        {
            initJ();
            break;
        }
        case TShapes::L:
        {
            initL();
            break;
        }
        default:
        {
            break;
        }
    }
}

void TShape::initI()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x, maxPoint.y-1};
    indices[2] = {maxPoint.x, maxPoint.y-2};
    indices[3] = {maxPoint.x, maxPoint.y-3};
}

void TShape::initO()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x+1, maxPoint.y};
    indices[2] = {maxPoint.x, maxPoint.y-1};
    indices[3] = {maxPoint.x+1, maxPoint.y-1};
}

void TShape::initT()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x+1, maxPoint.y};
    indices[2] = {maxPoint.x-1, maxPoint.y};
    indices[3] = {maxPoint.x, maxPoint.y+1};
}
//max point at the right
void TShape::initZ()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x, maxPoint.y - 1};
    indices[2] = {maxPoint.x - 1, maxPoint.y - 1};
    indices[3] = {maxPoint.x - 1, maxPoint.y - 2};
}
//max point at the left
void TShape::initS()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x, maxPoint.y - 1};
    indices[2] = {maxPoint.x + 1, maxPoint.y - 1};
    indices[3] = {maxPoint.x + 1, maxPoint.y - 2};
}

void TShape::initJ()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x, maxPoint.y - 1};
    indices[2] = {maxPoint.x , maxPoint.y - 2};
    indices[3] = {maxPoint.x - 1, maxPoint.y - 2};
}
void TShape::initL()
{
    indices[0] = {maxPoint.x, maxPoint.y};
    indices[1] = {maxPoint.x, maxPoint.y - 1};
    indices[2] = {maxPoint.x , maxPoint.y - 2};
    indices[3] = {maxPoint.x + 1, maxPoint.y - 2};
}
const sf::Color& TShape::getRandColor()
{
    return TShapes::shapeColors[GUtils::genRandomInt(0, TShapes::shapeColors.size() - 1)];
}

/*void TShape::rotate(bool clockWise)
{
    if (type == TShapes::Type::O)
        return;
    int dir = clockWise ? 1 : -1;
    for (int i = 0; i < shapeParts; i++) {
        sf::Vector2f pos = m_rects[i].getPosition();
        float x = pos.x + rectSize / 2 - center.x;
        float y = pos.y + rectSize / 2 - center.y;
        pos.x = center.x - y*dir - rectSize / 2;
        pos.y = center.y + x*dir - rectSize / 2;
        m_rects[i].setPosition(pos);
    }

}
void TShape::moveShape(const sf::Vector2f& iMotion)
{
    for (int rectIdx = 0; rectIdx < TetrisShapes::shapeParts; rectIdx++) {
        m_rects[rectIdx].move(iMotion);
    }
    center.x += iMotion.x;
    center.y += iMotion.y;
}*/
void GTetris::genRandTShape() {
    idxActive = objects.size();
    GObj * rndShape = dynamic_cast<GObj*>(new TShape(GUtils::genRandomInt(0, TShapes::numTypes - 1)));
    //TShape* rndShape = new TShape(TetrisShapes::J);
    objects.push_back(rndShape);
}
TField::TField(int iWinWidth, int iWinHeight)
{
    fieldWidth = (iWinWidth - 50 )/ TShapes::rectSize;
    fieldHeight = (iWinHeight - 50)/ TShapes::rectSize;

	for (int i = 0; i < fieldWidth; i ++) {
		for (int j = 0; j < fieldHeight; j ++) {
            //TODO: need new?
			auto* cell = new sf::RectangleShape(sf::Vector2f(TShapes::rectSize, TShapes::rectSize));
			cell->setPosition( i * TShapes::rectSize - TShapes::outlineThick, j * TShapes::rectSize-TShapes::outlineThick);
			cell->setFillColor(sf::Color::White);
			cell->setOutlineThickness(TShapes::outlineThick);
			cell->setOutlineColor(sf::Color::Black);
			grid.push_back(*cell);
		}
	}
}

void TField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& cell: grid)
	{
		target.draw(cell);
	}
}

void TField::markRect(short i, short j, const sf::Color &iColor) {
    int idx = fieldWidth * i + fieldHeight * j;
    grid[idx].setFillColor(iColor);
}

int TField::getMark(short i, short j) {
    int idx = fieldWidth * i + fieldHeight * j;
    sf::Color rectColor = grid[idx].getFillColor();
    if (rectColor != sf::Color::Transparent){
        return Cell::Shape;
    }
    return Cell::Empty;
}

void TField::processEvent(float iTime, int iEventIdx) {

}

void TField::revertLastEvent() {

}

TField::~TField()
{
    //TODO: memory leaks?
    grid.clear();
}