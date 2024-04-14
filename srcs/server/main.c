/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:14 by pepie             #+#    #+#             */
/*   Updated: 2024/04/15 01:18:44 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

t_server    g_srv;

static void sig_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        g_srv.byte_received++;
        //ft_printf("0");
    }
    else if (signum == SIGUSR2)
    {
        g_srv.total += 1 << (7 - g_srv.byte_received);
        g_srv.byte_received++;
        //ft_printf("1");
    }
    else
    {
        char *msg = "Reçu signal inattendu\n";
        write(STDERR_FILENO, msg, ft_strlen(msg));
        _exit(EXIT_FAILURE);
    }
    if (g_srv.byte_received == 8)
    {
        g_srv.byte_received = 0;
        ft_printf("%c", g_srv.total - 128);
        g_srv.total = 0;
    }
}

int main(void)
{
    g_srv.byte_received = 0;
    g_srv.total = 0;
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        return (ft_printf("Error signal1\n"), 1);
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
    {
        ft_printf("[ERROR] signal2");
        exit(EXIT_FAILURE);
    }
    ft_printf("[STARTED] PID : %d\n", getpid());
    while (1)
    {
        pause();
    }
    return (0);
}