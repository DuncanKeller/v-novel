#include "Scene.h"

Scene::Scene(void) {
	backdrop = NULL;
	text = "";
	SDL_WM_SetCaption( "TTF Test", NULL );
	font = TTF_OpenFont( "fonts\\georgia.ttf", 28 );
	Load();
	ptr = commands.begin();
}

Scene::~Scene(void) {
	TTF_CloseFont( font );
}

void Scene::Run() {
	string debugStr(*ptr);
		std::wstring stemp = std::wstring(debugStr.begin(), debugStr.end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);
		OutputDebugString(L"\n");
	Command(*ptr);
	ptr++;
}

void Scene::Update() {
	std::map<std::string, Actor*>::iterator iter;
	for (iter = actors.begin(); iter != actors.end(); ++iter) {
		iter->second->Update();
    }
}

void Scene::Load() {
	ifstream input;
	input.open("script.txt");

	if(input.fail()) {
		OutputDebugString(L"failure");
		return;
	}

	char line[255];

	while(true)  {
		input.getline(line, 255);

		// test for end of file
		if(input.eof() == true) {
			break;
		}

		string debugStr(line);

		if(!debugStr.empty()) {
			commands.push_back(line);
		}
	}

	input.close();
}

void Scene::Command(string cmd) {
	int pos = 0;
	bool first = true;
	string name = "";
	for(int i = 0; i < cmd.length(); i++)
	{
		if(first)
		{
			if(cmd[i] == '[' || cmd[i] == '\"'  ||
				cmd[i] == '<' || cmd[i] == '\'' || 
				cmd[i] == '(' || cmd[i] == '{')
			{
				pos = i + 1;
				first = false;
			}
		} else if(!first) {
 			if(cmd[i] == ']') {
 				string n = cmd.substr(pos, i - pos);
				name = n;
				if(actors[name] == NULL) {
					actors[name] = new Actor(name);
				}
				first = true;
			} else if(cmd[i] == '\"') {
				string s = name + ": \"" + cmd.substr(pos, i - pos) + "\"";
				text = s;
				first = true;
			} else if(cmd[i] == '\'') {
				string s = "\"" +cmd.substr(pos, i - pos);
				text = s;
				first = true;
			} else if(cmd[i] == '>') {
				string e = cmd.substr(pos, i - pos);
				actors[name]->SetExpression(e);
				first = true;
			} 
			else if(cmd[i] == '}') {
				string a = cmd.substr(pos, i - pos);
				actors[name]->SetAnimation(a);
				first = true;
			} else if(cmd[i] == ')') {
				if(cmd[pos - 4] == 'b' && cmd[pos - 3] == 'k' && cmd[pos - 2] == 'g') {
					string b = "backdrops\\" + cmd.substr(pos, i - pos) + ".jpg";
					backdrop = IMG_Load(  b.c_str() );
				}
				first = true;
			}			
		}
	}
}

void Scene::Draw(SDL_Surface* surface) {
	char* str =  new char[text.length()+1];
	strcpy(str, text.c_str());
	SDL_Rect backdropRect;
		backdropRect.x = 0;
		backdropRect.y = 0;
		backdropRect.w = 800;
		backdropRect.h = 600;


	if(backdrop == NULL) {
		SDL_FillRect(surface, &backdropRect, SDL_MapRGB(surface->format, 
			0, 0, 0));
	} else {
		SDL_BlitSurface( backdrop, NULL, surface, &backdropRect );
	}

	std::map<std::string, Actor*>::iterator iter;
	for (iter = actors.begin(); iter != actors.end(); ++iter) {
		iter->second->Draw(surface);
    }

	WrapText(str, 20, 460, 750, surface);
}

void Scene::WrapText( const char *text, Uint16 x, Uint16 y, Uint16 Width, SDL_Surface* surface ) {
	Uint16 text_Width = Width - 40;		// -- holds the maximum width a line can be (in pixels)
	std::vector < std::string > lines;	// -- these are the individual lines of text
	std::string temp( text );		// -- holds the current line of text
	temp += " ";  // -- Adds a space to the end of the string so that all of the text will always be displayed.
	Uint32 n = 0;	// -- Holds the index of the current index to find out if it is past the box
	Uint32 p = 0;	// -- Holds the index of the previous space so that the wrod that goes past the end gets wrapped to the next line
	// -- Get until either ' ' or '\0'
	while( n != -1 ) {
		std::string strSub;
		n = temp.find( " ", p + 1 );		// -- Find the next " "
		if( (n * 16) >= text_Width ) {
			strSub = temp.substr( 0, p );	// -- sets strSub to the of the current line
			lines.push_back( strSub );	// -- Puts strSub into the lines vector
			if( n != -1 ){
				temp = temp.substr( p+1, std::string::npos );
			}
			p = 0;
		}
		else{
			p = n;
		}
	}
	//backdrop
	if(!Scene::text.empty()) {

		SDL_Rect textBackdrop;
		textBackdrop.x = x;
		textBackdrop.y = y;
		textBackdrop.w = Width;
		textBackdrop.h = y + lines.size() * 25;
		SDL_Color backColor = { 0, 0, 0 };

		SDL_Surface *sfc = SDL_CreateRGBSurface(
			SDL_SWSURFACE | SDL_ANYFORMAT, textBackdrop.w, textBackdrop.h, 
			surface->format->BitsPerPixel, 0, 0, 0, 0);
		SDL_FillRect(sfc, NULL, SDL_MapRGBA(sfc->format, 
			backColor.r, backColor.g, backColor.b, 100));
		SDL_SetAlpha(sfc, SDL_SRCALPHA, 100);

		SDL_BlitSurface( sfc, NULL, surface, &textBackdrop );

		SDL_FreeSurface(sfc);

		// -- Draws the text for each line of text onto the box
		for( Uint8 i = 0; i < lines.size(); i++ ) {
			const char *txtPtr = lines[i].c_str();

			SDL_Rect offset;
			offset.x = x + 10;
			offset.y = y + i * 25 + 10;
			SDL_Color textColor = { 255, 255, 255 };
			SDL_Surface* dialogSurface = 
				TTF_RenderText_Solid( font, 
				txtPtr, 
				textColor );

			SDL_BlitSurface( dialogSurface, NULL, surface, &offset );

			//m_Graphics->drawText( txtPtr, x + 41, y + line_Skip + ( line_Skip * i ), 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF );
		}
	}
}