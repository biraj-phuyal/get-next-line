/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:17:40 by biphuyal          #+#    #+#             */
/*   Updated: 2025/07/15 17:20:44 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	buff[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	while (1)
	{
		if (buff[0] == '\0')
		{
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read == 0)
				return (str);
			if (bytes_read == -1)
				return (free(str), NULL);
			buff[bytes_read] = '\0';
		}
		move_buffer(buff, &str);
		if (str && str[ft_strlen(str) - 1] == '\n')
			return (str);
	}
}
/* 
int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return 1;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
} */