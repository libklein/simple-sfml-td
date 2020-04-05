# Architecture

## Sprites

* Sprite Atlas
  * Keep track of mapping 
* Texture Atlas
  * Representation of sprite sheet, gets proper texture coordinates for sprite ids

* Animation member / Subclass Animation
  * List of:
    * Duration
    * Frames (Sprite ids)

## Entities

* Entity (Animation)
* Actor interface (Controllable?)
* Movable interface



**What will definietly be in the game:**

* Towers
  * Static, but can rotate
* Enemies
  * Spawn in waves
  * Run to target
* Statics
  * Bushes, etc., belongs to map
  * May be destructable
* All need to be aware of the world

## World

### Map

* Grid of tiles
* Manages connecting neighboring tiles etc.

---

* Keeps track of entities in the world