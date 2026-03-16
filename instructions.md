# Instructions

## Wave 0: Intial Setup
### Identifier
1. With your partners choose a 3 letter unique identifier for your files.
1. Confirm with the instructor that this identifier is available.
### Fork/clone
1. ONE partner forks the repository.
1. That partner adds the others as collaborators.
1. EVERYONE clones the fork.
1. EVERYONE `cd`s into the repository and opens VS Code, reopening in a dev container. 
### Setting an upstream
1. EVERYONE checks their origin:

    ```git remote -v```

    This should show the fork as the origin.
1. EVERYONE adds an upstream:

    ```git remote add upstream UPSTREAM_CLONE_URL```

    UPSTREAM_CLONE_URL should be the clone URL for your cohort, NOT the fork your group made
1. EVERYONE checks their upstream

    ```git remote -v```

    origin and upstream should have different URLs
## Wave 1: Branching
1. ONE partner (partner A) should make an "dev" branch and switch to it:

    ```
    git branch dev
    git switch dev
    ```
1. That ONE partner (partner A) should push the dev branch to origin

    ```
    git push origin dev
    ```
1. The OTHER partners will still be on main. Doing a pull will bring down the new branch, which they can then switch to.

    ```
    git pull
    git switch dev
    ```
1. Everyone should now be on the `dev` branch. EVERYONE run `git status` to verify this.

ALL OF YOUR COMMITS SHOULD BE IN BRANCHES. DO NOT EVER MAKE NEW COMMITS DIRECTLY TO MAIN, ONLY PULLS/MERGES FROM UPSTREAM.

## Wave 2: Directory setup
In this section we will be setting up some directories and checking that pushing/pulling on our branches works. Please actually do this in 3 commits, alternating partners so we can check that all the pushing/pulling is working correctly. All of this will happen on the `dev` branch, `main` will remain unchanged!

As you go through, DO NOT COMMIT ANY CHANGES TO FILES OTHER THAN THE ONES FOR YOUR GROUP. This includes markdown files, source files, etc.

### Directory in src
1. VERIFY YOU ARE ON THE DEV BRANCH.
1. ONE partner should make a new directory inside the `src` directory. This new directory should be the 3 letter identifier of your group.
1. Inside the directory, make a new empty file named `.gitignore` NOTE THAT IT STARTS WITH A PERIOD AND IS ALL LOWER CASE. You must match the name exactly!
    > We are making this `.gitignore` so that git will pick up this directory in a commit. git does not track empty directories, so we will create an empty file to ensure the directory gets tracked. We will later be filling this with useful files, but for now we're just setting up the structure.
1. VERIFY AGAIN that you are on the dev branch.
1. add/commit/push new directory
1. The other partners should verify they are on the dev branch, then pull

### Directory in include
1. Have the OTHER partner follow the above steps to make a directory with your identifier in the `include` directory. Make sure to add a `.gitignore`
1. add/commit/push/pull

### Directory in graphics
1. Switch parnters again and repeat to create a subdirectory in `graphics`.

### Pull Request
Make a PR to the upstream. It should come from your `dev` branch. Your `main` branch should still be unchanged!

## Wave 3: Exploration
In this section you will be exploring the repository and looking at an example microgame.

1. EVERYONE make the game.
1. EVERYONE play the game. Fair warning: it is quite ugly and unfun right now and there is only one microgame.
1. AS A GROUP explore the below files TOGETHER. In a shared doc, answer the below questions TOGETHER. DO NOT SPLIT UP THE WORK.

### Files to Explore Closely (in this recommended order)
- `include/aub/aub_test_game.h`
- `src/aub/aub_test_game.cpp`
- `include/aub/player.h`
- `src/aub/player.cpp`
- `include/mj/mj_game.h`

### Questions to answer
Answer the below questions IN A FILE OUTSIDE OF THIS REPOSITORY (maybe a Google Doc?)

### Source Questions
1. What is the name of the class reposible for the "Leave the screen" microgame?
1. What is it a subclass of?
1. What instance variable(s) does the "Leave the screen" microgame have?
1. How long does this microgame last?
1. How does the game signal when to end early?
1. How often is `play` called?

### Research Questions
Answer the following questions. Consider using online searches or AI for help, but answer in your own words.

1. What does ```[[maybe_unused]]``` mean in C++?
1. What does ```override``` mean in C++?
1. What is a namespace in C++?


## Wave 4: Game skeleton

### Updating from upstream
Follow the instructions in the [Git Branching Cheatsheet](./gitBranchingCheatsheet.md) to update from the upstream. Then, ENSURE YOU ARE BACK ON A BRANCH OTHER THAN MAIN TO CONTINUE WORK. Following these instructions will pull in the new updates from your classmates to the game. In the future, always do this before starting work so that you will stay up-to-date and lessen the chance of merge conflicts.

### Creating a game header
In this section we will be making a header file that holds the class declaration for your game. I STRONGLY recommend looking at ```include/mj/mj_game.h``` for reference and ```include/aub/aub_test_game.h``` for an example.
1. In the `include/xxx` directory (where xxx is your 3 letter identifier) make a file ```xxx_game_name.h``` (where xxx and game_name are replaced with your identifier and what you want to call the game).
1. Add an include guard with the name `XXX_GAME_NAME_H`
1. Include `mj/mj_game.h`
1. Make a namespace with your 3 letter identifier after the include statement for `mj_game.h`, but still within your include guard.
1. Inside your namespace, make a class ```xxx_game_name``` that publicly extends ```mj::game```.
1. Add declarations (BUT NOT IMPLEMENTATIONS) for the following public member functions. Their signatures must match EXACTLY what is required, overriding the superclass. `aub_test_game` is a useful example to follow!
    1. Constructor that takes `(int completed_games, const mj::game_data& data)` as arguments
    1. `title`
    1. `total_frames`
    1. `play`
    1. `victory`
    1. `fade_in`
    1. `fade_out`
1. Make sure you're on a branch other than main, make sure your're not adding any files unintentionally, then add/commit/push

### Creating a dummy implementation
In this section we will make a dummy implementation of your game. We will make sure everything is set up properly before implementing the actual game logic. I STRONGLY recommend looking at ```src/aub/aub_test_game.cpp``` for an example.

1. Create a `src/xxx/xxx_game_name.cpp` file.
1. Include your header you created.
1. Make a namespace `xxx`.
1. Create an implementation for your constructor. You can leave the body of the constructor empty, but you MUST call the superclass constructor (`mj::game`) as the first item in your initializer list. Call the superclass constructor with your 3 letter id: `mj::game("xxx")`. You can see `src/aub/aub_test_game.cpp` for an example.
1. Create dummy implementations for all required member functions. We are not actually writing your game logic yet, just setting up the class so we can test that the skeleton is written correctly.
    1. Return some string for a title in `title`. This is what will be displayed to the player when your game starts
    1. Set `total_frames` so your game has a time limit of a few seconds.
    1. You can construct a default `mj::game_result` and return it in `play`
    1. Have `victory` always return `false` for now.
    1. You can leave the bodies of `fade_in` and `fade_out` empty for now, but they must still be in the `.cpp`
1. `make` your game and fix any compilation issues. Your microgame will not yet show up when your run the ROM, but we want to make sure everything compiles.
1. Make sure you're on a branch other than main, make sure your're not adding any files unintentionally, then add/commit/push

### Registering your game and credits
1. In `xxx_game_name.cpp` add an anonymous namespace after your includes but before the xxx namespace.
1. Make 4 `constexpr bn::string_view` arrays for code credits, graphics, credits, sfx credits, and music credits. Fill them with your names or pseudonyms. Note that this is public online, so only post a name you feel comfortable with. You can have an array with a single empty string for any category that you do not need.
1. OUTSIDE OF ANY NAMESPACE, call `MJ_GAME_LIST_ADD(xxx::xxx_game_name)`. This will register your game so it will be included in the game list and be made possible to play.
1. ALSO OUTSIDE OF ANY NAMESPACE call the following macros with your string view arrays to add to the credits:
    - `MJ_GAME_LIST_ADD_CODE_CREDITS`
    - `MJ_GAME_LIST_ADD_GRAPHICS_CREDITS`
    - `MJ_GAME_LIST_ADD_MUSIC_CREDITS`
    - `MJ_GAME_LIST_ADD_SFX_CREDITS`

### Testing your game
1. Make your game and resolve any compilation errors.
1. Run the game, and choose your game from the DEBUG menu. When you choose your game in the DEBUG menu, it will repeatedly play your game and no others. This is useful for testing purposes.
    > Right now your game should display the title, but there will be nothing to do. You will repeatedly lose the game after a few seconds. This is what is expected for now.
1. Close the emulator, re-run the game, and watch the credits to make sure your names were added (you can hold the A button to speed up the scrolling of the credits).
1. Close the emulator, re-run the ROM, and play the main game not in debug mode by choosing `PLAY`. It will randomly intersperse games, and your game skeleton should show up intermittently.
1. Once you are satisfied your game is working, make sure you're on a branch other than main, make sure your're not adding any files unintentionally, then add/commit/push

## Wave 5: Game prototype
Begin implementing your game! By the end of this wave you do NOT need to have a finished game, nor a game that is fun or looks good. You do not need to have all your game mechanics implemented. But it should be making progress towards your overall game goal. You do not need to worry about multiple difficulty levels or game speeds.

### Functionality required for Wave 5
- The game must take input from the player
- It must be possible to win/lose the game
- You should have at least one new sprite that you created and that is used in the game
- The game must not crash
- You must create and use at least one ADDITIONAL class that your game uses (for example, `aub::aub_test_game` uses `aub::player`)
- Your code must have pulled from upstream the recent changes from your classmates in other groups. Pull frequently from upstream!

### Code requirements for Wave 5
- YOU MUST ONLY MAKE CHANGES IN DIRECTORIES WITH YOUR THREE LETTER IDENTIFIERS
- YOU MUST NOT COMMIT DIRECTLY TO MAIN
- ALL NEW CODE MUST BE IN YOUR GROUP'S NAMESPACE
- New headers must have include guards.
- You MUST NOT read keypad input in `fade_in`/`fade_out`
- You MUST NOT call `bn::core::update()`
- Any sounds/music must ONLY be played using member functions from the `mj::game` superclass: `play_music`, `play_sound`, or `play_jingle`

### Hints
- START SMALL AND TEST FREQUENTLY.
    > If you make a ton of changes and it doesn't work, it's really hard to debug! Making small changes helps you make sure things are working at each step. Make small subgoals, e.g. first just make a sprite show up.
- PULL FROM UPSTREAM AND MAKE COMMITS FREQUENTLY.
- Consider what instance variables you will need, and add them to the header for your game
- Add initialization for those instance variables in the initializer list where appropriate
- You do not need to write your own `while` event loop! `update` is repeated called once per frame.
- You can make more branches if it's helpful for coordination with your teams.

Once you have a prototype ready for review, make a PR from your branch. Make a NEW BRANCH off of that branch so you can continue working on later waves as you wait for feedback.

## Wave 6: Functioning game

In this wave you will implement the rest of the gameplay functionality and handle difficulty. You do not yet need to have the graphics/sound perfect, but the gameplay will have all of the game mechanics you need implemented.

### Pre-reqs
If you have feedback on a PR, PLEASE RESOLVE THOSE ISSUES BEFORE WORKING ON NEW FUNCTIONALITY.

#### Resolving issues

1. Make sure you are on the dev branch.
1. Resolve issues described in PR feedback. 
1. Make/run your game to verify they are fixed.
1. Commit/add/push.

#### Making a new branch and pulling upstream changes

1. Make sure you are still on dev
1. Make a new branch off of dev
1. Switch to that branch
1. Switch to main
1. Update from upstream: [Git Branching Cheatsheet](./gitBranchingCheatsheet.md)
1. Switch back to your new branch
1. Merge the updates from main
1. Push up your changes and have your partners pull down the new branch.

### Game functionality

MAKE SURE YOU HAVE UPDATED FROM UPSTREAM. Finish implementing the game mechanics. All of your gameplay functionality should be there! Don't forget to add/commit/push (making sure you're not pushing to a branch with a pending PR)

### Difficulty

MAKE SURE YOU HAVE UPDATED FROM UPSTREAM. Implement 3 tiers of difficulty. Your game should call `recommended_difficulty_level` (see `mj_game.h` for details and `aub_test_game` for an example). It will be accessible as a member function on your game class because your class is a subclass of `mj::game`. You do not need to redeclare this method in you header nor reimplement it. You can just call it. It is currently set up such that the first time your game is played it will be EASY, the second time it will be NORMAL, and later times will be HARD. Therefore you can test your 3 difficulty levels by selecting your game from the DEBUG menu and playing it multiple times.

Your game should become harder in some substantive way. Some suggestions:
- More enemies to avoid
- More collectables required
- Faster speed

However, remember that players will be seeing this microgame for the first time with very little introduction! Make it at least in theory possible to beat when seeing it for the first time.

Make/run, then add/commit/test. You should be tuning your game so that it's fun to play and an appropriate difficulty level.

### Submitting

Once you have added your difficulty levels, add/commit/push. Make a new PR! If you want to continue work past this, please make a new branch to continue your work.

## Wave 7: Prettifying and incorporating feedback
If you have feedback on a PR, PLEASE RESOLVE THOSE ISSUES BEFORE WORKING ON NEW FUNCTIONALITY.

If your PR is still open, please make a NEW BRANCH to continue your work.

PLEASE MAKE SURE TO PULL FROM UPSTREAM

### Incorporating Feedback

Please make improvements to your game based on the feedback you got from your classmates. You do not need to take every suggestion, but you should seriously consider what they say!

Some types of improvements:

- Making games easier/harder
- Fixing bugs
- Changing controls / game mechanics

Make/test, then add/commit/push

### Adding a background

Please create a nice looking background in LibreSprite and add it to your game. A few resources to help:
- Look at the example aub_test_game
- Look at the `regular_bgs` example in butano-contained
- The Butano importing assets [regular_bg section](https://gvaliente.github.io/butano/import.html#import_regular_bg)

Please pay attention to the size restrictions on the Butano importing assets page!

Make/run, then add/commit/push.

### Adding a sprite animation

At least one of your sprites must be animated. Some examples of possible types of animations

- Looping animation of blinking lights on a space ship
- Sprite that flips directions when moving in different directions
- Swirling black hole, twinkling stars etc.
- Explosion animation when player crashes

A few resources to help:
- Look at the example aub_test_game
- In the sprites example of butano-contained
    - sprites_animation_actions_scene function
    - sprites_animation_scene function

Make/run, then add/commit/push.

### Submitting
Make a new PR! If you want to continue work past this, please make a new branch to continue your work. Please submit your PR link on Canvas.