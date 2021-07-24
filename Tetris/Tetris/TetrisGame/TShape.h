#pragma once
#include "../GObj.h"

static bool debug = true;

namespace TetrisShapes {
	static const int shapeParts = 4;
	static const int rectSize = 30;
	static const float outlineThick = 2;
	static const int numTypes = 7;
	static const float shapeSpeed = 100;
	static sf::Vector2f center{ 200,100 };
	static const std::vector<sf::Color> shapeColors {
		sf::Color(153,0,153), //purple
		sf::Color(204,255,51),	//yellow
		sf::Color(0,255,102), //green
		sf::Color(151,53,255),	//blue
		sf::Color(255,51,153)	//pink
	};
	enum ShapeType
	{
		I,
		Z,
		S,
		O,
		T,
		J,
		L
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
		void initI();
		void initZ();
		void initS();
		void initO();
		void initT();
		void initJ();
		void initL();

	protected:
		sf::Vector2f center;
		std::vector<sf::RectangleShape> m_rects;
		float elapsedTime = 0.0;
		const float fallTime = 0.5;
		bool rotated = false;
	};


	class TBackGround : public GObj
	{
	public:
		
	};