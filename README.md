moosetimer
==========

Moosetimer is a simple Arduino-based timer.

It was inspired by the Pomodoro method of time management. In an effort to sit less and get up more, I wanted to be reminded
every 25 minutes to get up and walk around/stretch. There are several good web-based timers -- however, I found that I kept forgetting to
set/reset the timer. By creating a physical object it wouldn't be as easy to forget as a tab.

I was also inspired by this Instructables guitar amp project I built (http://www.instructables.com/id/Make-a-Sweet-Portable-Guitar-Amp/). 
It was cased in a gum container, which was a good size and an inexpensive housing. This timer was a good project to experiment with that approach.

The concept is simple:

- When you turn it on, the first of 5 LEDs starts slowly blinking.
- Every N time interval (where N is configurable, defaulting to 5 minutes) the previous LED stays lit, and the next LED starts blinking.
- After 5 * N minutes, a sound is emmitted and all LEDs remain lit.
- Pushing the button at any point will reset the timer.

I used an Arduino nano clone so it would fit nicely in the gum container. I also used a big arcade-style button I had lying around
from another project, but any momentary on button would work fine.

A schematic, built in ExpressSCM, is included.

The moosetimer code and schematic are public domain. Do with them as you will.

