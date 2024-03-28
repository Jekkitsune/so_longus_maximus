/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:16:50 by fparis            #+#    #+#             */
/*   Updated: 2023/11/17 14:50:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_putchar_l(char c);
int		ft_putnbr_l(int n);
int		ft_putstr_l(char *s);
size_t	ft_strlen(const char *str);
int		ft_putnbr_un(unsigned long n);
int		ft_ptrhexa(void *ptr);
int		ft_putnbr_hexa(unsigned int nb, int up);

#endif
