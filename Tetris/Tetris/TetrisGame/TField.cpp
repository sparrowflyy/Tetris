#include "TField.h"
#include "TShape.h"

TField::TField(int iWinWidth, int iWinHeight)
{
	int rowCount = (iWinWidth - 50 )/ TetrisShapes::rectSize;
	int colCount = (iWinHeight - 50)/ TetrisShapes::rectSize;

	for (int i = 0; i < rowCount; i ++) {
		for (int j = 0; j < colCount; j ++) {
			sf::RectangleShape* cell = new sf::RectangleShape(sf::Vector2f(TetrisShapes::rectSize, TetrisShapes::rectSize));
			cell->setPosition( i * TetrisShapes::rectSize - TetrisShapes::outlineThick, j * TetrisShapes::rectSize-TetrisShapes::outlineThick);
			cell->setFillColor(sf::Color::Transparent);
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
