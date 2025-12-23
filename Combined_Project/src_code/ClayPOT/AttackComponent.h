#pragma once


class AttackComponent {
public:
	AttackComponent(float cooldown = 1.0f)
		: cooldown(cooldown), timer(0.0f), attacking(false) {
	}

	void update(float dt) {
		if (attacking) {
			timer += dt;
			if (timer >= cooldown) {
				attacking = false;
				timer = 0.0f;
			}
		}
	}

	bool canAttack() const {
		return !attacking;
	}

	void attack() {
		if (!attacking) {
			attacking = true;
			timer = 0.0f;
			playAnimation("attack");
		}
	}

private:
	float cooldown;   // seconds between attacks
	float timer;
	bool attacking;

	void playAnimation(const std::string& name) {
		// Replace this with your engine's animation call
		std::cout << "[Animation] Playing: " << name << "\n";
	}
};
