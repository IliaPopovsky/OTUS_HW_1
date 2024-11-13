#makefile для seeker_zip.c
seeker_zip: seeker_zip.c
	gcc  -Wall -Wextra -Wpedantic -o seeker_zip seeker_zip.c -lpthread -no-pie

