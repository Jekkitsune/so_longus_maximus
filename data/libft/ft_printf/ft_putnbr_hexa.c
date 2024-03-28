/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:38:57 by fparis            #+#    #+#             */
/*   Updated: 2023/11/17 14:51:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hexa(unsigned int nb, int up)
{
	char	chara;
	int		res;

	if (nb < 16)
	{
		if (nb < 10)
			chara = '0' + nb;
		else
			chara = 'A' + (nb - 10) + (('a' - 'A') * up);
		write(1, &chara, 1);
		return (1);
	}
	else
	{
		res = 1 + ft_putnbr_hexa(nb / 16, up);
		nb = nb % 16;
		if (nb < 10)
			chara = '0' + nb;
		else
			chara = 'A' + (nb - 10) + (('a' - 'A') * up);
		write(1, &chara, 1);
		return (res);
	}
}
