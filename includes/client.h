/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:41 by pepie             #+#    #+#             */
/*   Updated: 2024/05/07 10:39:37 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <common.h>

typedef struct s_client
{
	char	*msg;
	int		msg_len;
	int		index;
	int		i;
	char	c;
	int		pid;
	bool	is_finish;
}	t_client;

#endif
