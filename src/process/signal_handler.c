/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:38:55 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 16:17:38 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	handle_ignored_signal(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// to handle SIGINT (ctrl + c)
// TIOCSTI is ioctl command that simulates terminal input
// by inserting characters into the terminal's input buffer
// as if they were typed by the user.
void	handle_sigint(int signum)
{
	t_mini	*mini;

	mini = get_mini();
	if (signum != SIGINT) // only handle (ctrl + c)
		return ;
	mini->exit_code = EXIT_FAILURE; // with ctrl+c, process exit with failure
	if (mini->h_flag == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();       // prepare for a new line
		rl_replace_line("", 0); // clear current input line
		rl_redisplay();         // redisplay the prompt
	}
	else // handling for heredoc mode
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// simulate a new line to break the heredoc
		ft_putstr_fd("\033[1A", STDOUT_FILENO);
		// move the cursor up one line (prevent leaving an empty line on terminal)
		mini->h_flag = 0;
	}
}

void	setup_signal_handler(void)
{
	disable_ctrl_echo();
	// to check if it works correctly (comment in/out)
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// not to print ^C when ctrl+c is pressed
void	disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// to print ^C when ctrl+c is pressed
void	enable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
