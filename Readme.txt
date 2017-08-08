
To run assignment 2:
	-run make
	-run the executable using the following format:
		./A2				
		
Note: After the game quits the main thread waits for some time like around 5-10 seconds
for the threads that spawns the rows with log threads to finish because the log threads 
sleeps for some time and that's why the delay occurs and the moment it wakes up 
it joins the log threads cleans everything and entering a key will quit the game.