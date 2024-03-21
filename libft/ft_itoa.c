/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:45:31 by fparis            #+#    #+#             */
/*   Updated: 2023/11/03 16:52:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	if (n < 0)
		len = 2;
	else
		len = 1;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	putnbr_str(unsigned int n, char *str, int i)
{
	if (n < 10)
		str[i] = n + '0';
	else
	{
		putnbr_str(n / 10, str, i - 1);
		str[i] = (n % 10) + '0';
	}
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;

	len = int_len(n);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		putnbr_str((unsigned int)n * -1, res, len - 1);
	}
	else
		putnbr_str((unsigned int)n, res, len - 1);
	return (res);
}
