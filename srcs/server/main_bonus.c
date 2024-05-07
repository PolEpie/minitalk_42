/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:14 by pepie             #+#    #+#             */
/*   Updated: 2024/05/07 10:48:19 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

t_server	g_srv;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_srv.byte_received++;
	else if (signum == SIGUSR2)
	{
		g_srv.total += 1 << (7 - g_srv.byte_received);
		g_srv.byte_received++;
	}
	else
	{
		write(STDERR_FILENO, "Reçu signal inattendu\n", 22);
		_exit(EXIT_FAILURE);
	}
	if (g_srv.byte_received == 8)
	{
		g_srv.byte_received = 0;
		ft_printf("%c", g_srv.total);
		if (g_srv.total == 0)
			(ft_printf(" | (%d)\n", info->si_pid), kill(info->si_pid, SIGUSR2));
		else
			kill(info->si_pid, SIGUSR1);
		g_srv.total = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_srv.byte_received = 0;
	g_srv.total = 0;
	ft_printf("[STARTED] PID : %d\n", getpid());
	while (1)
		pause();
	return (0);
}
