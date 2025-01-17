#include <stdlib.h> // for mallic, free
#include <unistd.h> // for write
#include <stdarg.h> // for va_va_start, va_arg, va_copy, va_end
/* #include <stdio.h> // for real printf */

int	ft_printf_write(int c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_found_d(int d, int i)
{
	if (d == -2147483648)
	{
		write (1, "-2147483648", 11);
		i = i + 11;
	}
	else if (d < 0)
	{
		i = ft_printf_write('-', i);
		i = ft_found_d(-d, i);
	}
	else if (d >= 0 && d < 10)
		i = ft_printf_write(d + '0', i);
	else
	{
		i = ft_found_d(d / 10, i);
		i = ft_printf_write(d % 10 + '0', i);
	}
	return (i);
}

int	ft_found_s(char *s, int i)
{
	if (!s)
		i = ft_found_s("(null)", i);
	else
	{
		while (*s)
		{
			i = ft_printf_write(*s, i);
			s++;
		}
	}
	return (i);
}

int	ft_found_x(unsigned int x, int i)
{
	if (x == 0)
		i = ft_printf_write('0', i);
	else if (x >= 16)
	{
		i = ft_found_x(x / 16, i);
		i = ft_found_x(x % 16, i);
	}
	else
	{
		if (x <= 9)
			i = ft_printf_write(x + '0', i);
		else
			i = ft_printf_write(x + 'a' - 10, i);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = -1;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%')
		{
			j++;
			if (format[j] == 's')
				i = ft_found_s(va_arg(args, char *), i);
			if (format[j] == 'd')
				i = ft_found_d(va_arg(args, int), i);
			if (format[j] == 'x')
				i = ft_found_x(va_arg(args, unsigned int), i);
		}
		else
			i = ft_printf_write(format[j], i);
	}
	va_end(args);
	return (i);
}