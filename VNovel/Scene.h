#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Actor.h"
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;
class Scene
{
public:
	Scene(void);
	~Scene(void);
	void Update(void);
	void Draw(SDL_Surface*);
	void Command(string);
	void Run();
	void Load();
	void WrapText( const char*, Uint16, Uint16, Uint16, SDL_Surface* );
private:
	map<string, Actor*> actors;
	string text;
	vector<string> commands;
	vector<string>::iterator ptr;
	TTF_Font *font;
	SDL_Surface* backdrop;
};

