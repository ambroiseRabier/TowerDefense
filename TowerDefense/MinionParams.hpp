#pragma once
struct MinionParams
{
	MinionParams(const float speed = 1.f, const float health = 1.f, const float damage = 1.f, const float money = 10.f)
		: speed(speed),
		  health(health),
		  damage(damage),
		  money(money)
	{
	}

	const float speed;
	const float health;
	const float damage;
	const float money;
};