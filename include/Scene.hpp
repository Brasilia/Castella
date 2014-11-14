#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <stack>
#include <iostream>

#include "Window.hpp"
#include "Input.hpp"
#include "ScriptHandler.hpp"
#include <Player.hpp>

//Virtual class parent to every game scene
class Scene
{
    public:
        Scene();
        Scene(Player* player1, Player* player2);
        virtual ~Scene();
        //Runs the scene logic
        virtual void update();
        //Draws the scene items
        virtual void draw(SDL_Surface *screen);
        //Handles the scene input - handles generic context inputs and calls specific context handler
        void handle_input();

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
        std::vector<Window*> windows;
        //Handles scene-specific input - called from handle_input()
        virtual void handle_scene_input(int input) {cout << "to na scene normal";};
        //Handles a mouse click input on the scene
        virtual void mouseclick(int x, int y);
        //Defines a method for the ESC key
        virtual void escape();

		/// Ponteiro de qualquer tipo, para guardar algo que precisar (estou olhando pra Região e Estrutura)
		static void *ptr;

    private:

};

// - TODO: base Scene must control mouse position aquisition and standard inputs like asking to quit on the X(close) button

#endif // SCENE_H
