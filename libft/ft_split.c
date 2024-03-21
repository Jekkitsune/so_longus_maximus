/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:42:37 by fparis            #+#    #+#             */
/*   Updated: 2023/11/07 16:34:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**gen_tab(char const *s, char c)
{
	int		count_words;
	int		i;
	char	**tab;

	i = 0;
	count_words = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab = malloc((count_words + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[count_words] = NULL;
	return (tab);
}

static char	*make_tab(char const *s, int start, int end)
{
	char	*tab;
	int		i;

	tab = malloc(((end - start) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = start;
	while (i < end)
	{
		tab[i - start] = s[i];
		i++;
	}
	tab[i - start] = '\0';
	return (tab);
}

static void	*free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		nb_word;
	int		word_start;

	res = gen_tab(s, c);
	nb_word = -1;
	i = 0;
	while (res != NULL && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			nb_word++;
			word_start = i;
			while (s[i] && s[i] != c)
				i++;
			res[nb_word] = make_tab(s, word_start, i);
			if (res[nb_word] == NULL)
				return (free_tab(res, nb_word + 1));
		}
	}
	return (res);
}
