/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:25:27 by fparis            #+#    #+#             */
/*   Updated: 2023/11/17 14:52:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_nb(unsigned int n)
{
	char	chara;
	int		res;

	if (n < 10)
	{
		chara = n + '0';
		write(1, &chara, 1);
		return (1);
	}
	else
	{
		chara = (n % 10) + '0';
		res = 1 + write_nb(n / 10);
		write(1, &chara, 1);
		return (res);
	}
}

int	ft_putnbr_l(int n)
{
	unsigned int	u_n;
	int				res;

	res = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		u_n = -n;
		res++;
	}
	else
		u_n = n;
	return (res + write_nb(u_n));
}
