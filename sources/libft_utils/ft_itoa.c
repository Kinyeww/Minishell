#include <stdlib.h>

static int	ft_numlen(long num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(char *str, long num, int len)
{
	str[len] = '\0';
	len--;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
	{
		str[0] = '0';
		return ;
	}
	while (num > 0 && len >= 0)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = ft_numlen(num);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_putnbr(str, num, len);
	return (str);
}