/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf44_operate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:22:27 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 16:06:42 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_FTMFLOAT4X4	ftmf44_add(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2)
{
	t_FTMFLOAT4X4	result;
	int				r;
	int				c;

	r = -1;
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
		{
			result.data[r][c] = pm1->data[r][c] + pm2->data[r][c];
		}
	}
	return (result);
}

t_FTMFLOAT4X4	ftmf44_sub(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2)
{
	t_FTMFLOAT4X4	result;
	int				r;
	int				c;

	r = -1;
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
		{
			result.data[r][c] = pm1->data[r][c] - pm2->data[r][c];
		}
	}
	return (result);
}

t_FTMFLOAT4X4	ftmf44_mult(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2)
{
	t_FTMFLOAT4X4	result;
	int				r1;
	int				c2;
	int				idx;

	r1 = -1;
	while (++r1 < 4)
	{
		c2 = -1;
		while (++c2 < 4)
		{
			result.data[r1][c2] = 0;
			idx = -1;
			while (++idx < 4)
				result.data[r1][c2] += pm1->data[r1][idx] * pm2->data[idx][c2];
		}
	}
	return (result);
}

void	ftmf44_transpose(t_FTMFLOAT4X4 *pm)
{
	int		row;
	int		col;
	float	temp;

	row = -1;
	while (++row < 4)
	{
		col = row;
		while (++col < 4)
		{
			temp = pm->data[row][col];
			pm->data[row][col] = pm->data[col][row];
			pm->data[col][row] = temp;
		}
	}
}
