/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:30:38 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:30:39 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		mrt_read_color_amb(char *data, unsigned char color[4])
{
	int				temp;
	char			**digits;
	int				cnt;
	char			err;

	cnt = -1;
	err = 1;
	color[3] = 0;
	digits = ft_split(data, ',');
	while (++cnt < 3 && digits[cnt] != NULL)
	{
		temp = -1;
		while (digits[cnt][++temp] != '\0')
			if (!ft_isdigit(digits[cnt][temp]) && digits[cnt][temp] != '\0')
				err = 0;
		temp = ft_atoi(digits[cnt]);
		(temp > 255 || temp < 0) ? (err = 0) : (1);
		color[cnt] = temp;
	}
	(cnt != 3 || digits[3] != NULL) ? (err = 0) : (1);
	temp = color[1];
	color[1] = color[2];
	color[2] = temp;
	mrt_reading_data_clean(digits);
	return (err);
}

void	mrt_ambient_light_read(char *line)
{
	char	**data;

	if (fg_win()->res_amb[1] != 0)
		mrt_input_error(7, line);
	fg_win()->res_amb[1]++;
	data = ft_split(line, ' ');
	if (data[1] == NULL || data[2] == NULL || data[3] != NULL)
		mrt_input_error(5, line);
	if (mrt_read_block(data[1]) != (int)ft_strlen(data[1]))
		mrt_input_error(5, line);
	fg_win()->a_light.intense = ft_atod(data[1]);
	if (fg_win()->a_light.intense < 0.0 || fg_win()->a_light.intense > 1.0)
		mrt_input_error(8, line);
	if (mrt_read_color_amb(data[2], fg_win()->a_light.color) == 0)
		mrt_input_error(11, line);
	fg_win()->amb_act = 'a';
	mrt_reading_data_clean(data);
}

void	mrt_no_res_cam_buff(char *line)
{
	t_cam_buf *cb;

	if (fg_win()->cam_buf == NULL)
	{
		fg_win()->cam_buf = (t_cam_buf *)malloc_gc(sizeof(t_cam_buf));
		cb = fg_win()->cam_buf;
	}
	else
	{
		cb = fg_win()->cam_buf;
		while (cb->next != NULL)
			cb = cb->next;
		cb->next = (t_cam_buf *)malloc_gc(sizeof(t_cam_buf));
		cb = cb->next;
	}
	cb->line = ft_strdup(line);
}

void	mrt_cam_buf_to_scene(void)
{
	t_cam_buf *forward;
	t_cam_buf *backward;

	forward = fg_win()->cam_buf;
	while (forward->next != NULL)
	{
		mrt_camera_read(forward->line);
		backward = forward;
		forward = forward->next;
		free_gc(backward->line);
		free_gc(backward);
	}
	mrt_camera_read(forward->line);
	free_gc(forward->line);
	free_gc(forward);
}

void	mrt_res_read(char *line)
{
	char		**data;

	if (fg_win()->res_amb[0] != 0)
		mrt_input_error(6, line);
	fg_win()->res_amb[0]++;
	data = ft_split(line, ' ');
	if (data[1] == NULL || data[2] == NULL)
		mrt_input_error(5, line);
	fg_win()->x = ft_atoi(data[1]);
	fg_win()->y = ft_atoi(data[2]);
	if (mrt_read_block(data[1]) == -1 || mrt_read_block(data[2]) == -1 ||\
		data[3] != NULL)
		mrt_input_error(5, line);
	if (fg_win()->cam_buf != NULL)
		mrt_cam_buf_to_scene();
	res_checking();
}
