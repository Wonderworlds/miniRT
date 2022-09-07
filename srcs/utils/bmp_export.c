/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:46:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/07 22:24:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx_data.h"
#include "libft.h"

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

static void	createBitmapFileHeader (int filesize, unsigned char *dest);
static void	createBitmapInfoHeader(int height, int width, unsigned char *dest);

int	generateBitmapImage(const unsigned char* img, int height, int width,
		const char* filename)
{
	int				fd;
	int				line;
	char			*filename_bmp;
	unsigned char	fileHeader[FILE_HEADER_SIZE];
	unsigned char	infoHeader[INFO_HEADER_SIZE];

	line = ft_strlen(filename);
	filename_bmp = ft_calloc(sizeof(char), line + 5);
	if (!filename_bmp)
		return (1);
	ft_memcpy(filename_bmp, filename, line + 1);
	ft_strlcat(filename_bmp, ".bmp", line + 5);
	fd = open(filename_bmp, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	line = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (BYTES_PER_PIXEL * height * width);
	createBitmapFileHeader(line, &fileHeader[0]);
	createBitmapInfoHeader(height, width, &infoHeader[0]);
	write(fd, fileHeader, FILE_HEADER_SIZE);
	write(fd, infoHeader, INFO_HEADER_SIZE);
	line = height;
	while(--line + 1)
		write(fd, img + width * line * 4, width * 4);
	ft_printf("\nScreenshot ==> %s\n", filename_bmp);
	free(filename_bmp);
	close(fd);
	return (0);
}

static void	createBitmapFileHeader (int filesize, unsigned char *dest)
{
	ft_memcpy(dest, (char[]){'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0}, 14);
	dest[2] = (unsigned char)(filesize);
	dest[3] = (unsigned char)(filesize >> 8);
	dest[4] = (unsigned char)(filesize >> 16);
	dest[5] = (unsigned char)(filesize >> 24);
}

static void	createBitmapInfoHeader (int height, int width, unsigned char *dest)
{
	ft_memcpy(dest, (char[]){40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 32,0,
				0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, 40);
	dest[4] = (unsigned char)(width);
	dest[5] = (unsigned char)(width >> 8);
	dest[6] = (unsigned char)(width >> 16);
	dest[7] = (unsigned char)(width >> 24);
	dest[8] = (unsigned char)(height);
	dest[9] = (unsigned char)(height >> 8);
	dest[10] = (unsigned char)(height >> 16);
	dest[11] = (unsigned char)(height >> 24);
}