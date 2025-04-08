/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf44_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:31:53 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 13:32:02 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

t_FTMFLOAT4X4	ftmf44_set_zero(void)
{
	t_FTMFLOAT4X4	matrix;
	int				idx1;
	int				idx2;

	idx1 = -1;
	while (++idx1 < 4)
	{
		idx2 = -1;
		while (++idx2 < 4)
		{
			matrix.data[idx1][idx2] = 0.0;
		}
	}
	matrix.data[3][3] = 1.0;
	return (matrix);
}

t_FTMFLOAT4X4	ftmf44_set_id(void)
{
	t_FTMFLOAT4X4	matrix;
	int				idx;

	matrix = ftmf44_set_zero();
	idx = -1;
	while (++idx < 3)
	{
		matrix.data[idx][idx] = 1.0;
	}
	return (matrix);
}

t_FTMFLOAT4X4	ftmf44_set_angle_x(float rad)
{
	t_FTMFLOAT4X4	matrix;

	matrix = ftmf44_set_id();
	matrix.data[1][1] = cosf(rad);
	matrix.data[2][2] = cosf(rad);
	matrix.data[1][2] = sinf(rad);
	matrix.data[2][1] = -sinf(rad);
	return (matrix);
}

t_FTMFLOAT4X4	ftmf44_set_angle_y(float rad)
{
	t_FTMFLOAT4X4	matrix;

	matrix = ftmf44_set_id();
	matrix.data[0][0] = cosf(rad);
	matrix.data[2][2] = cosf(rad);
	matrix.data[0][2] = -sinf(rad);
	matrix.data[2][0] = sinf(rad);
	return (matrix);
}

t_FTMFLOAT4X4	ftmf44_set_angle_z(float rad)
{
	t_FTMFLOAT4X4	matrix;

	matrix = ftmf44_set_id();
	matrix.data[0][0] = cosf(rad);
	matrix.data[1][1] = cosf(rad);
	matrix.data[0][1] = sinf(rad);
	matrix.data[1][0] = -sinf(rad);
	return (matrix);
}
