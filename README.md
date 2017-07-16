# Arduino Melody

This github repo is intended as a method to convert text-based music into arduino code for easy arduino programming. 

 The archetypal arduino call is the following:

	tone(8, NOTE_A4, 300);
	delay(400);

   This program simply converts from a specified format (shown below) to the more cumbersome one:

	<note><octave> <length[whqes]><dotted[.-]>
    
	where Note is one of C, D, E, F, G, A, B
		  Octave is one of 0-6
		  Length is one of 'w', 'h', 'q', 'e', 's' corresponding to the first letter of the length (whole, half, etc.)
		  Dotted is either '.' (dotted) or '-' (not dotted)

