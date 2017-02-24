typedef struct lista {
	char *nombre;
	struct amigos *friends;
	struct lista *sig;
}LISTA;

typedef struct amigos {
	char *amigo;
	struct amigos *sig;
}AMIGOS;

typedef struct comparacion {

	char *tupla;
	struct amigos *primero;
	struct amigos *segundo;
	struct comparacion *sig;

}COMPARACION;

typedef struct hilos {

	struct lista *argumento1;
	
	struct comparacion *argumento2;
	
}HILOS;