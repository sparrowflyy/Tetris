#pragma once
#include "../GObj.h"

static bool debug = true;

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
		TShape(const sf::Vector2f& iCenter = sf::Vector2f(200.0, 50.0));
		void update(float iTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		int type;
		static TShape* create(int iType);
		const sf::Color& getRandColor();
		virtual void init();
		virtual void rotate(float iAngle) {};
		//virtual void rotateLeft() {}
		//virtual void rotateRight() {}
		/*void initLine(const sf::Vector2f& iCenter);
		void initZigZagLeft(const sf::Vector2f& iCenter);
		void initZigZagRight(const sf::Vector2f& iCenter);
		void initRect(const sf::Vector2f& iCenter);
		void initT(const sf::Vector2f& iCenter);*/
		sf::Vector2f center;
		std::vector<sf::RectangleShape> m_rects;
		std::vector<sf::Transform> m_rectTransforms;
	};

class TShapeT: public TShape
{
public:
	TShapeT(const sf::Vector2f& iCenter = sf::Vector2f(200.0, 50.0));
	void init() override;
	void rotate(float iAngle) override;
	//void rotateLeft() override;
	//void rotateRight() override;
	
};



	class TBackGround : public GObj
	{
	public:
		
	};