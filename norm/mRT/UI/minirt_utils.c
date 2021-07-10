/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:31:33 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:31:35 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	first_input_check(int argc, char **argv)
{
	int	cnt;

	if (argc < 2)
		mrt_input_error(1, NULL);
	cnt = ft_strlen(argv[1]);
	while (argv[1][--cnt] != '.' && cnt > 0)
		;
	if (argv[1][cnt + 1] != 'r' || argv[1][cnt + 2] != 't')
		mrt_input_error(0, NULL);
	cnt += 2;
	if (argv[1][cnt + 1] == '\0')
		return ;
	while (argv[1][++cnt] != '\0')
		if (argv[1][cnt] != ' ')
			mrt_input_error(0, NULL);
}

void	mrt_color_null(unsigned char *color)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}
