/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:23:40 by fparis            #+#    #+#             */
/*   Updated: 2023/11/17 14:52:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_hexaptr(unsigned long nb)
{
	char	chara;
	int		res;

	res = 0;
	if (nb < 16)
	{
		if (nb < 10)
			chara = '0' + nb;
		else
			chara = 'a' + (nb - 10);
		write(1, &chara, 1);
		return (1);
	}
	else
	{
		res = 1 + write_hexaptr(nb / 16);
		nb = nb % 16;
		if (nb < 10)
			chara = '0' + nb;
		else
			chara = 'a' + (nb - 10);
		write(1, &chara, 1);
		return (res);
	}
}

int	ft_ptrhexa(void *ptr)
{
	unsigned long	nb;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	nb = (unsigned long)ptr;
	write(1, "0x", 2);
	return (write_hexaptr(nb) + 2);
}
