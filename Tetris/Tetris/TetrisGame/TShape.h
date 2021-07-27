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
	struct RectInterInfo
	{
		bool intersection = false;
		sf::Vector2f myRectPos;
		sf::Vector2f otherRectPos;
		RectInterInfo() = default;
		RectInterInfo(const sf::Vector2f& iMyRectPos, const sf::Vector2f& iOtherPos) 
			: myRectPos(iMyRectPos), otherRectPos(iOtherPos) { intersection = true; }
	};
	class TShape : public GObj
	{
	public:
		TShape(int iType, const sf::Vector2f& iCenter = TetrisShapes::center);
		sf::FloatRect getExtents() const override;
		//shape moves to input motion and freezes
		RectInterInfo intersectShape(const TShape* ipOtherShape, sf::FloatRect& oIntersection) const;
		void moveShape(const sf::Vector2f& iMotion);
		const sf::Color& getRandColor();
		void processEvent(float iTime, int iEventIdx) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void revertLastEvent() override;
		void rotate(bool clockWise = true);
		void init();
		void initI();
		void initZ();
		void initS();
		void initO();
		void initT();
		void initJ();
		void initL();
		int type;
	protected:
		sf::Vector2f center;
		std::vector<sf::RectangleShape> m_rects;
		std::vector<sf::Vector2f> m_cachePos;
		bool rotated = false;
	};

