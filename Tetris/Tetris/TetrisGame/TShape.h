#pragma once
#include "../GObj.h"

namespace Tetris {
	static const int shapeParts = 4;
	enum ShapeType
	{
		Line,
		ZigZagLeft,
		ZigZagRight,
		Rect,
		T
	};
	
	class TShape : public GObj
	{
	public:
		TShape(int iType, const sf::Vector2i& iCenter = sf::Vector2i(200, 0));
		void update(float iTime) override {};
		const std::vector<sf::Drawable*>& getDrawable() const override;
		bool isActive = true;
		int type;
	private:
		void initLine(const sf::Vector2i& iCenter);
		void initZigZagLeft(const sf::Vector2i& iCenter);
		void initZigZagRight(const sf::Vector2i& iCenter);
		void initRect(const sf::Vector2i& iCenter);
		void initT(const sf::Vector2i& iCenter);
		sf::Vector2i center;
		std::vector<std::shared_ptr<sf::RectangleShape>> m_rects;
	};

}