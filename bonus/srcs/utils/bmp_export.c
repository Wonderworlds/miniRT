/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:46:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/13 22:55:31 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx_data.h"
#include "libft.h"

#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define FILENAME_BASE "screenshot_0000.bmp"

static void	gen_bmp_fheader(int filesize, unsigned char *dest);
static void	gen_bmp_iheader(int height, int width, unsigned char *dest);
static int	create_filename(char *file, size_t size);

void	gen_bmp(const unsigned char	*img, int height, int width)
{
	int				fd;
	int				line;
	char			filename_bmp[20];
	unsigned char	file_header[FILE_HEADER_SIZE];
	unsigned char	info_header[INFO_HEADER_SIZE];

	if (create_filename(&filename_bmp[0], 20))
	{
		ft_fprintf(2, "Error\nScreenshot ==> fail, \
		filename not available\n", filename_bmp);
		return ;
	}
	fd = open(filename_bmp, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	line = FILE_HEADER_SIZE + INFO_HEADER_SIZE
		+ (BYTES_PER_PIXEL * height * width);
	gen_bmp_fheader(line, &file_header[0]);
	gen_bmp_iheader(height, width, &info_header[0]);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	line = height;
	while (--line + 1)
		write(fd, img + width * line * 4, width * 4);
	ft_printf("\nScreenshot ==> %s\n", filename_bmp);
	close(fd);
	return ;
}

int	create_filename(char *file, size_t size)
{
	size_t	i;

	ft_memcpy(file, FILENAME_BASE, size);
	file[size] = 0;
	i = size - 6;
	while (!access(file, F_OK))
	{
		while (file[i] == '9')
			file[i--] = '0';
		if (i < size - 9)
			return (1);
		file[i] = file[i] + 1;
		if (i < size - 6)
			i = size - 6;
	}
	return (0);
}

static void	gen_bmp_fheader(int filesize, unsigned char *dest)
{
	ft_memcpy(dest, (char []){'B', 'M',
		0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0}, 14);
	dest[2] = (unsigned char)(filesize);
	dest[3] = (unsigned char)(filesize >> 8);
	dest[4] = (unsigned char)(filesize >> 16);
	dest[5] = (unsigned char)(filesize >> 24);
}

static void	gen_bmp_iheader(int height, int width, unsigned char *dest)
{
	ft_memcpy(dest, (char []){40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0}, 40);
	dest[4] = (unsigned char)(width);
	dest[5] = (unsigned char)(width >> 8);
	dest[6] = (unsigned char)(width >> 16);
	dest[7] = (unsigned char)(width >> 24);
	dest[8] = (unsigned char)(height);
	dest[9] = (unsigned char)(height >> 8);
	dest[10] = (unsigned char)(height >> 16);
	dest[11] = (unsigned char)(height >> 24);
}
