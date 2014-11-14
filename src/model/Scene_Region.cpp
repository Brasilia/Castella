#include <Scene_Region.hpp>

Scene_Region::Scene_Region () {
	SceneControl::set_cur (Scenes::SCENE_REGION);
	current = (Region*) Scene::ptr;
	// window
	Window *win = new Window ("region.lua");
	windows.push_back (win);
	
	static string a = "oi";
	static string b = "doido";

	Cont = new ContentTable<string> (&win->get_position (), 120, 120, 
			80, 80, {&a, &b});

	win->addWidget (Cont);
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
				Structure::Structure_TypeName (S->getType ()), 0, 255, 0);
		i++;
	}

	Scene::draw (screen);
}


void Scene_Region::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);

	string *oi = Cont->getContent ();

	if (oi) {
		cout << *oi << '\n';
	}
}


void Scene_Region::escape () {
	SceneControl::exitScene ();
}


void Scene_Region::handle_scene_input (int input) {

}
