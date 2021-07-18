#pragma once
#include "../GObj.h"

static bool debug = true;

namespace TetrisShapes {
	static const int shapeParts = 4;
	static const int rectSize = 30;
	static const float outlineThick = 2;
	static const int numTypes = 5;
	static sf::Vector2f center{ 200,50 };
	static const std::vector<sf::Color> shapeColors {
		sf::Color(153,0,153), //purple
		sf::Color(204,255,51),	//yellow
		sf::Color(0,255,102), //green
		sf::Color(151,53,255),	//blue
		sf::Color(255,51,153)	//pink
	};
	enum ShapeType
	{
		Null,
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
		TShape(int iType, const sf::Vector2f& iCenter = TetrisShapes::center);
		void update(float iTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		int type;
		const sf::Color& getRandColor();
		void init();
	  void rotate();
		void initLine(const sf::Vector2f& iCenter);
		void initZigZagLeft(const sf::Vector2f& iCenter);
		void initZigZagRight(const sf::Vector2f& iCenter);
		void initRect(const sf::Vector2f& iCenter);
		void initT(const sf::Vector2f& iCenter);

	protected:
		sf::Vector2f center;
		std::vector<sf::RectangleShape> m_rects;

	};


	class TBackGround : public GObj
	{
	public:
		
	};