/** @file Widget.hpp
 * header do view/Widget.cpp
 */

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "simpleSDLfunctions.h"

using namespace std;

/** @brief Widgets são os elementos básicos da GUI, montados usando SDL.
 *
 * Note que Widget é uma classe abstrata, já que não faz sentido um widget
 * não ser específico.
 */
class Widget {
protected:
	/// Caixa que contém o widget. Guarda sua posição e tamanho
	SDL_Rect box;
	/// Distância em relação à janela pai
	SDL_Rect windowRelativeOffset;
	/// Referência da janela pai, caso ela se desloque, widget desloca junto
	SDL_Rect *window {NULL};
	/// Imagem, o que será efetivamente mostrado
	SDL_Surface *image {NULL};

public:
	Widget ();
	/// Ctor com parâmetros: já define window pai, tamanho e posição relativa
	Widget (SDL_Rect *window, int width, int height, int x, int y);
	/// dtor
	virtual ~Widget () = 0;
	/// Verifica se clicou
	virtual bool mouse_try_click (int x, int y);
	/// Lógica a ser atualizada a cada frame
	/// por padrão, atualiza a posição global através da posição da window
	virtual void update ();
	/** @brief Desenha!
	 *
	 * Essa versão simplesmente aplica 'image' a 'target',
	 * em sua posição correta.
	 *
	 * @note As classes filhas, aplicam o que quiserem à
	 * image, que daí aqui a desenhamos na target.
	 */ 
	void draw (SDL_Surface *target);
};

#endif
