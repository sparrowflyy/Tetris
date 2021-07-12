#pragma once
#include "../GObj.h"

namespace TetrisShapes {
	static const int shapeParts = 4;
	static const int rectSize = 30;
	static const float outlineThick = 2;
	static const int numTypes = 5;
	static const std::vector<sf::Color> shapeColors {
		sf::Color(153,0,153), //purple
		sf::Color(204,255,51),	//yellow
		sf::Color(0,255,102), //green
		sf::Color(151,53,255),	//blue
		sf::Color(255,51,153)	//pink
	};
	enum ShapeType
	{
		Line,
		ZigZagLeft,
		ZigZagRight,
		Rect,
		T
	};
}
	class TShape : public GObj
	{
	public:
		TShape(int iType, const sf::Vector2f& iCenter = sf::Vector2f(200.0, 50.0));
		void update(float iTime) override;
		int type;
		const sf::Drawable* getDrawable(int idx) const override;
	private:
		const sf::Color& getRandColor();
		void initRectangles();
		void initLine(const sf::Vector2f& iCenter);
		void initZigZagLeft(const sf::Vector2f& iCenter);
		void initZigZagRight(const sf::Vector2f& iCenter);
		void initRect(const sf::Vector2f& iCenter);
		void initT(const sf::Vector2f& iCenter);
		sf::Vector2f center;
		std::vector<std::shared_ptr<sf::RectangleShape>> m_rects;
	};

	class TBackGround : public GObj
	{
	public:
		
	};