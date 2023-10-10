#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>

typedef {
	char nombre [60]
	char dni [9]
	int edad
} Jugador;

typedef {
	char Njugador1 [60]
	char Njugador2 [60]
	int Duracion
	int Fecha 
} Partida;

typedef {
	int idPartida [60]
	char Njugador1 [60]
	char Njugador2 [60]
	char Ganador [60] 
} Resultado;
		
int FechaPartidas(char nombre1[60])
{
	MYSQL *conn;
	int res;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[100];
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion(Necesario para las consultas)
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "JUEGO",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//consulta SQL
	sprintf(consulta, "SELECT Partida.Fecha FROM JUGADOR WHERE Partida.Njugador1 = '%s'",nombre1,"OR Partida.Njugador2 = '%d'",nombre1);
	//Comprobamos consulta
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	//Recogemos el resultado
	if (row == NULL)
		return -1;
	else
		res = strtok(row[0]," ");
	    return res;
		
	mysql_close (conn);
	exit(0);
}
int DamePartidasGanadas(char nombre[20])
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [100];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexin
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "JUEGO",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//consulta SQL
	strcpy (consulta, "SELECT COUNT(*) FROM JUEGO WHERE Resultado.Ganador = '");
	strcat (consulta, nombre);
	strcat (consulta, "'");
	
	//Para comprobar errores en la consulta
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	//Recogemos el resultado
	
	if (row == NULL || atoi(row[0]) == 0)
		return -1;
	else
		return atoi(row[0]);
	
	mysql_close (conn);
	exit(0);
	
}
int DuracionPartidas(char nombre1[60])
{
	MYSQL *conn;
	int err;
	int res;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[100];
	char nombre2[60];
		conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion(Necesario para las consultas)
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "JUEGO",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	strcpy(nombre1, nombre2);
	//consulta SQL
	sprintf(consulta, "SELECT Partida.Duracion FROM JUGADOR WHERE Partida.Njugador1 = '%s'",nombre1,"OR Partida.Njugador2 = '%d'",nombre1);	
	//Comprobamos consulta
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	//Recogemos el resultado
	if (row == NULL)
		return -1;
	else
		res = strtok(row[0]," ");
		return res;
	mysql_close (conn);
	exit(0);
}

void Login(char nombre[25], int DNI[25], char respuesta[512])
{
	MYSQL *conn;
	int err;
	int login;
	char consulta[500];
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error al crear la conexion1: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "JUEGO", 0, NULL, 0);
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion2: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	sprintf(consulta, "SELECT Jugador.Nombre, Jugador.DNI FROM Jugadores WHERE (Jugadores.Nombre='%s' AND Jugadores.DNI='%s')", nombre, DNI);
	err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Error al consultar datos de la base %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
		sprintf(respuesta, "0-Error-Al consultar la base de datos");
	}
	else
	{
		MYSQL_RES* resultado;
		resultado = mysql_store_result(conn);
		int num_filas = mysql_num_rows(resultado);
		mysql_free_result(resultado);
		
		if (num_filas > 0) {
			printf("Ha iniciado sesion el usuario con nombre: %s\n", nombre);
			sprintf(respuesta, "0-SI");
		}
		else {
			printf("No se encontro el usuario con nombre: %s\n", nombre);
			sprintf(respuesta, "0-Error-Usuario o contrasena mal introducida");
		}
	}
	mysql_close(conn);
}
void Registrar(char nombre[25], int DNI[25],float edad, char respuesta[512])
{
	char consulta[500];
	int numJ;
	int err;
	MYSQL *conn;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error al crear la conexion1: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "JUEGO", 0, NULL, 0);
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion2: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	sprintf(consulta, "INSERT INTO JUGADOR VALUES ('%s', '%s', %s)", nombre, DNI, edad);
	err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Error al insertar datos en la base: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
		sprintf(respuesta, "1-Error");
	}
	
	else
	{
		sprintf(respuesta, "Se ha podido registrar correctamente");
	}
	mysql_close(conn);
}

int main(int argc, char *argv[]) {
	
	int sock_conn,sock_listen,ret;
	struct sockaddr_in serv_adr;
	char buff[512];
	
	if(argc!=2)
		error()
	
	if((sock_listen = socket(Af_INET,SOCK_STREAM,0))<0)
		error("Error creando el socket");
	
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(9050);
	(bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
	error("Error al bind");
	
	f (listen(sock_listen, 10) < 0)
	error("listen");
	
	for(;;){
		printf("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
	
	ret = ssize_t read(int sock_conn, void *buff, sizeof(buff));
	
	
	close(sock_conn);
}