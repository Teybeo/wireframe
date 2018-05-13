#ifndef ERRORS_H
#define ERRORS_H

#define DEV 1

#if DEV == 1
	#define ERROR_OPEN_FAILED "Couldn't open file"
#else
	#define ERROR_OPEN_FAILED "error"
#endif

void	exit_with_message(char const *string);

#endif
