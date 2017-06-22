CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi score.cgi addc.cgi delc.cgi selc.cgi selscore.cgi hide.cgi selhide.cgi recovery.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
	cp *.cgi /usr/lib/cgi-bin/sx
	cp *.html /usr/lib/cgi-bin/sx
	sudo cp *.html /var/www/html 
