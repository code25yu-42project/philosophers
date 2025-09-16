#include "philo_thread.h"

long	ft_atoi(const char *str)
{
	long	flag;
	long	res;

	flag = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
	str++;
	if (str && *str == '-')
	{
		flag *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (str && *str >= '0' && *str <= '9')
	{
		res = 10 * res + *str - '0';
		str++;
	}
	if (*str)
		res = 0;
	return (flag * res);
}

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*res;

	res = (unsigned char *)ptr;
	while (len-- > 0)
		*res++ = (unsigned char)c;
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}
