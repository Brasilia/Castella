#include <Actor_Battler.hpp>

class Scene_Battle{
    public:
        static int frame;
};

class Skill{
    public:
        static std::vector<Skill*> skills;
        int get_cost(Actor_Battler *battler);
        int get_damage(Actor_Battler *battler);
};

Actor_Battler::Actor_Battler(Actor* actor){
    Actor_Battler *battler = this;
    *battler = *( (Actor_Battler*)actor );
    this->hp = get_max_hp();
    this->stamina = 0;
    //this->spritesheet = FileHandler::load_img("actors/actor1.png");
    this->direction = Direction::DOWN;
    //setar IA, de acordo com atributo do actor
    walking = 0;
}

Actor_Battler::~Actor_Battler()
{
    //dtor
}

SDL_Rect Actor_Battler::clip(int index){
    SDL_Rect clip;
    clip.w = spritesheet->w/3;
    clip.h = spritesheet->h/4;
    clip.x = index%3 * clip.w;
    clip.y = index/3 * clip.h;
    return clip;
}

void Actor_Battler::draw(int x, int y, int index, SDL_Surface *screen){
    index = (int)direction*3 + 1;
    apply_surface(x-clip(index).w/2, y, spritesheet, screen, &clip(index+(bool)walking*Scene_Battle::frame%18/6-1));
    //Código provisório para simular uma HUD em texto:
    write_text(x, y+clip(index).h, screen, to_string( (int)get_stamina_percent() ) +"%", {0,0,0}, 0.5);
    write_text(x, y+clip(index).h+24, screen, to_string(hp), {200,0,0}, 0.5);
}

void Actor_Battler::set_allegiance(int allegiance){
    this->allegiance = allegiance;
}

int Actor_Battler::get_allegiance(){
    return allegiance;
}

void Actor_Battler::set_map_pos(int x, int y){
    map_pos.x = x;
    map_pos.y = y;
}

SDL_Rect Actor_Battler::get_map_pos(){
    return map_pos;
}

void Actor_Battler::look(Direction direction){
    this->direction = direction;
}

void Actor_Battler::walk(Direction direction){
    look(direction);
    // Adicionar verificação de passabilidade do tile...
    //Caso seja passável, verificar custo e tentar executar a movimentação
    int cost = (30)/3; // estabelecer custo em função do peso e da força
    if (use_stamina(cost)){ //se tiver estamina suficiente, gasta e executa
        walking = 9;
        int x = map_pos.x;
        int y = map_pos.y;
        switch (direction){
            case Direction::DOWN:
                y++;
                break;
            case Direction::UP:
                y--;
                break;
            case Direction::LEFT:
                x--;
                break;
            case Direction::RIGHT:
                x++;
                break;
            default:
                break;
        }
        set_map_pos(x, y);
    }
}

bool Actor_Battler::use_skill(int skill_id){
    Skill *sk = Skill::skills.at(skill_id);
    int cost = sk->get_cost(this);
    std::cout << "Use Skill, cost:" << cost << std::endl;
    if ( enough_stamina(cost) ){
        SDL_Rect target;
        target.x = map_pos.x;
        target.y = map_pos.y;
        switch (direction){
            case Direction::DOWN:
                target.y++;
                break;
            case Direction::UP:
                target.y--;
                break;
            case Direction::LEFT:
                target.x--;
                break;
            case Direction::RIGHT:
                target.x++;
                break;
        }
        use_stamina(cost);
        skillDamageBuffer = sk->get_damage(this);
        skillTargetBuffer = target;
        return true;
    }
    return false;
}

void Actor_Battler::set_ai(int ai){
    this->AI = ai;
}

bool Actor_Battler::is_player_controlled(){
    return !AI;
}

bool Actor_Battler::is_passable(){
    return passable;
}

void Actor_Battler::update(){
	using namespace luabind;

    stamina += call_function<float> (*Lua_get_stamina_recovery, this);
    if (stamina >= call_function<float> (*Lua_get_max_stamina, this)){
        stamina = call_function<float> (*Lua_get_max_stamina, this);
    }
}

float Actor_Battler::get_stamina_percent(){
    return (stamina/get_max_stamina())*100;
}

bool Actor_Battler::use_stamina(int cost){
    if (enough_stamina(cost)){
        stamina -= cost;
        return true;
    }
    else return false;
}

bool Actor_Battler::enough_stamina(int cost){
    if (stamina >= cost){
        return true;
    }
    else return false;
}

void Actor_Battler::take_damage(int damage){
    hp -= damage;
    //Antes devem seguir possíveis redutores de dano, como:
    // atenuação de dano físico;
    // redução pela armadura;
    // etc
    //Depois, devem ser feitos outros testes, como de morte
}

int Actor_Battler::get_skill_damage_buffer(){
    return skillDamageBuffer;
}

SDL_Rect Actor_Battler::get_skill_target_buffer(){
    return skillTargetBuffer;
}

/// GET pega uma função do lua, a partir do seu nome
#define GET(func) (*Actor::Lua_get_##func = _G[#func])
void Actor_Battler::getFunctionsFromLua (const string script_name) {
	sH.load (script_name);
	sH.run_lua ();

	registerOnLua (sH.state ());

	LuaTable _G = sH.global ();
	GET (max_hp);
	GET (max_stamina);
	GET (precision);
	GET (evasion);
	GET (stamina_recovery);
	GET (phys_dmg_amplifier);
	GET (magic_dmg_amplifier);
	GET (phys_dmg_attenuation);
	GET (magic_dmg_attenuation);
}
#undef GET
ScriptHandler Actor_Battler::sH;

void Actor_Battler::registerOnLua (lua_State *L) {
	using namespace luabind;

	Actor::registerOnLua (L);

	module (L) [
		class_<Actor_Battler, Actor> ("Actor_Battler")
	];
}
