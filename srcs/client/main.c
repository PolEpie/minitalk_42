/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:11 by pepie             #+#    #+#             */
/*   Updated: 2024/04/15 01:09:00 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void    send_bytes(char n, int pid)
{
    int     i;
    int     n_positif;
    bool    is_zero;

    i = 7;
    n_positif = n + 128;
    ft_printf("Num: %d\n", n_positif);
    while (i >= 0)
    {
        is_zero = (n_positif & (1 << i)) == 0;
        if (is_zero)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        i--;
    }
    ft_printf("\n");
}

int	main(int argc, char **argv)
{
	int pid;
    int i;

    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
        return (1);
    }
    i = 0;
    pid = ft_atoi(argv[1]);
    while (argv[2][i])
    {
        send_bytes(argv[2][i], pid);
        i++;
    }
    send_bytes('\n', pid);
    ft_printf("Send message to: %d %s\n", pid, argv[2]);

	return (0);
}