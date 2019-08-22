/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 15:19:28 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/19 16:04:06 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_remal(char *str, int isneg)
{
	int		i;
	char	*res;

	res = 0;
	if (isneg < 0)
		*str = '-';
	while (!(*str == 45 || (*str > 47 && *str < 58) ||
		(*str > 64 && *str < 71)))
		str++;
	i = 0;
	while (str[i] != '\0')
		i++;
	res = ft_strnew(i);
	if (res != NULL)
		return (ft_strcpy(res, str));
	return (0);
}

static void	ft_check_sign(long int *n, int base, int *isneg)
{
	*isneg = 1;
	if (*n < 0)
	{
		if (base == 10)
			*isneg = -1;
		*n = -(*n);
	}
}

char		*ft_itoa_base(long int n, int base)
{
	char	str[33];
	char	*tmp;
	int		isneg;
	char	*xnbrs;

	xnbrs = "0123456789ABCDEF";
	n = (int)n;
	ft_check_sign(&n, base, &isneg);
	str[32] = '\0';
	tmp = &str[31];
	if (n == 0)
	{
		*tmp = '0';
		tmp--;
	}
	while (n > 0)
	{
		*tmp = xnbrs[n % base];
		tmp--;
		n /= base;
	}
	return (ft_remal(tmp, isneg));
}
