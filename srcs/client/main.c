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
    while (i >= 0)
    {
        is_zero = (n_positif & (1 << i)) == 0;
        if (is_zero)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(200);
        i--;
    }
}

void    sig_handler(int signum, siginfo_t *info, void *context)
{
	ft_printf("", context, info);
     if (signum == SIGUSR1)
    {
        ft_printf("[SERVER]\t->\t[CLIENT] Message successfully received!\n");
    }
    else
    {
        char *msg = "Reçu signal inattendu\n";
        write(STDERR_FILENO, msg, ft_strlen(msg));
        _exit(EXIT_FAILURE);
    }
}

int	main(int argc, char **argv)
{
	struct sigaction        sa;
	int pid;
    int i;

	sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
        return (1);
    }
    i = 0;
    pid = ft_atoi(argv[1]);
    ft_printf("[CLIENT]\t->\t[SERVER] Sending message to: %d\n", pid);
    while (argv[2][i])
    {
        send_bytes(argv[2][i], pid);
        i++;
    }
    ft_printf("[CLIENT]\t->\t[SERVER] Message sent!\n");
    send_bytes('\0', pid);
	return (0);
}