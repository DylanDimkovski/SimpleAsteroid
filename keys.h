#ifndef KEYS
#define KEYS

#include <bitset>
enum KeyState { KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_FIRE, KEY_CLOSE};
typedef std::bitset<4> Keys;

#endif