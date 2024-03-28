/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:24:05 by fparis            #+#    #+#             */
/*   Updated: 2024/02/21 21:54:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_revdigit(int nb, int nb_digit)
{
	int	len;
	int	i;

	len = ft_intlen(nb);
	if (nb_digit < 1 || nb_digit > len)
		return (0);
	i = 1;
	while (i < nb_digit)
	{
		nb -= (nb / (ft_power(10, len - 1)) * (ft_power(10, len - 1)));
		i++;
		len--;
	}
	nb = nb / (ft_power(10, len - 1));
	return (nb);
}
