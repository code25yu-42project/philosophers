#ifndef ERRNO_H
# define ERRNO_H

typedef enum e_errno
{
	RETURN_SUCCESS = 0,
	RETURN_FAILURE = 1,
	MALLOC_FAILURE = 1,
	INVALID_ARGV,
	EXTERNAL_FAILURE
}	t_errno;

typedef enum e_boolean
{
	FALSE,
	TRUE
}	t_boolean;

# define PHILO "philo: "
# define MSG_INVALID_ARGV "invalid arguments.\n"
# define MSG_EXTERNAL_FAILURE "error of external functs.\n"
# define MSG_MALLOC_FAILURE "malloc failed.\n"

#endif
