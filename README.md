# GEC-Semester-2

A relatively accurate depiction of the original Mario Bros Arcade game using SDL2, submitted as part of Game Engine Creation's Semester 2 Assessment. 

## The Premise

The aim of the game is to defeat all the enemies in each stage. Each stage begins with just Mario and Luigi, enemies will spawn periodically, the type of enemy spawning is predetermined in an array that is individual for each level. Each enemy will kill the players on contact, unless they have been flipped over beforehand, this can be done in two ways, jumping into the platform below them to bump them over, or hitting the POW block at the bottom of the stage. If flipped, the enemy will die on contact instead, and award the player points, as well as spawning a coin in the pipe above them. The POW block has three uses that replenish at the beginning of each stage and is used by jumping into the bottom of it. When all the enemies in a stage have been defeated, the game will swap to the next level. When Mario and Luigi have both been killed, the game will switch scene to a scoreboard where the players can enter a name and add their combined score. Once entered, the game will return to the main menu after a brief pause, allowing players to see their score on the board if it was high enough. Players may then play again if they decide to. Scores are stored in an external leader board, and the highest is displayed at the top of the screen while playing, alongside Mario and Luigi’s scores.

### Enemies:

* ShellCreeper (Koopa): Moves left and right, progression down the screen, will wrap around screen edge and if hit, will flip over, now being able to be kicked off the stage. If it flips back up however, it will become angry, speeding up dramatically. Awards *800* points on death. 
* SideStepper (Crab): Moves similarly to Koopa, also wrapping around screen edges, when hit once it will become angry, speeding up dramatically. On second hit, will flip like normal and can then be killed. Awards *1000* points.
* FighterFly: Jumps left and right as it moves, moves comparably slowly but can only be hit when on the ground, awards *1200* points on kill. 

## Controls

#### Mario

- W – Jump
- A – Move Left
- D – Move Right

#### Luigi

- Up arrow – Jump
- Left arrow – Move Left
- Right Arrow – Move Right

#### Menu Controls

- W/Up – Move cursor up
- S/Down – Move cursor down
- A/Left – Move cursor left
- D/Right – Move cursor right
- Enter - Enter name + score
- Space - Start game

## Files

### Classes
(Any in a list below a class are child classes)

* Character: Handles all entity behaviours
  * Player: Handles movement and behaviours unique to player characters
    * Mario
    * Luigi
  * Enemy: Handles enemy specific behaviours such as unique movement. taking damage, awarding points etc. 
    * Koopa
    * SideStepper
    * FighterFly
  * Coin

* ScreenManager: Handles loading and deleting scenes at appropriate times

* Screen: The foundation for levels to be created, stored information needed for each level such as background music
  * MainLevel: the basis for creating a basic level in Mario Bros, stores gameplay elements and methods for running the game
  * MainMenuScreen: Smaller screen class for displaying the main menu and allowing input to progress
  * ScoreScreen: Screen allowing player to enter name and add score to scoreboard

#### Game Elements

* Collisions: Singleton for dealing with collision
* LevelMap: Handles collisions with level platforms and POW block
* ScoreSystem: Singleton for handling the external scoreboard, and keeping track of player scores
* SoundEffect
* TextRenderer
* Texture2D: Seperate class for textures that handles rendering using various overloads
* Game: Overarching class that manages all others and their interactions 

#### Constants

* Commons.h: Contains common data types and structures created that will need accessing by several classes
* Constants.h: Contains all constant values such as speeds, sizes, screen width etc. 