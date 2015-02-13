all:
	gcc -c irc-client.c -o irc-client.o
	gcc -c network.c -o network.o
	gcc -pthread irc-client.o network.o -o irc-client
clean:
	rm irc-client
	rm *.o
