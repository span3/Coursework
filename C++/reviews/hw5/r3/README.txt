_____ General info _____

Files:    hex.cpp    README.txt

Partner: N/A

I created and tested my program on Windows using the CodeBlocks IDE and MinGW.
I also tested it on Unix using g++, but in the user input sections, backspace failed in Unix.
Unfortunately, there was nothing I could do to fix the backspace issue, as Unix recognized
it as a separate character (^H).







_____ Compiling _____

I would recommend compiling and running the program on Windows if possible by using an IDE or just
typing "g++ hex.cpp" into a command line window in the current directory.


Although the program runs on Unix (also compiled by "g++ hex.cpp"), when inputting coordinates
you will have to be careful to type them properly, since backspace is not recognized correctly.
Therefore I would not recommend that you run the program on Unix unless necessary.







_____ Executing _____

To execute the program, simply double click the executable created (in Windows), or run it from
the terminal window. It may be named hex.exe, a.exe, or a.out depending on how you compiled it.
You can also run the executable from an IDE after compiling.

After starting the program, it will prompt you for a board size (side length must be between 7 and 21).
After this, you will be prompted to enter the coordinates for your moves. 
The format for moves is "x y" (without the quotes).

In the rhombus,     This is the x axis
                   0________________+
                    \                
                     \               \
  This is the y axis  \               
                       \               \
                        + - - - - - - - -

I have labeled the x and y positions of all indices. Past 10, to save space, the x coordinate alternates
between being shown on the top and on the bottom of the rhombus. Hopefully this makes it easier to input
coordinates, as I've found this to be a bit difficult.


Originally, you'll start out as o's, trying to make a path from the left to the right of the board.
If you choose a location on or next to the line that runs between the 2 +'s in the above diagram, the
computer will swap places with you. If the computer swaps with you, you will now be playing as x's, and
you will have to make a path from the top to the bottom of the board. I chose this line because points 
on and next the line had the highest number of minimum-weight solutions that ran through those points.


Lastly, although I tried to make the computer's movements realistic, it was challenging. It uses a
weighted random system, and as a result it may take a while if you're trying to lose. I have a good
idea for the AI for program 5, but I did not have time to implement it here.







_____ What I've learned _____


In this assignment, I learned how to generate a basic artificial intelligence algorithm for the Hex board game. While no perfect solution for this game has been found for board sizes above a certain amount, I attempted to create a system that would most closely resemble reasonable human decisions.
	For my AI program, I did not need to adjust the inner workings of my original Hex program, so I focused on the strategy behind the AI. I learned about Monte Carlo algorithms and sampling, and how to implement priority into artificial intelligence when deciding on moves.
	In my program, a 2D array is generated on each computer turn to determine the highest priority, and a sample point is selected. After evaluated, if it is a reasonable location strategically, that becomes the computer’s move. If not, it reevaluates the array. 
