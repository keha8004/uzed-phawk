#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

// Test with Pizhawk - send one byte
// Compiled into a .elf file to be run on the MicroZed

int main() {


	// Open UART port
	char* filename = "/dev/ttys0";
	int fd; 	// File descriptor for the port
	fd = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1) {
		perror("didn’t open port filename");
	}
	else {

		fcntl(fd, F_SETFL, 0);
	}

	// Set baud rate
	struct termios options;	// Get the Current options for the port
	tcgetattr(fd, &options);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200); 	// Set the baud rates to 19200
	options.c_cflag |= (CLOCAL | CREAD); // Enable the receiver and set local mode…
	tcsetattr(fd, TCSANOW, &options);	// Set the new options for the port…

	// Write data to the port
	ssize_t n = write(fd, "FF" , 2);
	if(n < 0)

		fputs("write() of 2 bytes failed!\n", stderr);

	// Check for data from PixHawk
	// If there is a flag, send over a warning signal to PixHawk
	// close port
	close(fd);

	return(0);

}