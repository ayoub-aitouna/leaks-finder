/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_finder.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:28:45 by aaitouna          #+#    #+#             */
/*   Updated: 2022/11/02 00:28:47 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_FINDER
# define LEAK_FINDER

# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <execinfo.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

char	*get_next_line(int fd);
size_t	gt_strlen(const char *c);
void	*gt_calloc(size_t nmemb, size_t size);
char	*gt_strchr(const char *s, int c);
char	*gt_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void    *my_malloc(size_t size, const char *file, const char *function, int line);
#endif
