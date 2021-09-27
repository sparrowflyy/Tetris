#pragma once
#include "../GObj.h"
#include "TField.h"

static bool debug = true;

namespace TetrisShapes {
	static const int shapeParts = 4;
	static const int rectSize = 30;
	static const float outlineThick = 2;
	static const int numTypes = 7;
	static const float shapeSpeed = 100;
	static sf::Vector2i center{ 10,2 };
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
		TShape(TField* field , int iType, const sf::Vector2i& iMaxPoint = TetrisShapes::center);
		sf::FloatRect getExtents() const override;
		void moveShape(const sf::Vector2i& iMotion);
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
	private:
        std::unique_ptr<TField> field;
		sf::Vector2i maxPoint;
		std::vector<std::pair<short,short>> indices;
		bool rotated = false;
		int parts;
	};

