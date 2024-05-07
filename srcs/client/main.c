/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:11 by pepie             #+#    #+#             */
/*   Updated: 2024/05/07 11:02:20 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

t_client	g_cli;

void	send_finito(void)
{
	int	i;

	if (g_cli.is_finish)
		return ;
	g_cli.is_finish = true;
	i = 0;
	free(g_cli.msg);
	while (i <= 8)
	{
		kill(g_cli.pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

void	send_bytes(void)
{
	bool	is_zero;

	if (g_cli.i == -1)
	{
		if (g_cli.index == g_cli.msg_len)
			return (send_finito());
		g_cli.c = g_cli.msg[g_cli.index];
		g_cli.i = 7;
		g_cli.index++;
	}
	is_zero = (g_cli.c & (1 << g_cli.i)) == 0;
	if (is_zero)
		kill(g_cli.pid, SIGUSR1);
	else
		kill(g_cli.pid, SIGUSR2);
	g_cli.i = g_cli.i - 1;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
	{
		send_bytes();
	}
	else if (signum == SIGUSR2)
	{
		ft_printf("[CLIENT]\t->\t[SERVER] Message succesfully sent!\n");
		exit(0);
	}
	else
		(write(STDERR_FILENO, "Reçu signal inattendu\n", 21),
			exit(EXIT_FAILURE));
}

void	init_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;

	init_sigaction();
	if (argc != 3 || ft_atoi(argv[1]) == 0)
	{
		ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
		return (1);
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	g_cli.pid = pid;
	g_cli.index = 0;
	g_cli.msg = ft_strdup(argv[2]);
	g_cli.msg_len = ft_strlen(argv[2]);
	g_cli.is_finish = false;
	g_cli.c = 0;
	g_cli.i = -1;
	ft_printf("[CLIENT]\t->\t[SERVER] Sending message to: %d\n", pid);
	send_bytes();
	while (1)
	{
		pause();
	}
	return (0);
}
