# Bottery
This is a game about dodging and catching balls, made in Unreal Engine. It features components that manage the parent actor's flags, stats and resources like speed and health(aka battery). The balls(aka orbs) carry effect components that affects these values on collision.

## Purpose
With this project, I hope to show that I can implement gameplay mechanics using a component-based architecture.

## How to use
1. Clone the repository
2. Open in Unreal Engine version 5.5.4 or newer (this project is using version 5.5.4, opening in newer versions might require regenerating project files and rebuild to work correctly)

## Structure
- **Content/Bottery:** assets
  - **Animations:** contains a single animation montage for dashing
  - **Audio:** contains sound cue and attenuation assets (related to footsteps)
  - **DataAssets:** contains spawn table and tutorial [data assets](https://dev.epicgames.com/documentation/en-us/unreal-engine/data-assets-in-unreal-engine)
  - **Framework:** contains blueprint subclasses related to [UE's gameplay framework](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-framework-in-unreal-engine) like game mode and character controller
  - **Input:** assets related to [UE's enhanced input](https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine)
  - **Maps:** maps/levels (main menu and gameplay(TopDownMap))
  - **Obstacles:** contains blueprints of environment objects (cubes and pillars)
  - **Orbs:** orb assets
    - **Audio**
    - **Blueprints**
    - **Materials**
    - **VFX:** particle system when colliding with character, fade in and fade out curves
  - **UI:** UI widget blueprints
- **Source(C++ Classes in UE Content Drawer)/Bottery:** C++ source codes (Private: .cpp ;Public: .h)
  - **ActorData:** classes that define actor flags, stats, resources and corresponding component classes that store them
    - **Flag:** boolean true or false values eg. polarity
    - **Resource:** consumable/replenishable number like health(aka battery)
    - **Stat:** number that represents attributes like speed
  - **Character**
    - **BotCharacterMovementComponent:** character's movement component class, move speed based on character's speed stat
    - **BotteryCharacter:** the class of the character which the player controls (this class manages the character's components like the movement component, stat component etc.)
  - **Component:** arbitary component classes that can possibly be reused across unrelated actors
  - **DataAsset:** classes that define what data a UE data asset holds
  - **Effect:** contains classes related to effects that alters actor data (flags, resources, stats)
    - **Effect:** an abstract base class Effect, which effects like ChangeFlagEffect and DamageEffect inherits from
    - **CollisionEffectComponent:** another abstract base component class which stores an Effect
    - **HitEffectComponent:** subclass of CollisionEffectComponent that applies the stored effect when a blocking collision occurs
    - **OverlapEffectComponent:** subclass of CollisionEffectComponent that applies the stored effect when a non-blocking collision (an overlap) occurs
  - **Orb**
    - **Orb:** orb class which orb blueprints derive from
    - **OrbMovementComponent:** derives from UProjectileMovementComponent, move speed based on orb's speed stat
  - **PlayerProgression:** for simple saving and loading of high score and max health/battery (which grows by 1 for every 100 score achieved in a game)
    - **BotterySaveGame:** class that defines what a save file should contain (high score and max health/battery)
    - **PlayerProgressSubsystem:** a UGameInstanceSubsystem that is created when the game launches and lasts for as long as the game runs, it loads save file when it is created and provides function to save progress to file (more on  UE's subsystems [here](https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-subsystems-in-unreal-engine) and UGameInstance [here](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/UGameInstance))
  - **Spawner:**
    - **Spawner:** a generic spawner class that spawns actors from a weighted spawn table
    - **OrbSpawner:** a subclass of Spawner that spawns actors(orbs) from different spawn tables based on the current score
  - **UEFramework:** subclasses of UE's gameplay framework classes