/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 15:16:26 by dkocob        #+#    #+#                 */
/*   Updated: 2022/04/14 15:37:07 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lncnt(char const *s, char c)
{
	int	ln;

	ln = 0;
	while(s[i] && s[i] == c)
		i++;
	while(s[i])
	{
		while(s[i] && s[i] != c)
			i++;
		while(s[i] && s[i] == c)
			i++;
		ln++;
	}
	return (ln);
}

static char		**ft_malloc_array2(char const *s, char c, size_t x, size_t y)
{
	char	**result;
	int		i;

	i = 0;
	while(s[i])
	{
		while(s[i] == c)
			i++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_malloc_array2(s, c, 0, 0);
	if (result == NULL)
		return (NULL);
	return (result);
}
