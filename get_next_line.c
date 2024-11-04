/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danperez <danperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:37:43 by danperez          #+#    #+#             */
/*   Updated: 2024/11/04 12:31:05 by danperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *restante;   // Almacenamiento temporal para la próxima línea
	size_t	BUFFER_SIZE;
	char buffer[BUFFER_SIZE + 1];
	int bytes_leidos;

	// Leer del archivo
	bytes_leidos = read(fd, buffer, BUFFER_SIZE);
	if (bytes_leidos <= 0) {
		return (NULL);  // Fin de archivo o error
	}
	buffer[bytes_leidos] = '\0';

	// En este punto, `buffer` contiene los datos leídos y debes agregarlos a `restante`.
	// Puedes usar `ft_strcat` o `ft_strjoin` según tu preferencia.

	return NULL;  // Para pruebas, estamos retornando NULL
}
