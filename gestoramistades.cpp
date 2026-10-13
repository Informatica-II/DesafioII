#include "Gestoramistades.h"
#include <iostream>
#include <fstream>

using namespace std;

GestorAmistades::GestorAmistades() {}

bool GestorAmistades::existeUsuario(const char* nombreUsuario, int& iteraciones) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro usuarios.txt" << endl;
        return false;
    }

    char linea[50];
    bool encontrado = false;

    while (archivo.getline(linea, 50)) {
        iteraciones++;
        bool coincide = true;
        for (int i = 0; nombreUsuario[i] != '\0' || linea[i] != '|'; i++) {
            iteraciones++;
            if (linea[i] == '|' && nombreUsuario[i] == '\0'){
                break;
            }
            if (nombreUsuario[i] != linea[i]) {
                coincide = false;
                break;
            }
        }
        if (coincide) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    return encontrado;
}

bool GestorAmistades::sonAmigos(const char* usuario1, const char* usuario2, int& iteraciones) {
    ifstream archivo("amigos.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro usuarios.txt" << endl;
        return false;
    }

    char linea[250];
    bool amigos = false;

    while (archivo.getline(linea, 250)) {
        iteraciones++;
        char duenio[25] = {0};
        int i = 0;
        int posDuenio = 0;

        while (linea[i] != '|' && linea[i] != '\0' && posDuenio < 24) {
            duenio[posDuenio++] = linea[i++];
        }
        duenio[posDuenio] = '\0';

        bool esDuenio = true;
        for (int k = 0; duenio[k] != '\0' || usuario1[k] != '\0'; k++) {
            iteraciones++;
            if (duenio[k] != usuario1[k]) {
                esDuenio = false;
                break;
            }
        }

        if (esDuenio && linea[i] == '|') {
            i++;
            char amigo[25] = {0};
            int posAmigo = 0;
            while (linea[i] != '\0') {
                iteraciones++;
                if (linea[i] == '/' || linea[i] == '\r') {
                    amigo[posAmigo] = '\0';
                    bool match = true;
                    for (int m = 0; amigo[m] != '\0' || usuario2[m] != '\0'; m++) {
                        if (amigo[m] != usuario2[m]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        amigos = true;
                        break;
                    }
                    posAmigo = 0;
                }
                else if (posAmigo < 24) {
                    amigo[posAmigo++] = linea[i];
                }
                i++;
            }
            amigo[posAmigo] = '\0';
            bool matchFinal = true;
            for (int m = 0; amigo[m] != '\0' || usuario2[m] != '\0'; m++) {
                if (amigo[m] != usuario2[m]) {
                    matchFinal = false;
                    break;
                }
            }
            if (matchFinal && amigo[0] != '\0') amigos = true;
        }
        if (amigos) break;
    }
    archivo.close();
    return amigos;
}

bool GestorAmistades::existeSolicitud(const char* emisor, const char* receptor, int& iteraciones) {
    ifstream archivo("solicitudes.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro usuarios.txt" << endl;
        return false;
    }
    char linea[250];
    bool existe = false;

    while (archivo.getline(linea, 250)) {
        iteraciones++;
        char duenio[25] = {0};
        int i = 0;
        int posDuenio = 0;

        while (linea[i] != '|' && linea[i] != '\0' && posDuenio < 24) {
            duenio[posDuenio++] = linea[i++];
        }
        duenio[posDuenio] = '\0';

        bool esReceptor = true;
        for (int k = 0; duenio[k] != '\0' || receptor[k] != '\0'; k++) {
            if (duenio[k] != receptor[k]) {
                esReceptor = false;
                break;
            }
        }

        if (esReceptor && linea[i] == '|') {
            i++;
            char sol[25] = {0};
            int posSol = 0;
            while (linea[i] != '\0') {
                iteraciones++;
                if (linea[i] == '/' || linea[i] == '\r') {
                    sol[posSol] = '\0';
                    bool match = true;
                    for (int m = 0; sol[m] != '\0' || emisor[m] != '\0'; m++) {
                        if (sol[m] != emisor[m]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        existe = true;
                        break;
                    }
                    posSol = 0;
                }
                else if (posSol < 24) {
                    sol[posSol++] = linea[i];
                }
                i++;
            }
            sol[posSol] = '\0';
            bool matchFinal = true;
            for (int m = 0; sol[m] != '\0' || emisor[m] != '\0'; m++) {
                if (sol[m] != emisor[m]) {
                    matchFinal = false;
                    break;
                }
            }
            if (matchFinal && sol[0] != '\0') existe = true;
        }
        if (existe) break;
    }
    archivo.close();
    return existe;
}

void GestorAmistades::guardarElemento(const char* nombreArchivo, const char* duenio, const char* elemento, int& iteraciones) {
    ifstream archivoLeido(nombreArchivo);
    ofstream archivoTemp("temp.txt");

    bool duenioEncontrado = false;
    char linea[250];

    if (archivoLeido.is_open()) {
        while (archivoLeido.getline(linea, 250)) {
            iteraciones++;
            char d[25] = {0};
            int i = 0, posD = 0;

            while (linea[i] != '|' && linea[i] != '\0' && posD < 24) {
                d[posD++] = linea[i++];
            }
            d[posD] = '\0';

            bool esDuenio = true;
            for (int k = 0; d[k] != '\0' || duenio[k] != '\0'; k++) {
                iteraciones++;
                if (d[k] != duenio[k]) {
                    esDuenio = false;
                    break;
                }
            }

            if (esDuenio) {
                duenioEncontrado = true;
                archivoTemp << linea;

                int j = 0;
                while(linea[j] != '\0') { iteraciones++; j++; }

                if (j > i + 1) archivoTemp << '/';
                archivoTemp << elemento << "\n";

            } else {
                archivoTemp << linea << "\n";
            }
        }
        archivoLeido.close();
    }

    if (!duenioEncontrado) {
        archivoTemp << duenio << "|" << elemento << "\n";
    }
    archivoTemp.close();

    ifstream leerTemp("temp.txt");
    ofstream escribirOriginal(nombreArchivo);

    if (leerTemp.is_open()) {
        while (leerTemp.getline(linea, 250)) {
            iteraciones++;
            escribirOriginal << linea << "\n";
        }
        leerTemp.close();
        escribirOriginal.close();
    }
}

void GestorAmistades::eliminarSolicitudPendiente(const char* emisor, const char* receptor, int& iteraciones) {
    ifstream archivoLeido("solicitudes.txt");
    ofstream archivoTemp("temp.txt");

    if (!archivoLeido.is_open()) return;

    char linea[250];

    while (archivoLeido.getline(linea, 250)) {
        iteraciones++;
        char duenio[25] = {0};
        int i = 0, posDuenio = 0;

        while (linea[i] != '|' && linea[i] != '\0' && posDuenio < 24) {
            duenio[posDuenio++] = linea[i++];
        }
        duenio[posDuenio] = '\0';

        bool esReceptor = true;
        for (int k = 0; duenio[k] != '\0' || receptor[k] != '\0'; k++) {
            iteraciones++;
            if (duenio[k] != receptor[k]) {
                esReceptor = false;
                break;
            }
        }

        if (esReceptor && linea[i] == '|') {
            i++;
            archivoTemp << duenio << "|";

            char sol[25] = {0};
            int posSol = 0;
            bool primero = true;

            while (linea[i] != '\0') {
                if (linea[i] == '/' || linea[i] == '\r') {
                    sol[posSol] = '\0';
                    bool match = true;
                    for (int m = 0; sol[m] != '\0' || emisor[m] != '\0'; m++) {
                        if (sol[m] != emisor[m]) {
                            match = false;
                            break;
                        }
                    }
                    if (!match && sol[0] != '\0') {
                        if (!primero) archivoTemp << '/';
                        archivoTemp << sol;
                        primero = false;
                    }
                    posSol = 0;
                }
                else if (posSol < 24) {
                    sol[posSol++] = linea[i];
                }
                i++;
            }

            sol[posSol] = '\0';
            bool matchFinal = true;
            for (int m = 0; sol[m] != '\0' || emisor[m] != '\0'; m++) {
                if (sol[m] != emisor[m]) {
                    matchFinal = false;
                    break;
                }
            }
            if (!matchFinal && sol[0] != '\0') {
                if (!primero) archivoTemp << '/';
                archivoTemp << sol;
            }
            archivoTemp << "\n";
        }
        else {
            archivoTemp << linea << "\n";
        }
    }
    archivoLeido.close();
    archivoTemp.close();

    ifstream leerTemp("temp.txt");
    ofstream escribirOriginal("solicitudes.txt");

    if (leerTemp.is_open()) {
        while (leerTemp.getline(linea, 250)) {
            iteraciones++;
            bool estaVacia = true;
            for (int k = 0; linea[k] != '\0'; k++) {
                if (linea[k] == '|') {
                    if (linea[k+1] != '\0' && linea[k+1] != '\r' && linea[k+1] != '\n') {
                        estaVacia = false;
                    }
                    break;
                }
            }
            if (!estaVacia) {
                escribirOriginal << linea << "\n";
            }
        }
        leerTemp.close();
        escribirOriginal.close();
    }
}

void GestorAmistades::administrar(const char* usuarioActivo, int& iteracionesGlobales, int& memoriaGlobal) {
    int opcion = 0;
    do {
        cout << "\n--- GESTOR DE AMISTADES ---" << endl;
        cout << "1. Enviar solicitud de amistad" << endl;
        cout << "2. Ver solicitudes de amistad" << endl;
        cout << "3. Volver" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        int iteraciones = 0;
        int memoria = 0;

        switch (opcion) {
        case 1: {
            char usuarioDestino[25];
            cout << "Ingrese el usuario destino: ";
            cin.getline(usuarioDestino, 25);

            bool mismo = true;
            for (int i = 0; usuarioActivo[i] != '\0' || usuarioDestino[i] != '\0'; i++) {
                if (usuarioActivo[i] != usuarioDestino[i]) {
                    mismo = false;
                    break;
                }
            }

            if (mismo) cout << "[!] No puedes enviarte a ti mismo." << endl;
            else if (!existeUsuario(usuarioDestino, iteraciones)) cout << "[!] Usuario no existe." << endl;
            else if (sonAmigos(usuarioActivo, usuarioDestino, iteraciones)) cout << "[!] Ya son amigos." << endl;
            else if (existeSolicitud(usuarioActivo, usuarioDestino, iteraciones)) cout << "[!] Ya enviaste solicitud." << endl;
            else if (existeSolicitud(usuarioDestino, usuarioActivo, iteraciones)) cout << "[!] Ya te envio solicitud, ve a aceptarla." << endl;
            else {
                guardarElemento("solicitudes.txt", usuarioDestino, usuarioActivo, iteraciones);
                cout << "[EXITO] Solicitud enviada a " << usuarioDestino << "." << endl;
            }
            memoria += sizeof(usuarioDestino);
            break;
        }
        case 2: {
            cout << "\n--- SOLICITUDES RECIBIDAS ---" << endl;
            ifstream archivo("solicitudes.txt");
            if (!archivo.is_open()) {
                cout << "No tienes solicitudes pendientes." << endl;
                break;
            }

            char listaSolicitudes[50][25];
            int totalSol = 0;
            char linea[250];

            while (archivo.getline(linea, 250)) {
                iteraciones++;
                char duenio[25] = {0};
                int i = 0, posD = 0;

                while (linea[i] != '|' && linea[i] != '\0' && posD < 24) {
                    duenio[posD++] = linea[i++];
                }
                duenio[posD] = '\0';

                bool esUsuarioActivo = true;
                for (int k = 0; duenio[k] != '\0' || usuarioActivo[k] != '\0'; k++) {
                    if (duenio[k] != usuarioActivo[k]) {
                        esUsuarioActivo = false;
                        break;
                    }
                }

                if (esUsuarioActivo && linea[i] == '|') {
                    i++;
                    char sol[25] = {0};
                    int posSol = 0;
                    while (linea[i] != '\0') {
                        if (linea[i] == '/' || linea[i] == '\r') {
                            sol[posSol] = '\0';

                            if (sol[0] != '\0' && totalSol < 50) {
                                for (int m = 0; m <= posSol; m++) {
                                    listaSolicitudes[totalSol][m] = sol[m];
                                }
                                totalSol++;
                            }
                            posSol = 0;
                        } else if (posSol < 24) {
                            sol[posSol++] = linea[i];
                        }
                        i++;
                    }

                    sol[posSol] = '\0';
                    if (sol[0] != '\0' && totalSol < 50) {
                        for (int m = 0; m <= posSol; m++) {
                            listaSolicitudes[totalSol][m] = sol[m];
                        }
                        totalSol++;
                    }
                    break;
                }
            }
            archivo.close();

            if (totalSol == 0) {
                cout << "No tienes solicitudes pendientes." << endl;
            } else {
                for (int i = 0; i < totalSol; i++) {
                    cout << i + 1 << ". " << listaSolicitudes[i] << endl;
                }
                cout << "0. Cancelar" << endl;
                cout << "Selecciona el numero de la solicitud para aceptar: ";
                int seleccion;
                cin >> seleccion;
                cin.ignore();

                if (seleccion > 0 && seleccion <= totalSol) {
                    const char* nuevoAmigo = listaSolicitudes[seleccion - 1];

                    guardarElemento("amigos.txt", usuarioActivo, nuevoAmigo, iteraciones);
                    guardarElemento("amigos.txt", nuevoAmigo, usuarioActivo, iteraciones);
                    eliminarSolicitudPendiente(nuevoAmigo, usuarioActivo, iteraciones);

                    cout << "[EXITO] Ahora eres amigo de " << nuevoAmigo << "." << endl;
                }
            }

            memoria += sizeof(listaSolicitudes);
            break;
        }
        case 3:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
        iteracionesGlobales += iteraciones;
        memoriaGlobal += memoria;
    } while (opcion != 3);
}