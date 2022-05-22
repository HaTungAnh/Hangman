#include "TexOb.h"
#include "Util.cpp"
void TexOb::setPos(float x, float y) {
	position = Vector2D(x, y);
}

void TexOb::setSize(float x, float y) {
	sizex = x; sizey = y;
}

void TexOb::setTexture(Texture* a) {
	texture = a;
}

void TexOb::setTexture(Text* a)
{
	text = a;
}

void TexOb::init(SDL_Renderer* renderer) {

}

void TexOb::render(SDL_Renderer* renderer) {
	if (visiable) {
		SDL_RenderSetScale(renderer, sizex, sizey);
		SDL_Rect pos = Util::toSDL_Rect(position, (text == NULL) ? texture->getWidth() : text->w, (text == NULL) ? texture->getHeight() : text->h);
		SDL_Texture* t = (text == NULL) ? texture->getTexture() : text->texture;
		SDL_RenderCopy(renderer, t, NULL, &pos);
		SDL_RenderSetScale(renderer, 1, 1);
	}
}

void TexOb::eventCheck(SDL_Event* Event) {

}

void TexOb::tick() {

}

void TexOb::free() {

}

TexOb::~TexOb()
{
	free();
}