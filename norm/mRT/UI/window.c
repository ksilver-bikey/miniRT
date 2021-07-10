/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:31:55 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:31:56 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void		res_checking(void)
{
	int	act_x;
	int	act_y;

	if (fg_win()->x < 1 || fg_win()->y < 1)
		mrt_input_error(4, NULL);
	if (fg_win()->save != 's')
	{
		mlx_get_screen_size(fg_win()->prcs, &act_x, &act_y);
		if (fg_win()->x > act_x)
			fg_win()->x = act_x;
		if (fg_win()->y > act_y)
			fg_win()->y = act_y;
	}
}

int			win_close(void)
{
	free_all();
	exit(0);
	return (0);
}

int			some_button(int id)
{
	if (id == 53)
		win_close();
	if (id == 124 || id == 49)
	{
		if (fg_win()->act_cam->next == NULL)
			mrt_painting(fg_win()->camera);
		else
			mrt_painting(fg_win()->act_cam->next);
	}
	if (id == 123)
		if (fg_win()->act_cam->prev != NULL)
			mrt_painting(fg_win()->act_cam->prev);
	return (0);
}

void		looping(void)
{
	mlx_hook(fg_win()->win, 2, 1L << 0, some_button, 0);
	mlx_hook(fg_win()->win, 17, 1L << 17, win_close, 0);
	mlx_loop(fg_win()->prcs);
}

void		scene_activate(void)
{
	t_window	*window;

	window = fg_win();
	ft_bzero(window, sizeof(t_window));
}
