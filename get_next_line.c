/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:19:31 by svanmeen          #+#    #+#             */
/*   Updated: 2022/11/21 15:39:36 by svanmeen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_get_nl(char *mem)
{
	int	i;

	i = 0;
	if (!mem)
		return (-1);
	while (mem[i] != '\n' && mem[i] != '\0')
		i++;
	if (mem[i] == '\n')
		return (i);
	if (mem[1] == '\n')
		return (0);
	else
		return (-1);
}

static char	*ft_mem_new(char *buf, char *mem)
{
	static char	*new_mem;

	if (!mem)
		return (ft_strdup(buf));
	new_mem = malloc((ft_strlen(buf) + ft_strlen(mem) + 1) * sizeof(char));
	if (!new_mem)
		return (NULL);
	ft_strncpy(new_mem, mem, ft_strlen(mem) + 1);
	ft_strlcat(new_mem, buf, ft_strlen(buf) + ft_strlen(mem) + 1);
	if (mem)
		free(mem);
	return (new_mem);
}

static char	*ft_save(char *mem)
{
	static char	*new_mem;

	if (!mem || (ft_strlen(mem) < 1))
		return (NULL);
	new_mem = malloc((ft_strlen(mem) + 1) * sizeof(char));
	ft_strncpy(new_mem, mem, ft_strlen(mem));
	return (new_mem);
}

static char	*ft_check(int b_r, char **mem)
{
	char	*temp;

	if (b_r < 0 || !*mem)
		return (NULL);
	temp = malloc((ft_strlen(*mem) + 1) * sizeof(char));
	ft_strncpy(temp, *mem, ft_strlen(*mem));
	*mem = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			b_r;
	int			i_before_nl;

	i_before_nl = -1;
	while (i_before_nl < 0)
	{
		b_r = read(fd, buf, BUFFER_SIZE);
		if (b_r <= 0)
			return (ft_check(b_r, &mem));
		buf[b_r] = '\0';
		mem = ft_mem_new(buf, mem);
		i_before_nl = ft_get_nl(mem);
	}
	temp = malloc((i_before_nl + 1) * sizeof(char));
	temp = ft_strncpy(temp, mem, i_before_nl);
	mem = ft_save(mem + i_before_nl + 1);
	if (temp[0] == '\n')
		return (NULL);
	return (temp);
}
