/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf44_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:56:26 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 16:17:27 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_FTMFLOAT4X4	*ftmf44_scale(
					t_FTMFLOAT4 *prow_vec,
					t_FTMFLOAT4X4 *ptarget
					)
{
	int		r;
	int		c;

	r = -1;
	while (++r < 3)
	{
		c = -1;
		while (++c < 3)
		{
			ptarget->data[r][c] *= prow_vec->data[r];
		}
	}
	return (ptarget);
}

t_FTMFLOAT4X4	*ftmf44_translate(t_FTMFLOAT4X4 *ptarget, t_FTMFLOAT4 *prow_vec)
{
	ptarget->data[3][0] += prow_vec->data[0];
	ptarget->data[3][1] += prow_vec->data[1];
	ptarget->data[3][2] += prow_vec->data[2];
	return (ptarget);
}

t_FTMFLOAT4	ftmf44_affine(
					t_FTMFLOAT4 *prow_vector,
					t_FTMFLOAT4X4 *pmatrix
					)
{
	t_FTMFLOAT4	result;
	int			c;
	int			r;

	c = -1;
	while (++c < 4)
	{
		r = -1;
		result.data[c] = 0;
		while (++r < 4)
		{
			result.data[c] += prow_vector->data[r] * pmatrix->data[r][c];
		}
	}
	return (result);
}
