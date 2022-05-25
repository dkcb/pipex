/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_splitll.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 15:16:26 by dkocob        #+#    #+#                 */
/*   Updated: 2022/04/20 13:54:44 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

void	printlinklist(struct s_ll *start)
{
	struct s_ll *cur;
	// write (1, "Yo!\n", 4);
	cur = start;
	while (cur->next)
	{
		printf("Line:%s\n", cur->next->line);
		cur = cur->next;
	}
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!src)
		return (0);
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

struct s_ll	*newlnode(struct s_ll *prev, char *s, int len)
{
	char		*line;
	struct s_ll	*node;

	// printf ("strN: %s\n", s);
	node = malloc(sizeof(struct s_ll));
	line = malloc(sizeof(char) * len);
	ft_strlcpy(line, s, len);
	// printf ("Line: %s\n", line);
	node->line = line;
	if (prev)
		prev->next = node;
	printf("NNL: %s\n", prev->next->line);
	return (node);
}

char		**ft_splitll(char const *s, char c)
{
	char		**result;
	struct s_ll	start;
	struct s_ll	*node;
	int			i;
	int			i2;

	start.next = node;
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		i2 = i;
		while (s[i2] && s[i2] != c)
			i2++;
		// write (1, "Yo!\n", 4);
		printf("len: %d\n", i2 - i);
		if (i2 - i)
			node = newlnode(node, (char *)&s[i], i2 - i + 1);
		i = i2;
	}
	// printf("start: %s\n", start.next->line);
	// printlinklist(start.next);
	return (result);
}

int main()
{
	char **spl;
	int i = 0;

	spl = ft_splitll("*y1*b2*b3*", '*');
	printf("len:\n");
	// while (spl[i])
	// {
	// 	printf("%d: %s\n", i, spl[i]);
	// 	i++;
	// }
	return (0);
}
