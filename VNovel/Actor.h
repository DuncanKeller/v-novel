#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

class Actor
{
public:
	Actor(string);
	~Actor(void);
	void AddExpression(SDL_Surface*, string);
	void SetExpression(string);
	void SetAnimation(int, int, int);
	void SetAnimation(string);
	void SetPosition(int x, int y);
	void Update(void);
	void Draw(SDL_Surface*);
private:
	int width;
	int height;
	void ResetRect();
	string name;
	string currExpression;
	map< string, SDL_Surface*> expressions;
	SDL_Rect rect;
	int moveX;
	int moveY;
	int animationLength;
	int time;

};