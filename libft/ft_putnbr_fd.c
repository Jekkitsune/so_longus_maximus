/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:25:27 by fparis            #+#    #+#             */
/*   Updated: 2023/11/03 18:33:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nb(unsigned int n, int fd)
{
	char	chara;

	if (n < 10)
	{
		chara = n + '0';
		write(fd, &chara, 1);
	}
	else
	{
		chara = (n % 10) + '0';
		write_nb(n / 10, fd);
		write(fd, &chara, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_n;

	if (n < 0)
	{
		write(fd, "-", 1);
		u_n = -n;
	}
	else
		u_n = n;
	write_nb(u_n, fd);
}
