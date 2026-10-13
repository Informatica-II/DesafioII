#include "plataforma.h"
#include <iostream>
#include <fstream>
#include "GestorAmistades.h"

using namespace std;

Plataforma::Plataforma() {
    usuarioActivo[0] = '\0';
    sesionIniciada = false;
}

void Plataforma::iniciar() {
    int opcion = 0;

    do {
        cout << "===============================" << endl;
        cout << "           UdeaBook            " << endl;
        cout << "===============================" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- INICIO DE SESION ---" << endl;

                int iteraciones = 0;
                int memoria = 0;

                bool exito = procesarInicioSesion(iteraciones, memoria);

                if (exito) {
                    cout << "\nBienvenido a UdeaBook " << usuarioActivo << "." << endl;

                    menuInterno();

                    sesionIniciada = false;
                    usuarioActivo[0] = '\0';
                }
                else {
                    cout << "Usuario o contrasenia incorrectos." << endl;
                }

                int memoriaTotalSistema = memoria + sizeof(opcion) + sizeof(exito);

                cout << "\n--- REPORTE DE RENDIMIENTO ---" << endl;
                cout << "a. Iteraciones requeridas : " << iteraciones << " ciclos." << endl;
                cout << "b. Memoria consumida      : " << memoriaTotalSistema << " bytes." << endl;
                cout << "------------------------------\n" << endl;
                break;
            }
            case 2:
                cout << "\nSaliendo de la plataforma... Hasta pronto." << endl;
                break;
            default:
                cout << "\nOpcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 2);
}

bool Plataforma::procesarInicioSesion(int& iteraciones, int& memoriaEnUso) {
    iteraciones = 0;
    memoriaEnUso = 0;

    char nombreIngresado[25];
    char contraseniaIngresada[25];

    cout << "Usuario: ";
    cin.getline(nombreIngresado, 25);
    cout << "Contrasenia: ";
    cin.getline(contraseniaIngresada, 25);

    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro usuarios.txt" << endl;
        return false;
    }

    char lineaLeida[50];
    bool accesoConcedido = false;

    while (archivo.getline(lineaLeida, 50)) {
        iteraciones++;

        char usuarioLeido[25] = {0};
        char contraseniaLeida[25] = {0};
        bool leyendoUsuario = true;
        int posUser = 0;
        int posPass = 0;

        for (int i = 0; lineaLeida[i] != '\0'; i++) {
            iteraciones++;

            if (lineaLeida[i] == '|') {
                leyendoUsuario = false;
            }
            else {
                if (leyendoUsuario) {
                    usuarioLeido[posUser++] = lineaLeida[i];
                }
                else {
                    contraseniaLeida[posPass++] = lineaLeida[i];
                }
            }
        }

        bool coincideUsuario = true;
        for (int i = 0; nombreIngresado[i] != '\0' || usuarioLeido[i] != '\0'; i++) {
            iteraciones++;
            if (nombreIngresado[i] != usuarioLeido[i]) {
                coincideUsuario = false;
                break;
            }
        }

        bool coincidePass = true;
        if (coincideUsuario) {
            for (int i = 0; contraseniaIngresada[i] != '\0' || contraseniaLeida[i] != '\0'; i++) {
                iteraciones++;
                if (contraseniaIngresada[i] != contraseniaLeida[i]) {
                    coincidePass = false;
                    break;
                }
            }
        }
        else {
            coincidePass = false;
        }

        if (coincideUsuario && coincidePass) {
            accesoConcedido = true;
            this->sesionIniciada = true;

            for(int i = 0; usuarioLeido[i] != '\0'; i++) {
                this->usuarioActivo[i] = usuarioLeido[i];
            }
            this->usuarioActivo[posUser] = '\0';

            break;
        }
    }

    memoriaEnUso = sizeof(*this) + sizeof(nombreIngresado) + sizeof(contraseniaIngresada) + sizeof(lineaLeida) + sizeof(archivo) + sizeof(accesoConcedido);

    archivo.close();
    return accesoConcedido;
}

void Plataforma::menuInterno() {
    int opcion = 0;

    int iteracionesGlobales = 0;
    int memoriaGlobal = 0;

    do {
        cout << "\n===============================" << endl;
        cout << "      Menu de opciones      " << endl;
        cout << "===============================" << endl;
        cout << "1. Gestionar Amistades" << endl;
        cout << "2. Gestionar Albumes" << endl;
        cout << "3. Gestionar Mensajes" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\nEntrando a Gestor de Amistades..." << endl;
                GestorAmistades gestorAmigos;
                gestorAmigos.administrar(usuarioActivo, iteracionesGlobales, memoriaGlobal);
                break;
            }
            case 2:
                cout << "\nEntrando a Gestor de Albumes..." << endl;
                break;
            case 3:
                cout << "\nEntrando a Gestor de Mensajes..." << endl;
                break;
            case 4:
                cout << "\nCerrando sesion..." << endl;
                cout << "--- RENDIMIENTO DE LA SESION ---" << endl;
                cout << "Iteraciones: " << iteracionesGlobales << endl;
                cout << "Memoria extra: " << memoriaGlobal << " bytes" << endl;
                cout << "--------------------------------" << endl;
                break;
            default:
                cout << "\nOpcion no valida." << endl;
                break;
        }
    } while (opcion != 4);
}

Plataforma::~Plataforma() {}