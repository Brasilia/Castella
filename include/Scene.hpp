#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <stack>
#include <iostream>

#include "Drawable.hpp"
#include "Window.hpp"
#include "Input.hpp"

//Virtual class parent to every game scene
class Scene : public Drawable
{
    public:
        Scene();
        virtual ~Scene();
        //Runs the scene logic
        virtual void update();
        //Handles the scene input - handles generic context inputs and calls specific context handler
        virtual void handle_input();

		virtual void draw (SDL_Surface *screen);
		virtual void set_need_redraw ();

        static Scene *scene; //the logic game scene
        /** Pilha de Cenas
		 *
		 * É usada uma pilha pra, na hora de sair da cena,
		 * voltar pra que tava antes.
		 * @sa exitScene
		 */
		static std::stack<Scene*> scenes;

    protected:
        int input; //stores the last input value returned
        std::vector<Window *> windows;
        //Handles scene-specific input - called from handle_input()
        virtual void handle_scene_input(int input);
        //Handles a mouse click input on the scene
        virtual void mouseclick(int x, int y);
        //Defines a method for the ESC key
        virtual void escape();
        //Checks rather a key is pressed or not
        virtual bool is_key_pressed(SDLKey key);

		/// Redesenha cena
		virtual void redraw ();

		/// Ponteiro de qualquer tipo, para guardar algo que precisar (estou olhando pra Região e Estrutura)
		static void *ptr;

    private:

};

#endif // SCENE_H
