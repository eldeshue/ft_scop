/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_voperate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:00:37 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 13:57:13 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

t_FTMFLOAT4	ftmf4_vadd(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2)
{
	t_FTMFLOAT4	result;

	result.data[0] = v1.data[0] + v2.data[0];
	result.data[1] = v1.data[1] + v2.data[1];
	result.data[2] = v1.data[2] + v2.data[2];
	result.data[3] = v1.data[3];
	return (result);
}

t_FTMFLOAT4	ftmf4_vsub(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2)
{
	t_FTMFLOAT4	result;

	result.data[0] = v1.data[0] - v2.data[0];
	result.data[1] = v1.data[1] - v2.data[1];
	result.data[2] = v1.data[2] - v2.data[2];
	result.data[3] = v1.data[3];
	return (result);
}

float	ftmf4_vsize(const t_FTMFLOAT4 *pvec)
{
	return (sqrt(powf(pvec->data[0], 2.0)
			+ powf(pvec->data[1], 2.0) + powf(pvec->data[2], 2.0)));
}
