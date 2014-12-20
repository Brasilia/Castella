#include "Scene_Region.hpp"
#include "World.hpp"

Scene_Region::Scene_Region () {
	SceneControl::set_cur (Scenes::SCENE_REGION);
	current = (Region *) Scene::ptr;

	// window
	Window *win = new Window ("region.lua", [=] (lua_State *L) {
				World::registerOnLua (L);
				ScriptHandler::send_to_lua<Region *> (L, "reg", current);
				using namespace luabind;
				module (L) [
					def ("vaiPraEstrutura", &Scene_Region::goToStructure)
				];
			});
	windows.push_back (win);

	static string a = "oi";
	static string b = "doido";
	static string c = "mais um xD";

	Cont = new Checklist<string> (&win->get_position (), 220, 80,
			80, 80, {&a, &b, &c});

	win->addWidget (Cont);
}


void Scene_Region::goToStructure (Structure *structure) {
	Scene::ptr = structure;
	SceneControl::set_next (Scenes::SCENE_STRUCTURE);
}


Scene_Region::~Scene_Region () {}


void Scene_Region::update () {
	Scene::update ();
}


void Scene_Region::draw (SDL_Surface *screen) {	
	const int positions[][2] = {
		{0, 0},
		{Screen::WIDTH/2, 0},
		{0, Screen::HEIGHT/2},
		{Screen::WIDTH/2, Screen::HEIGHT/2}
	};

	int i = 0;
	for (Structure *S : current->getStructures ()) {
		boxRGBA (screen,
				positions[i][0], positions[i][1],
				positions[i][0] + Screen::WIDTH/2,
				positions[i][1] + Screen::HEIGHT/2,
				i * 40, i * 40, i * 40, 255);
		write_text (positions[i][0], positions[i][1], screen, 
				Structure::StructureTypeName (S->getType ()), {0, 255, 0});
		i++;
	}

	write_text (200, 400, screen,
			"Enter pra pegar os conteudos da checklist (na stdout)", PRETO);

	Scene::draw (screen);
}


void Scene_Region::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}


void Scene_Region::escape () {
	SceneControl::exitScene ();
}


void Scene_Region::handle_scene_input (int input) {
	// teste da checklist
	if (input == SDLK_RETURN) {
		cout << "marcados:\n";
		for (auto i : Cont->getChecked ()) {
			cout << *i << '\n';
		}
		cout << '\n';
	}
	Scene::handle_scene_input (input);
}
