To Run: (only tested in unix.ic, please only run in THIS enviornment)
-------------------------------
g++ assignment4.cpp

Write-up
--------------------
With Homework 5, I implemented a game of Hex that allows the user to play
against a computer. I used the Monte carlo process that was specified in the
instructions of the homework. The Monte Carlo was pretty simple to implement,
but the result from implementing it isn't a very smart AI. I have found out that
there are more required analysis in order to make the AI a lot smarter. For this
assignment though, Ira said he only expected a functioning Monte Carlo.

I simply take a copy of the board, put in random spots for both players 
until one is a victor. If the AI doing the move is the victor, 
it stores that position. The position with the highest number is the move that
the AI chooses. I currently have it set to 10000 but that can be changed in
Global.h. I also have it currently set to one AI and one player playing against each
other since it was not speified if we need to have 2 AI's playing against each other.
