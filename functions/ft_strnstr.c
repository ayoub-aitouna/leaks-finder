/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:09:18 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:09:19 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leak_finder.h"

static char	*check_if_is_the_one(const char *little, const char *big,
		unsigned int i, unsigned int len)
{
	unsigned int	j;
	size_t			ci;
	size_t			llen;

	llen = ft_strlen(little);
	ci = i;
	j = 0;
	while (little[j] && big[ci] == little[j])
	{
		if (j == llen - 1 && ci < len)
			return ((char *)&big[i]);
		ci++;
		j++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*rs;
	if(len == -1)
		len = ft_strlen(big);
	i = 0;
	j = 0;
	if (big == NULL || little == NULL)
		return (NULL);
	if (!little[j])
		return ((char *)big);
	while (big[i] && i < len)
	{
		rs = check_if_is_the_one(little, big, i, len);
		if (rs)
			return (rs);
		i++;
	}
	return (NULL);
}
