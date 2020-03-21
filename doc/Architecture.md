# Architecture

## Sprites

* Sprite Atlas
  * Keep track of mapping 
* Texture Atlas
  * Representation of sprite sheet, gets proper texture coordinates for sprite ids

* Animation member / Subclass Animation
  * List of:
    * Target transform
    * Duration
    * Frames (Sprite ids)

## World

### Map

* Grid of tiles
* Manages connecting neighboring tiles etc.

---

* Keeps track of entities in the world