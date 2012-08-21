#include "Actor.h"

Actor::Actor(string name) {
	Actor::name = name;
	width = 400;
	height = 700;
	rect.w = width;
	rect.h = height;
	rect.y = 600 - rect.h;
	rect.x = (800 / 2) - (rect.w / 2);
}

Actor::~Actor(void) {
}

void Actor::ResetRect() {
	rect.w = width;
	rect.h = height;
}

void Actor::AddExpression(SDL_Surface* s, string name)  {
	expressions[name] = s;
}

void Actor::SetExpression(string exp) {
	if(expressions[name] == NULL) {
		string n = "actors\\" + name + "-" + exp + ".png";
		SDL_Surface* s = IMG_Load(  n.c_str() );
		AddExpression(s, exp);
	}
	currExpression = exp;
}

void Actor::SetPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void Actor::SetAnimation(string s) {
	if(s == "move-down") {
		SetAnimation(rect.x, 550, 200);
	} else if(s == "move-up") {
		SetAnimation(rect.x, 0, 60);
	} else if(s == "move-left") {
		SetAnimation(-100, rect.y, 150);
	} else if(s == "move-right") {
		SetAnimation(800, rect.y, 150);
	}
}

void Actor::SetAnimation(int x, int y, int t) {
	animationLength = t;
	time = t;
	moveX = (x - rect.x) / animationLength;
	moveY = (y - rect.y) / animationLength;
}

void Actor::Update() {
	if(time > 0) {
		rect.x += moveX;
		rect.y += moveY;
		time--;
	}
}

void Actor::Draw(SDL_Surface* s) {
	ResetRect();
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = rect.w;
	source.h = rect.h;
	SDL_BlitSurface(expressions[currExpression], &source, s, &rect);
}