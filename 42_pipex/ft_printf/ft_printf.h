/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft/libft.h"
# include <stdarg.h>

int		ft_printf(const char *input, ...);
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char const *str);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(const char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

#endif