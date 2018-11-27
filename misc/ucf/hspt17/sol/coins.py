# https://en.wikipedia.org/wiki/Nim
# This problem is a popular variant of the game of nim.
# Found at the link above you can find the derivation and solution to this
# particular variant known as "The Subtraction Game".

T = int(input());
for t in range(1,T+1):
	line = input().split(' ');
	n = int(line[0]);
	k = int(line[1]);
	first = line[2];
	snd = 'Matthew' if (first == 'Bill') else 'Bill';
	
	if( n % (k+1) == 0 ):
		print('Game #'+str(t)+': '+snd);
	else:
		print('Game #'+str(t)+': '+first);
