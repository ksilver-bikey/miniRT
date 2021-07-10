/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:32:39 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:32:40 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mrt_reading_data_clean(char **data)
{
	int	cnt;

	cnt = 0;
	while (data[cnt] != NULL)
		free_gc(data[cnt++]);
	free_gc(data);
}

void	mrt_norm_vec(double norm_vec[3], char *line)
{
	if (norm_vec[0] > 1.0 || norm_vec[1] > 1.0 || norm_vec[2] > 1.0 ||
		norm_vec[0] < -1.0 || norm_vec[1] < -1.0 || norm_vec[2] < -1.0)
		mrt_input_error(10, line);
}

int		write_color(int cnt, char **digits, char *data)
{
	int	temp;
	int	err;

	err = 1;
	temp = ft_atoi(digits[cnt]);
	if (temp > 255 || temp < 0)
		mrt_input_error(11, data);
	temp *= fg_win()->a_light.intense;
	temp += fg_win()->a_light.color[cnt] * fg_win()->a_light.intense;
	if (temp > 254)
		temp = 255;
	if (temp < 1)
		temp = 1;
	return (temp);
}

int		mrt_read_color(char *data, unsigned char color[4])
{
	int				temp;
	char			**digits;
	int				cnt;
	char			err;

	cnt = 0;
	err = 1;
	color[3] = 0;
	digits = ft_split(data, ',');
	while (cnt < 3 && digits[cnt] != NULL)
	{
		temp = -1;
		while (digits[cnt][++temp] != '\0')
			if (!ft_isdigit(digits[cnt][temp]) && digits[cnt][temp] != '\0')
				err = 0;
		color[cnt] = write_color(cnt, digits, data);
		cnt++;
	}
	if (digits[3] != NULL || cnt != 3)
		err = 0;
	mrt_reading_data_clean(digits);
	return (err);
}

int		mrt_read_coords(char *data, double crds[3])
{
	int		err;
	char	**digits;
	int		cnt;

	err = 1;
	cnt = -1;
	digits = ft_split(data, ',');
	while (++cnt < 3)
	{
		if (digits[cnt] == NULL)
			mrt_input_error(5, data);
		if (mrt_read_block(digits[cnt]) != (int)ft_strlen(digits[cnt]))
			err = 0;
		crds[cnt] = ft_atod(digits[cnt]);
	}
	mrt_reading_data_clean(digits);
	return (err);
}
