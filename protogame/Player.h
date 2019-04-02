#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

class Player
{
	public:
		float health;
		float maxHealth;
		float exp;
		int level;

		float x;
		float y;

		Texture2D texture;
		Vector2 position;

		Player();
		~Player();

	protected:

	private:
};

#endif