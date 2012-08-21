#include "Actor.h"

Actor::Actor(string name)
{
	Actor::name = name;
	rect.w = 400;
	rect.h = 700;
	rect.y = 600 - rect.h;
	rect.x = (800 / 2) - (rect.w / 2);
}

Actor::~Actor(void)
{
}

void Actor::AddExpression(SDL_Surface* s, string name) 
{
	expressions[name] = s;
}

void Actor::SetExpression(string exp)
{
	if(expressions[name] == NULL)
	{
		string n = "actors\\" + name + "-" + exp + ".png";
		SDL_Surface* s = IMG_Load(  n.c_str() );
		AddExpression(s, exp);
	}
	currExpression = exp;
}

void Actor::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Actor::Update()
{

}

void Actor::Draw(SDL_Surface* s)
{
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = rect.w;
	source.h = rect.h;
	SDL_BlitSurface(expressions[currExpression], &source, s, &rect);
}