# Game Design document

## Introduction
This game design document details the game *PowerKraft*, a 2D arena shoot-em-up where the player 
collects materials to craft powerups in order to survive for 10 minutes. The game employs 
sprite-based animation, tilesets, collision detection, AI, and an Entity-Component System design 
pattern.


## Technology
### Available Platforms
Windows 
### Game engine/software library
SFML with maths, Entity-Component manager, and tileset loader libraries.


## Backstory
In *PowerKraft*, you play as a man trapped in hell who has made a deal with the devil to return 
to the land of the living - if he can survive an onslaught of hellhounds for 10 minutes, he will 
be granted his life back.


## Objective
The objective of the game is to fend off the hellhounds for 10 minutes. If the player manages to 
survive, they win. However, if they die, they must try again from the start. The player will get 
damaged if a hellhound gets too close to them, and dies when their health reaches 0.


## Gameplay
*PowerKraft* is an 2D arena roguelite, with players able to move around a square arena where hellhounds 
continuously spawn every 20 seconds in slowly increasing numbers. These hellhounds do not go away until 
they are killed.

Alongside the hellhounds, two materials that can be picked up spawn in every 20 seconds. After 10 
seconds, they despawn, meaning the player needs to get to them quickly. Once picked up, the player 
can use these materials to craft powerups. These powerups utilise the Entity-Component System design 
pattern to attach components to the player for a brief period of time, giving them special 
enhancements to their attributes. The powerups have different costs associated with how beneficial 
they are to the player. The powerups are as follows:

| Powerup    | Material Cost | Description                                                                   |
|------------|:--------------|-------------------------------------------------------------------------------|
| Speed-up   | 1             | Doubles player speed for 20 seconds                                           |
| Reload     | 2             | Halves reload time, allowing the player to shoot twice as fast for 15 seconds |
| Insta-kill | 3             | Enemies die in one shot for 10 seconds                                        |
| Health     | 5             | Heals the player for 20 health                                                |


## Levels
The game takes place in a 31x16 grid level, surrounded by walls at all sides. The player is trapped in 
here with no escape - their only way out is to survive for 10 minutes. The levels themselves are not 
procedurally generated, but the enemies and pickups spawn in random locations around the player, meaning 
every wave is different, and allowing for a brand-new experience each time you play the game.


## Controls
The player uses a combination of the mouse and keyboard in order to move, shoot, and craft powerups.
* W/Up Arrow - Move up
* A/Left Arrow - Move left
* S/Down Arrow - Move down
* D/Right Arrow - Move right
* Left Click - Shoot
* Num1 - Craft powerup 1 (Speed-up)
* Num2 - Craft powerup 2 (Reload)
* Num3 - Craft powerup 3 (Insta-kill)
* Num4 - Craft powerup 4 (Health)


## GUI/In-game menu
Upon first loading the game, the player is greeted with the main menu, with options to start a new 
game, go to the options menu, or exit the game. Once in the game, the player will see a HUD, created 
from SFML components such as Text and RectangleShape. This HUD represents the players health, their
powerup meter, the game timer, their currently owned materials, and the list of powerups to craft.


## Artwork
Most of the artwork used in the game, such as the player, the enemies, and the level's tileset, was 
originally included in the DropPod repository. However, the artwork for the materials that the player 
picks up was create specifically for *PowerKraft*.

Textures are managed by using a mix of std::shared_ptr and std::make_shared keywords. The use of 
shared_ptr means that the texture will be destroyed once all shared_ptr references go out of scope, 
freeing up memory for new objects. The use of make_shared means only one heap allocation is made as 
opposed to two when shared_ptr is used. This means that if an error occurs during loading the texture, 
no memory will be leaked.


## Sound (sound effects)
Sound is implemented in a very similar manner to how textures are loaded into the game with SFML. It 
again makes use of shared_ptr and make_shared keywords to ensure good memory management for the same 
reasons as above.

*PowerKraft* uses sound effects in different parts of the game. Clicking sound effects will play for 
the buttons in the main menu. While in-game, the player will hear shooting sound effects every time 
they shoot their gun, and the enemies will make a sound when they get hit by one of the player's 
bullets.


## Music
The background music used in the main menu is Claude Debussy's "*Clair de Lune*". This was chosen to 
evoke a calm sensation in the player in contrast to the stress that the gameplay evokes.

The background music used in-game was retrieved from [Ovani Sound's Metal Music Pack Vol. 2](https://ovanisound.com/products/metal-music-pack-vol-2?variant=46714983285051), 
a music pack that I got through the Humble Bundle in October 2023. This music pack was chosen to evoke 
a sense of urgency and stress in the player to keep them on-edge and glued to the game.