#pragma once
#include "Structs.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

//Got this from our programing 2 framework
bool IsOverlapping(const DDWRect& collider, const DDWRect& otherCollider)
{
	if (collider.x > 0 && collider.x + collider.width < otherCollider.x)
	{
		return false;
	}
	if (collider.x > otherCollider.x + otherCollider.width)
	{
		return false;
	}
	if (collider.y > 0 && collider.y + collider.height < otherCollider.y)
	{
		return false;
	}
	if (collider.y > otherCollider.y + otherCollider.height)
	{
		return false;
	}
	else return true;
}

bool IsPointInRect(const glm::vec2& point, const DDWRect& rect) 
{
	return (point.x >= rect.x &&
			point.x <= rect.x + rect.width &&
			point.y >= rect.y && 
			point.y <= rect.y + rect.height);
}