/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:32:07 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:32:09 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_window	*fg_win(void)
{
	static t_window window;

	return (&window);
}

void		mrt_open_file(int argc, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		mrt_input_error(3, argv[1]);
	scene_activate();
	fg_win()->prcs = mlx_init();
	if (argc > 2)
	{
		if ((ft_strncmp(argv[2], "--save", 6) == 0) && argc == 3)
			fg_win()->save = 's';
		else
			mrt_input_error(2, NULL);
	}
	fg_win()->name = argv[1];
	while ((gnl = get_next_line(fd, &line)) > -1)
	{
		mrt_parcer(line);
		if (gnl == 0)
			break ;
	}
	close(fd);
}

void		mrt_painting(t_obj_cam *cam)
{
	int cnt_x;
	int cnt_y;
	int cnt_field;

	cnt_x = 0;
	cnt_y = 0;
	cnt_field = -1;
	fg_win()->act_cam = cam;
	while (cnt_y < fg_win()->y - 1)
	{
		cnt_x = 0;
		while (cnt_x < fg_win()->x)
		{
			mlx_pixel_put(fg_win()->prcs, fg_win()->win, cnt_x, cnt_y, \
			cam->field[++cnt_field]);
			cnt_x++;
		}
		cnt_y++;
	}
}

void		scene_clear(void)
{
	t_mro	*f_obj;
	t_mro	*b_obj;
	t_light	*f_light;
	t_light	*b_light;

	f_obj = fg_win()->objects;
	while (f_obj != NULL)
	{
		b_obj = f_obj;
		f_obj = f_obj->next;
		free_gc(b_obj);
	}
	f_light = fg_win()->lights;
	while (f_light != NULL)
	{
		b_light = f_light;
		f_light = f_light->next;
		free_gc(b_light);
	}
}

int			main(int argc, char **argv)
{
	first_input_check(argc, argv);
	mrt_open_file(argc, argv);
	mrt_obj_cleaner();
	walk_through_the_field(fg_win()->camera);
	fg_win()->win = mlx_new_window(fg_win()->prcs, fg_win()->x,\
												fg_win()->y, fg_win()->name);
	scene_clear();
	if (fg_win()->save == 's')
		bmp_rev();
	mrt_painting(fg_win()->camera);
	looping();
	free_all();
	return (0);
}
