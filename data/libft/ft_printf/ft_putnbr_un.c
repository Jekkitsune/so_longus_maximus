/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:38:49 by fparis            #+#    #+#             */
/*   Updated: 2023/11/17 14:53:35 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_un(unsigned long n)
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
		res = 1 + ft_putnbr_un(n / 10);
		write(1, &chara, 1);
		return (res);
	}
}
