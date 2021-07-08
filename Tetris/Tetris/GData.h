#pragma once
#include <vector>
#include <memory>
#include "GObj.h"
class GData final
{
	enum GDataObj
	{
		defaultObj
	};
public:
	void addObj(int iObj);
private:
	std::vector<std::shared_ptr<GObj>> m_obj;
};