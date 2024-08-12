/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:38:55 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 17:57:59 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Handles ignored signals, specifically SIGINT
 * - If the signal is SIGINT (Ctrl+C), prints a newline character
 * - Helps to ensure that the prompte is displayed on a new line
 */
void	handle_ignored_signal(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

/**
 * @brief Handles SIGING (Ctrl+C) signal
 * - If the signal is SIGINT, sets the exit code to EXIT_FAILURE
 * - For normal mode, clears current input and redisplay the prompt
 * - For heredoc, simulates a newline to break out of heredoc input
 * - The cursor then moved up to prevent leaving an empty line
 * - TIOCCSTI is an ioctl command that simulates terminal input
 */
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

/**
 * @brief Configures signal handling
 * - Disables printing of ^C when Ctrl+C is pressed
 * - Sets up handler for SIGINT to handle Ctrl+C
 * - Ignores SIGQUIT (Ctrl+\) to prevent shell from quittig
 */
void	setup_signal_handler(void)
{
	disable_ctrl_echo();
	// to check if it works correctly (comment in/out)
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Disables printing of ^C when Ctrl+C is pressed
 */
void	disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief Enables printing of ^C when Ctrl+C is pressed
 */
void	enable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
