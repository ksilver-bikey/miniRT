/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:00:10 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:00:12 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	bmp_header(int fd)
{
	int				size;
	unsigned char	header[54];
	int				cnt;
	unsigned char	*temp;

	cnt = 54;
	while (--cnt > -1)
		header[cnt] = '\0';
	header[0] = 66u;
	header[1] = 77u;
	size = (fg_win()->x * fg_win()->y * 4) + 54;
	temp = (unsigned char *)&size;
	while (++cnt < 4)
		header[2 + cnt] = temp[cnt];
	header[10] = 54u;
	header[14] = 40u;
	size = fg_win()->x;
	while (--cnt > -1)
		header[18 + cnt] = temp[cnt];
	size = fg_win()->y;
	while (++cnt < 4)
		header[22 + cnt] = temp[cnt];
	header[26] = 1u;
	header[28] = 32u;
	write(fd, header, 54);
}

char		*mrt_make_me_name(int num)
{
	char	*number;
	char	*name;
	int		cnt;
	int		slash;

	cnt = -1;
	slash = 0;
	name = fg_win()->name;
	while (name[++cnt] != '\0')
		if (name[cnt] == '/')
			slash = cnt;
	name = ft_strdup(&fg_win()->name[slash + 1]);
	name[ft_strlen(name) - 3] = '\0';
	if (num > 0)
	{
		number = ft_itoa(num);
		name = ft_strins_fr(number, name, 0, 'b');
	}
	name = ft_strins_fr(".bmp", name, 0, 'a');
	return (name);
}

static void	creat_bmp(t_obj_cam *cam, char *name, int num)
{
	int				fd;
	int				size;
	unsigned char	*field;
	int				line;

	name = mrt_make_me_name(num);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	free_gc(name);
	if (fd < 1)
		mrt_input_error(16, NULL);
	bmp_header(fd);
	field = (unsigned char*)cam->field;
	line = 0;
	while (++line < (fg_win()->y - 1) * 4)
	{
		size = fg_win()->x * (fg_win()->y - line) * 4;
		write(fd, &field[size], fg_win()->x * 4);
	}
	close(fd);
}

void		bmp_rev(void)
{
	t_obj_cam	*cam;
	int			num;

	cam = fg_win()->camera;
	num = 0;
	while (cam != NULL)
	{
		creat_bmp(cam, NULL, num);
		cam = cam->next;
		num++;
	}
	free_all();
	exit(0);
}
