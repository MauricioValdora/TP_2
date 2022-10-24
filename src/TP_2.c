/*
 ============================================================================
 Name        : TP_2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

#define TAM 5
#define TAM_CON 5

typedef struct {
	int id;
	char nombre[50];
	char region[50];
	int anioCreacion;

} eConfederacion;

typedef struct {
	int id;
	char nombre[50];
	char posicion[50];
	short numeroCamiseta;
	int idConfederacion;
	float salario;
	short aniosContrato;
	short isEmpty;
} eJugador;

int menu();
int inicializarJugador(eJugador lista[], int tam);
int buscarLibre(eJugador lista[], int tam);
int altaPersona(eJugador lista[], int tam, int *pId);
void mostrarJugador(eJugador p, eConfederacion confederaciones[], int tam);
int mostrarJugadores(eJugador lista[], int tam,
		eConfederacion confederaciones[], int tam_con);
int buscarJugador(eJugador lista[], int tam, int id);
int bajaJugador(eJugador lista[], int tam, eConfederacion confederaciones[],
		int tam_con);
int menuModificacion();
int modificarJugador(eJugador lista[], int tam,
		eConfederacion confederaciones[], int tam_con);
int menuIdConfederacion();
int cargarConfederacion(eConfederacion confederaciones[], int tam,
		int idConfederacion, char confederacion[]);

int main(void) {
	setbuf(stdout, NULL);

	char seguir = 's';
	int nextId = 20000;

	eJugador lista[TAM] = {
			{ 20000, "mauricio", "delantero", 10, 1, 30000, 5, 0 }, { 20001,
					"mauricio", "delantero", 10, 1, 30000, 5, 0 }, { 20002,
					"mauricio", "delantero", 10, 1, 30000, 5, 0 }, { 20003,
					"mauricio", "delantero", 10, 1, 30000, 5, 0 }, { 20004,
					"mauricio", "delantero", 10, 1, 30000, 5, 0 }

	};
	eConfederacion confederaciones[TAM_CON] = { { 1, "UEFA", "europa", 1991 }, {
			2, "CONCACAF", "alemania", 1990 }, { 3, "OFC", "oriente", 1980 }, {
			4, "CAF", "africa", 1994 }, { 5, "CONMEBOL", "america", 1997 }

	};
	//inicializarJugador(lista,TAM);
	do {
		switch (menu()) {
		case 1:
			if (!altaPersona(lista, TAM, &nextId)) {
				printf("no se pudo realizar el alta\n");
			} else {
				printf("alta exitosa!!\n");
			}
			break;
		case 2:
			bajaJugador(lista, TAM, confederaciones, TAM_CON);
			break;
		case 3:
			if (!modificarJugador(lista, TAM, confederaciones, TAM_CON)) {
				printf("no se pudo realizar la modificacion\n");
			} else {
				printf("modificacion exitosa\n");
			}
			break;
		case 4:
			mostrarJugadores(lista, TAM, confederaciones, TAM_CON);
			break;
		case 5:
			printf("a seleccionado la opcion salir\n");
			seguir = 'n';
			break;
		default:
			printf("opcion invalida!!!\n");
		}
		fflush(stdin);
	} while (seguir == 's');
	return EXIT_SUCCESS;
}

int menu() {

	int opcion;

	printf("   ******FIFA******\n\n");
	printf(" 1-Alta personas.\n");
	printf(" 2-Baja personas.\n");
	printf(" 3-Modificar jugador.\n");
	printf(" 4-Informes.\n");
	printf(" 5-Salir.\n");
	scanf("%d", &opcion);

	return opcion;

}

int inicializarJugador(eJugador lista[], int tam) {

	int todoOk = 0;

	if (lista != NULL && tam > 0) {
		for (int i = 0; i < tam; i++) {
			lista[i].isEmpty = 1;
			todoOk = 1;
		}
	}

	return todoOk;
}

int buscarLibre(eJugador lista[], int tam) {

	int indice = -1;
	for (int i = 0; i < tam; i++) {
		if (lista[i].isEmpty) {
			indice = i;
			break;
		}
	}
	return indice;
}
int altaPersona(eJugador lista[], int tam, int *pId) {

	int todoOk = 0;
	int indice;
	int camiseta;
	int salario;
	int aniosDeContrato;
	char auxCadena[50];
	eJugador auxJugador;
	if (lista != NULL && tam > 0) {

		printf("*** Alta persona***\n\n");

		indice = buscarLibre(lista, tam);

		if (indice == -1) {
			printf("no hay lugar\n");
		} else {

			auxJugador.id = *pId;
			(*pId)++;

			utn_getNombre(auxCadena, 50, "ingrese nombre \n",
					"error ingrese nombre nuevamente \n", 3);
			strcpy(auxJugador.nombre, auxCadena);

			utn_getNombre(auxCadena, 50, "ingrese posicion \n",
					"error ingrese posicion nuevamente \n", 3);
			strcpy(auxJugador.posicion, auxCadena);
			strlwr(auxJugador.posicion);
			auxJugador.posicion[0] = toupper(auxJugador.posicion[0]);
			while (strcmp(auxJugador.posicion, "Delantero") != 0
					&& strcmp(auxJugador.posicion, "Mediocampista") != 0
					&& strcmp(auxJugador.posicion, "Defensor") != 0
					&& strcmp(auxJugador.posicion, "Arquero") != 0) {

				utn_getNombre(auxCadena, 50, "ingrese posicion \n",
						"error ingrese posicion nuevamente \n", 3);
				strcpy(auxJugador.posicion, auxCadena);
				strlwr(auxJugador.posicion);
				auxJugador.posicion[0] = toupper(auxJugador.posicion[0]);
			}

			utn_getNumero(&camiseta, "ingrese numero de camiseta \n",
					"error \n", 1, 100, 3);
			auxJugador.numeroCamiseta = camiseta;

			auxJugador.idConfederacion = menuIdConfederacion();

			utn_getNumero(&salario, "ingrese salario \n", "error \n", 1, 500000,
					3);
			auxJugador.salario = (float) salario;

			utn_getNumero(&aniosDeContrato, "ingrese años de contrato\n",
					"error\n", 1, 20, 3);
			auxJugador.aniosContrato = aniosDeContrato;

			auxJugador.isEmpty = 0;

			lista[indice] = auxJugador;

			todoOk = 1;
		}
	}

	return todoOk;
}

int menuIdConfederacion() {
	int opcion;

	printf("   ******ID de confederaciones******\n\n");
	printf("ingrese el id de confederacion\n");
	printf("*** ID   confederacion***\n");
	printf(" 1   UEFA.\n");
	printf(" 2   CONCACAF.\n");
	printf(" 3   OFC.\n");
	printf(" 4   CAF.\n");
	printf(" 5   CONMEBOL.\n");
	printf(" 6   Salir.\n");
	utn_getNumero(&opcion, "ingrese numero de ID \n", "error ", 1, 6, 3);
	return opcion;
}

void mostrarJugador(eJugador p, eConfederacion confederaciones[], int tam) {

	char confederacion[20];
	cargarConfederacion(confederaciones, tam, p.idConfederacion, confederacion);

	printf("%d|", p.id);
	printf("%-10s|", p.nombre);
	printf("%10s |", p.posicion);
	printf(" %-10d| ", p.numeroCamiseta);
	printf(" %-10s |", confederacion);
	printf("%10.2f| ", p.salario);
	printf(" %-10d  |\n\n", p.aniosContrato);
}
int mostrarJugadores(eJugador lista[], int tam,
		eConfederacion confederaciones[], int tam_con) {

	int flag = 1;

	int todoOk = 0;

	if (lista != NULL && tam > 0) {
		printf(
				"----------------------------------------------------------------------------------------------\n");
		printf("   *** Lista de jugadores ***\n");
		printf(
				"----------------------------------------------------------------------------------------------\n");
		printf(
				" id  |  nombre  |  posicion | camiseta  |  federacion |  sueldo  |  años de contrato | \n");
		printf(
				"--------------------------------------------------------------------------------------------\n\n");
		for (int i = 0; i < tam; i++) {

			if (!lista[i].isEmpty) {
				mostrarJugador(lista[i], confederaciones, tam_con);
				flag = 0;
			}
		}
		if (flag) {
			printf("no hay jugadores para mostrar \n\n");
		}
		todoOk = 1;
	}

	return todoOk;
}

int buscarJugador(eJugador lista[], int tam, int id) {

	int indice = -1;
	for (int i = 0; i < tam; i++) {
		if (!lista[i].isEmpty && lista[i].id == id) {
			indice = i;
			break;
		}
	}
	return indice;

}
int bajaJugador(eJugador lista[], int tam, eConfederacion confederaciones[],
		int tam_con) {

	int todoOk = 0;
	int indice;
	int id;
	char confirma;

	if (lista != NULL && tam > 0 && lista->isEmpty == 0) {

		printf("   ***Baja jugador***\n\n");
		if (mostrarJugadores(lista, tam, confederaciones, tam_con)) {
			fflush(stdin);
			utn_getNumero(&id, "ingrese el id que quiere eliminar \n",
					"error \n", 20000, 23000, 3);
			indice = buscarJugador(lista, tam, id);
			if (indice == -1) {
				printf("El ID %d no esta registrado en el sistema \n", id);
			} else {
				fflush(stdin);
				mostrarJugador(lista[indice], confederaciones, tam_con);
				printf("confirma baja ");
				fflush(stdin);
				scanf("%c", &confirma);
				if (confirma == 's') {
					lista[indice].isEmpty = 1;
					todoOk = 1;
				} else {
					printf("Baja cancelada por el usuario\n");
				}
			}
		}

	} else {
		printf("Por favor primero realice la carga de un jugador");
	}

	return todoOk;
}

int menuModificacion() {

	int opcion;

	printf(" 1-nombre \n");
	printf(" 2-posicion\n");
	printf(" 3-numero de camiseta\n");
	printf(" 4-confederacion \n");
	printf(" 5-salario\n");
	printf(" 6-años de contrato\n");
	printf(" 7-Salir\n");

	scanf("%d", &opcion);

	return opcion;

}
int modificarJugador(eJugador lista[], int tam,
		eConfederacion confederaciones[], int tam_con) {

	int todoOk = 0;
	int indice;
	int id;
	char confirma;
	char auxNombre[20];
	char auxPosicion[20];
	short auxCamiseta;
	int auxConfederacion;
	float auxSalario;
	short auxContrato;

	if (lista != NULL && tam > 0) {

		printf("   ***Modificar personaaaaaaaaaa***\n\n");
		mostrarJugadores(lista, tam, confederaciones, tam_con);
		fflush(stdin);
		utn_getNumero(&id, "ingrese el id del jugador que quiere modificar \n",
				"Error ingrese un id existente \n", 20000, 23000, 3);
		indice = buscarJugador(lista, tam, id);
		if (indice == -1) {
			printf("El id %d no esta registrado en el sistema \n", id);
		} else {
			//mostrarJugador(lista[indice], confederaciones, tam_con);
			printf("confirma modificacion?:");
			fflush(stdin);
			scanf("%c", &confirma);
			if (confirma == 's') {
				switch (menuModificacion()) {
				case 1:
					printf("ingrese nuevo nombre");
					fflush(stdin);
					gets(auxNombre);
					strcpy(lista[indice].nombre, auxNombre);
					break;
				case 2:
					printf("ingrese nueva posicion");
					fflush(stdin);
					gets(auxPosicion);
					strcpy(lista[indice].posicion, auxPosicion);
					break;
				case 3:
					printf("ingrese nuevo numero de camiseta");
					scanf("%hd", &auxCamiseta);
					lista[indice].numeroCamiseta = auxCamiseta;
					break;
				case 4:
					printf("ingrese el ID de la nueva confederacion");
					scanf("%d", &auxConfederacion);
					lista[indice].idConfederacion = auxConfederacion;
					break;
				case 5:
					printf("ingrese el nuevo salario");
					scanf("%f", &auxSalario);
					lista[indice].salario = auxSalario;
					break;
				case 6:
					printf("ingrese los nuevos años de contrato");
					scanf("%hd", &auxContrato);
					lista[indice].aniosContrato = auxContrato;
					break;
				case 7:
					printf("quiere cancelar la modificacion?");
					fflush(stdin);
					scanf("%c", &confirma);
					if (confirma == 's') {
						printf("modificacion cancelada");
					}
					;
					break;
				default:
					printf("opcion invalida!!!");
				}
			} else if (confirma == 'n') {
				printf("modificacion cancelada");
			}

		}
		todoOk = 1;

	}

	return todoOk;

}

int cargarConfederacion(eConfederacion confederaciones[], int tam,
		int idConfederacion, char confederacion[]) {
	int todoOk = 0;
	if (confederaciones != NULL && tam > 0 && confederacion != NULL) {

		for (int i = 0; i < tam; i++) {
			if (confederaciones[i].id == idConfederacion) {

				strcpy(confederacion, confederaciones[i].nombre);
				break;
			}
		}

		todoOk = 1;
	}
	return todoOk;
}

