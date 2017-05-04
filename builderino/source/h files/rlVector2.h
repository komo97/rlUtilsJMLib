#pragma once
class rlVector2
{
public:
	rlVector2();
	rlVector2(const float& _x, const float& _y);

	//Getters
	int getX();
	int getY();
	float getXf();
	float getYf();
	
	//Setters
	void setX(const float& _x);
	void setY(const float& _y);
	void moveX(const float& _x);
	void moveY(const float& _y);
	void Translate(rlVector2& vec);
	


	~rlVector2();

	rlVector2& operator+= (rlVector2 rhs);
	rlVector2& operator-= (rlVector2 rhs);
	float operator*= (rlVector2 rhs);
	rlVector2& operator*= (const float& rhs);

	static float Distance(rlVector2& vec1, rlVector2& vec2);
private:
	float x, y;
};

rlVector2& operator+(rlVector2 lhs, rlVector2 rhs);
rlVector2& operator-(rlVector2 lhs, rlVector2 rhs);
float operator*(rlVector2 lhs, rlVector2 rhs);
rlVector2& operator*(rlVector2 lhs, const float& rhs);
rlVector2& operator+(rlVector2 lhs, const float& rhs);

