/** @file Widget.hpp
 * Widgets a serem usados nos scripts lua, montados usando o SDL.
 */

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SDL/SDL.h>

class Widget {
protected:
	/// Caixa que contém o widget. Guarda sua posição e tamanho
	SDL_Rect box;
	/// Distância em relação à janela pai
	SDL_Rect windowRelativeOffset;
	/// Referência da janela pai, caso ela se desloque, widget desloca junto
	SDL_Rect *window;
	/// Imagem, o que será efetivamente mostrado
	SDL_Surface *image;

public:
	Widget ();
	/// Ctor com parâmetros: já define window pai, tamanho e posição relativa
	Widget (SDL_Rect *window, int width, int height, int x, int y);
	/// dtor
	virtual ~Widget () = 0;
	/// Verifica se clicou
	virtual bool mouse_try_click (int x, int y);
	/// Lógica a ser atualizada a cada frame
	virtual void update () = 0;
	/// Desenha!
	virtual void draw (SDL_Surface *target) = 0;
};

#endif
