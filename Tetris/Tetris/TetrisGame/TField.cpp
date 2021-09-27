#include "TField.h"
#include "TShape.h"
using namespace Field;
TField::TField(int iWinWidth, int iWinHeight)
{
	m_blockWidth = (iWinWidth - 50 )/ TetrisShapes::rectSize;
	m_blockHeight = (iWinHeight - 50)/ TetrisShapes::rectSize;

	for (int i = 0; i < m_blockWidth; i ++) {
		for (int j = 0; j < m_blockHeight; j ++) {
			auto* cell = new sf::RectangleShape(sf::Vector2f(TetrisShapes::rectSize, TetrisShapes::rectSize));
			cell->setPosition( i * TetrisShapes::rectSize - TetrisShapes::outlineThick, j * TetrisShapes::rectSize-TetrisShapes::outlineThick);
			cell->setFillColor(sf::Color::White);
			cell->setOutlineThickness(TetrisShapes::outlineThick);
			cell->setOutlineColor(sf::Color::Black);
			m_grid.push_back(*cell);
		}
	}
}
TField::~TField()
{
	//TODO: memory leaks?
	m_grid.clear();
}
void TField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& cell: m_grid)
	{
		target.draw(cell);
	}
}

void TField::markRect(short i, short j, const sf::Color &iColor) {
    int idx = m_blockWidth * i + m_blockHeight * j;
    m_grid[idx].setFillColor(iColor);
}

int TField::getMark(short i, short j) {
    int idx = m_blockWidth * i + m_blockHeight * j;
    sf::Color rectColor = m_grid[idx].getFillColor();
    if (rectColor != sf::Color::Transparent){
        return Cell::Shape;
    }
    return Cell::Empty;

}

