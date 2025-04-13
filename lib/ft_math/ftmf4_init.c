/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:59:58 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 20:33:45 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_FTMFLOAT4	ftmf4_set_vector(float x, float y, float z, float w)
{
	t_FTMFLOAT4	result;

	result.data[0] = x;
	result.data[1] = y;
	result.data[2] = z;
	result.data[3] = w;
	return (result);
}

int	ftmf4_is_vector(t_FTMFLOAT4 *pvec)
{
	return (pvec->data[3] == 0);
}

int	ftmf4_is_point(t_FTMFLOAT4 *pvec)
{
	return (pvec->data[3] == 1);
}

int	ftmf4_is_zero(t_FTMFLOAT4 *pvec)
{
	return ((pvec->data[0] == 0) && (pvec->data[1] == 0)
		&& (pvec->data[2] == 0));
}
