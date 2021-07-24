# Tennis For One - That One Being You
- [Tennis For One - That One Being You](#tennis-for-one---that-one-being-you)
- [TECHSTUFF](#techstuff)
- [Story](#story)
- [Gameplay](#gameplay)
  - [Matches](#matches)
    - [Controls](#controls)
    - [Shot types](#shot-types)
      - [Normal shot](#normal-shot)
      - [Slice shot](#slice-shot)
      - [Powershot](#powershot)
    - [Running distance](#running-distance)
  - [Between Matches](#between-matches)
    - [Skill points](#skill-points)
      - [Power skil](#power-skil)
      - [Running distance skill](#running-distance-skill)
      - [Dexterity](#dexterity)
- [Specific engine parts](#specific-engine-parts)
  - [Cinematic](#cinematic)

# TECHSTUFF
For audio on arch ,install pulseaudio-alsa

# Story
You are the last person on earth. A nuclear fallout has killed every single living being on the planet. While seeking shelter, you come across a rec facility, with a top of the line Zer 0-G Tennis court, with a built in AI. With a decent chunk of supplies left, you make camp in the facility, hoping to survive for a long while.

After finishing the game and beating the 3 AI levels, the AI terminates the player. A cinematic will play, revealign that the AI caused the fallout, because a supreme leader beat it at tennis.


# Gameplay
## Matches
Tennis matches are confined in a [DESIGN ARENA]. Inside of said space, you are placed in a Zero-G plexi rectangle. After a brief countdown, the ball will be served by the player first. After serving, each bounce of the ball will slow it down to a minimum amount, which is determined by difficulty (EG.: progression). If the player or the AI lets the ball slip to their backboard, the other person wins the round. [DESIGN SCORING SYSTEM]. First one to win 2 games wins the match.
### Controls
The player controls the racket with their mouse. Depending on their [skill level](#skill-points), the racket may move faster towards the mouse. Racket angle is dependent on the distance from the center point.
![](README_images/racketmovement.png)

### Shot types
There are 3 different ways to hit the ball.
#### Normal shot
Normal shots are the ones where the racket simply hits the ball without any further user input. The ball's velocity will increase slightly and the direction of the ball will be calculatedy by the distance from the middle of the racket, by normal rules. 
#### Slice shot
With a certain key, the player can initiate a *Slice Shot*. A Slice shot leaves the racket in a Semi-frozen state, where it sort of tries to go to the cursor, but is bound towards the point in which the racket was when the slice key was pressed. Uppon another press of the key (and given that the cursor is far enough away.), the racket will quickly ([although quickness depends on skill level](#skill-points)) snap to the cursor. But, if the conditions are not met, and the cursors is not far enough away, the racket will simply return to its default state. If the ball is hit during the snap-event, where the "slicing" rakcet is still travelling to the cursor, the ball's direction will grealty change, given the angle, and will also get a speed boost, although not a significant amount. This shot is mainly used to bounce the ball around, confusing slower player.
#### Powershot
The most powerful shot type. The player first needs to fill up their power bar in order to use this. Hitting balls regurarly gives a certain amount of fillage to the bar, slice-shots give a lot more, 1.5 times as much. If the bar is filled, pressing the power shot button freeze the racket in place. In this state, the bar begins to drain. If the player presses the button while the bar is not fully drained, the move will be canceled, and the ***drained*** power bar remains. If, however, the bar is fully depleted, another press of the button will swing the racket. If the ball is hit during this swing, the ball's trajectory wont change as much, however, the ball will gain a significant speed boost.

### Running distance
Running distance is a distance which you run. Very descripive, I know. The ball doesnt just shoot past your racket if you miss it. You move back *with* the ball for a certain amount of time. The amount is set by a skill. The game checks one of the coordinates (probably Z) to see how back is the racket OR the ball. If the game sees that the ball will NOT collide with the racket, it'll move the racket back, as far as the skill permits it. At the end of said skill, time will gradually slow down, to a set amount, giving the player, not necesarilly more time to react, since the racket moves proportionally to the slowed down time, but more time to do small adjustments. Otherwise, if it sees it colliding, it'll simply stop pushing the racket back, allowing the player to hit the ball. After serving, the racket will swiftly go back to the original position, *smoothly*. AI will not have this feature. This is just to account for our ape brain.  

The running distance is only active ***while*** the player is not doing any special shots.

## Between Matches
### Skill points
#### Power skil
The most universally undestandable skill. Have more power, have a faster ball. It will not change the trajectory of the ball, only its bouncing-back velocity
#### Running distance skill
Simply permits the [running distance system](#running-distance) to have more distance, thus more time to react. It will not modify the slow-down effect, which activates at the end of the running distance, actuation point, scale, speed or ratio.
#### Dexterity
The speed of which the racket follows the cursor.

# Specific engine parts
## Cinematic
A set of camera positions are saved into the level file. Apart from the .blend file, the asset packer packs an intro.cin(ematic) and an outr.cin file aswell. these texts files determine which camera position is shown and for how long.
