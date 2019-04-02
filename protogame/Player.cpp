#include "Player.h"
#include <iostream>
#include <raylib.h>

// Constructor
Player::Player()
{
	health = 10;
	maxHealth = 10;
	exp = 0;
	level = 0;

	x = 0;
	y = 0;

	position = { 350.0f, 280.0f };
}

// Destructor
Player::~Player()
{
}