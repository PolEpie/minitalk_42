/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:27:14 by pepie             #+#    #+#             */
/*   Updated: 2024/04/12 23:27:14 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

static void sig_handler(int signum) {

  if(signum==SIGUSR1) {
    ft_printf("Reçu signal SIGUSR1\n");
  }
  else {
    if(signum==SIGUSR2) {
    ft_printf("Reçu signal SIGUSR2\n");
    }
    else {
      char *msg="Reçu signal inattendu\n";
      write(STDERR_FILENO,msg,ft_strlen(msg));
      _exit(EXIT_FAILURE);
    }
  }
}

int	main(void)
{
	if(signal(SIGUSR1,sig_handler)==SIG_ERR) {
		ft_printf("0");
		exit(EXIT_FAILURE);
	}
	if(signal(SIGUSR2,sig_handler)==SIG_ERR) {
		ft_printf("[ERROR] signal2");
		exit(EXIT_FAILURE);
	}
	ft_printf("[STARTED] PID : %d\n", getpid());
	while (1)
	{
		// Do something
	}
	return (0);
}