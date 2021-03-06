/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isxdigit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 15:22:54 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/20 19:51:23 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isxdigit(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 71) || (c > 96 && c < 103))
		return (1);
	return (0);
}
