#ifndef ___PROTOCOLO___
#define ___PROTOCOLO___

#define CREATE_LOBBY 11
#define JOIN_LOBBY 13
#define LEAVE_LOBBY 16
#define PLAYER_LEFT_LOBBY 14
#define PLAYER_JOINED_LOBBY 15
#define PLAYER_JOIN 17
#define PLAYER_LEAVE 18
#define PLAYER_IS_READY 19

#define LOG_IN	20
#define LOG_IN_FAILED 21
#define LOG_IN_SUCCESS 22

#define CLIENT_LOADED_GAME 23
#define GAME_MODEL_STARTED_RUNNING 24
#define LOAD_MAP 25
#define PATH_TILE 26
#define STRUCTURE_TILE 27
#define SPAWN_TILE 28
#define FINISH_TILE 29
#define MAP_HEIGHT 30
#define MAP_WIDTH 31
#define MAP_SURFACE 32
#define MAP_FINISHED_LOADING 33

#define NEW_TOWER 34
#define WATER_TOWER 35
#define FIRE_TOWER 36
#define EARTH_TOWER 37
#define AIR_TOWER 38

#define PLAYER_PICKED_SPELL 40
#define PICK_SPELL 42

#ifndef __SPELLS_ENUM__
#define __SPELLS_ENUM__
enum SPELL_TYPE {
    SPELL_TYPE_FIRE = 50,
    SPELL_TYPE_AIR = 51,
    SPELL_TYPE_GROUND = 52,
    SPELL_TYPE_WATER = 53
} ;
#endif


#ifndef __UNITS_ENUM__
#define __UNITS_ENUM__
enum UNIT_TYPE {
    UNIT_TYPE_Abmonible = 54,
    UNIT_TYPE_DemonioVerde = 55,
    UNIT_TYPE_Espectro = 56,
    UNIT_TYPE_HalconSangriento = 57,
    UNIT_TYPE_HombreCabra = 58,
    UNIT_TYPE_NoMuerto = 59
} ;
#endif

#define GAME_STARTED 100
#define GAME_OPCODE 101
#define TOWER_PLACED 102
#define UNIT_POSITION_UPDATE 103
#define UNIT_CREATED 104
#define GAME_OVER 105
#define PROJECTILE_FIRED 106
#define UNIT_DIED 107


#define CLIENT_CREATE_TOWER 108
#define CLIENT_CAST_SPELL 109


#ifndef __CAST_SPELL_ENUM__
#define __CAST_SPELL_ENUM__
enum CAST_SPELL_TYPE {
    SPELL_TERRAFORMING = 200,
    SPELL_GRIETA = 201,
    SPELL_FIREWALL = 203,
    SPELL_METEORITO = 204,
    SPELL_CONGELACION = 205,
    SPELL_VENTISCA = 206,
    SPELL_TORNADO = 207,
    SPELL_RAYO = 208,
    SPELL_PING = 209
} ;
#endif


#define IN_GAME_CHAT_MESSAGE 210
#define HORDE_STARTED 211
#define HORDE_ENDED 212
#define GAME_WON 213
#define TOWER_GAINED_EXP 214

enum UpgradeType {
    Range = 215,
    Damage = 216,
    CollateralRange = 217,
    Slow = 218 };

#define TOWER_UPGRADE 219
#define PICK_MAP 220
#define UNIT_SPEED_UPDATE 221
#define UNIT_FROZEN 222
#define SPELL_IS_FREE 223
#define LOBBY_GONE 224


#endif