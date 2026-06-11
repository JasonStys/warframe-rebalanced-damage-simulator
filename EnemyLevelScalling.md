# Enemy Level Scaling

Grineer:
Health: 1+0.0015(health - level)^2.5
Armor: 1+0.0015(armor - level)^3
Shields: 1+0.0015(shield - level)^2
Corpus:
Health: 1+0.0015(health - level)^2.5
Armor: 1+0.0015(armor - level)^2
Shields: 1+0.0015(shield - level)^3
Infested:
Health: 1+0.0015(health - level)^3
Armor: 1+0.0015(armor - level)^2.25
Shields: 1+0.0015(shield - level)^1.5
Corrupted:
Health: 1+0.0015(health - level)^2.5
Armor: 1+0.0015(armor - level)^2.5
Shields: 1+0.0015(shield - level)^2.25
Sentient:
Health: 1+0.0015(health - level)^2
Armor: 1+0.0015(armor - level)^2.5
Shields: 1+0.0015(shield - level)^2.5
Murmur
Health: 1+0.0015(health - level)^2.75
Armor: 1+0.0015(armor - level)^2.5
Shields: 1+0.0015(shield - level)^2
Narmer:
Health: 1+0.0015(health - level)^2
Armor: 1+0.0015(armor - level)^2
Shields: 1+0.0015(shield - level)^2
Shadow:
Health: 1+0.0015(health - level)^2.5
Armor: 1+0.0015(armor - level)^3
Shields: 1+0.0015(shield - level)^2
All information in the Enemy List is the Enemies at level 1. The amount of armor an enemy has increases the damage resistance to damage on the enemy’s health, the damage reduction from this damage resistance is represented by the equation, damage resistance = armor/(armor+300), depending on the unit type of the enemy the damage resistance reaches a fixed, capped value. For light units the cap is 90% damage resistances, for basic units the cap is 92% damage resistances, for medium units the cap is 94% damage resistance, for heavy units the cap is 96% resistances, and for boss units the cap is 98% damage resistances. Side not Sentient adaptation seen in enemy list is special damage resistance wear after taking a certain type of damage the enemy becomes 10% more resistant to that damage up to 90%, any weaker version of this special resistances reduces that cap. These features would have been implemented into the code if not for complexity, time, and replit's small CPU and ram limits. These are here for reference and for the user to see and use when inputting enemy values for health.
