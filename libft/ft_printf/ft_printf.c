/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:37:06 by fparis            #+#    #+#             */
/*   Updated: 2023/11/27 23:40:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_convert(char c, va_list args, int res)
{
	if (c == '%')
		return (res + ft_putchar_l('%'));
	if (c == 'c')
		return (res + ft_putchar_l(va_arg(args, int)));
	if (c == 's')
		return (res + ft_putstr_l(va_arg(args, char *)));
	if (c == 'p')
		return (res + ft_ptrhexa(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (res + ft_putnbr_l(va_arg(args, int)));
	if (c == 'u')
		return (res + ft_putnbr_un(va_arg(args, unsigned int)));
	if (c == 'x')
		return (res + ft_putnbr_hexa(va_arg(args, int), 1));
	if (c == 'X')
		return (res + ft_putnbr_hexa(va_arg(args, int), 0));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		res;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	res = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			res = put_convert(str[i + 1], args, res);
			i++;
		}
		else
			res += ft_putchar_l(str[i]);
		if (res == -1)
			return (res);
		i++;
	}
	return (res);
}
