CMPS109 HW4 README

TO COMPILE:
$ make

PARTNER:
Krishna Velury, kvelury@ucsc.edu

TO RUN:
$ ./hw4

TO DELETE GENERATED FILES:
$ make clean

WHAT I LEARNED: This program, for me, was all about the difficulty of dealing with developing
AI. My partner Krishna and I blazed through the set up steps of creating a player that could
place pieces and a game board, and very quickly had a win condition set up. However, dealing 
with our own personal goal for AI was, in retrospect, a bit lofty. First off, we did not
entirely meet our goals. While our AI is smart, in one, and only one, specific case, he makes
an illegal move, and can eventually 'win'. However, we also feel like we succeeded quite a lot.
Our AI moves from top to bottom, observing the pie rule and any swaps it has made, and attempts
to make a connection in a simplistic, yet single-mindedly brutal manner. It will negotiate any
possible traps (save for the one case where it moves outside the hex for some reason) and 
eventually snake to the bottom should you be unable to win. It is not a very difficult AI to
beat when you figure out the mechanic, but it isn't overly simple. I have never taken a course
for AI, and I feel, since I did the majority of the AI work, that I have done somewhat well
for my lack of experience.
