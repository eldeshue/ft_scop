/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_voperate2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:00:30 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 20:37:41 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

float	ftmf4_vdot(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2)
{
	return (v1.data[0] * v2.data[0]
		+ v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2]);
}

static float	det(float a, float b, float c, float d)
{
	return (a * d - b * c);
}

t_FTMFLOAT4	ftmf4_vcross(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2)
{
	t_FTMFLOAT4	result;

	result.data[0] = det(v1.data[1], v1.data[2], v2.data[1], v2.data[2]);
	result.data[1] = det(v1.data[2], v1.data[0], v2.data[2], v2.data[0]);
	result.data[2] = det(v1.data[0], v1.data[1], v2.data[0], v2.data[1]);
	result.data[3] = v1.data[3];
	return (result);
}

t_FTMFLOAT4	*ftmf4_vnormalize(t_FTMFLOAT4 *pvec)
{
	float	size;

	size = ftmf4_vsize(pvec);
	if (size != 0.0)
	{
		pvec->data[0] /= size;
		pvec->data[1] /= size;
		pvec->data[2] /= size;
	}
	return (pvec);
}
