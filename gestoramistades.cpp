#include "Gestoramistades.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

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

    bool amigos = false;
    int capacidad = 50;
    char* linea = new char[capacidad];
    char letra;
    int pos = 0;
    bool continuar = true;

    while (continuar) {
        if (archivo.get(letra)) {
            iteraciones++;
            if (letra == '\r') continue;
            if (letra != '\n') {
                if (pos >= capacidad - 1) {
                    redimensionarLinea(linea, capacidad, iteraciones);
                }
                linea[pos++] = letra;
                continue;
            }
        }
        else {
            continuar = false;
            if (pos == 0) break;
        }
        linea[pos] = '\0';

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

        pos = 0;
        if (amigos) break;
    }

    delete[] linea;
    archivo.close();
    return amigos;
}

bool GestorAmistades::existeSolicitud(const char* emisor, const char* receptor, int& iteraciones) {
    ifstream archivo("solicitudes.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro usuarios.txt" << endl;
        return false;
    }

    bool existe = false;
    int capacidad = 50;
    char* linea = new char[capacidad];
    char letra;
    int pos = 0;
    bool continuar = true;

    while (continuar) {
        if (archivo.get(letra)) {
            iteraciones++;
            if (letra == '\r') continue;
            if (letra != '\n') {
                if (pos >= capacidad - 1) {
                    redimensionarLinea(linea, capacidad, iteraciones);
                }
                linea[pos++] = letra;
                continue;
            }
        }
        else {
            continuar = false;
            if (pos == 0) break;
        }
        linea[pos] = '\0';

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

        pos = 0;
        if (existe) break;
    }

    delete[] linea;
    archivo.close();
    return existe;
}

void GestorAmistades::guardarElemento(const char* nombreArchivo, const char* duenio, const char* elemento, int& iteraciones) {
    ifstream archivoLeido(nombreArchivo);
    ofstream archivoTemp("temp.txt");
    bool duenioEncontrado = false;

    if (archivoLeido.is_open()) {
        int capacidad = 50;
        char* linea = new char[capacidad];
        char letra;
        int pos = 0;
        bool continuar = true;

        while (continuar) {
            if (archivoLeido.get(letra)) {
                iteraciones++;
                if (letra == '\r') continue;
                if (letra != '\n') {
                    if (pos >= capacidad - 1) {
                        redimensionarLinea(linea, capacidad, iteraciones);
                    }
                    linea[pos++] = letra;
                    continue;
                }
            }
            else {
                continuar = false;
                if (pos == 0) break;
            }
            linea[pos] = '\0';

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
            }
            else {
                archivoTemp << linea << "\n";
            }

            pos = 0;
        }
        delete[] linea;
        archivoLeido.close();
    }

    if (!duenioEncontrado) {
        archivoTemp << duenio << "|" << elemento << "\n";
    }
    archivoTemp.close();

    ifstream leerTemp("temp.txt");
    ofstream escribirOriginal(nombreArchivo);

    if (leerTemp.is_open()) {
        int capacidad = 50;
        char* linea = new char[capacidad];
        char letra;
        int pos = 0;
        bool continuar = true;

        while (continuar) {
            if (leerTemp.get(letra)) {
                iteraciones++;
                if (letra == '\r') continue;
                if (letra != '\n') {
                    if (pos >= capacidad - 1) {
                        redimensionarLinea(linea, capacidad, iteraciones);
                    }
                    linea[pos++] = letra;
                    continue;
                }
            }
            else {
                continuar = false;
                if (pos == 0) break;
            }
            linea[pos] = '\0';

            escribirOriginal << linea << "\n";
            pos = 0;
        }
        delete[] linea;
        leerTemp.close();
        escribirOriginal.close();
    }
}

void GestorAmistades::eliminarSolicitudPendiente(const char* emisor, const char* receptor, int& iteraciones) {
    ifstream archivoLeido("solicitudes.txt");
    ofstream archivoTemp("temp.txt");
    if (!archivoLeido.is_open()) return;

    int capacidad = 50;
    char* linea = new char[capacidad];
    char letra;
    int pos = 0;
    bool continuar = true;

    while (continuar) {
        if (archivoLeido.get(letra)) {
            iteraciones++;
            if (letra == '\r') continue;
            if (letra != '\n') {
                if (pos >= capacidad - 1) {
                    redimensionarLinea(linea, capacidad, iteraciones);
                }
                linea[pos++] = letra;
                continue;
            }
        }
        else {
            continuar = false;
            if (pos == 0) break;
        }
        linea[pos] = '\0';

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

        pos = 0;
    }
    delete[] linea;
    archivoLeido.close();
    archivoTemp.close();

    ifstream leerTemp("temp.txt");
    ofstream escribirOriginal("solicitudes.txt");

    if (leerTemp.is_open()) {
        capacidad = 50;
        char* lineaFase2 = new char[capacidad];
        pos = 0;
        continuar = true;

        while (continuar) {
            if (leerTemp.get(letra)) {
                iteraciones++;
                if (letra == '\r') continue;
                if (letra != '\n') {
                    if (pos >= capacidad - 1) {
                        redimensionarLinea(lineaFase2, capacidad, iteraciones);
                    }
                    lineaFase2[pos++] = letra;
                    continue;
                }
            }
            else {
                continuar = false;
                if (pos == 0) break;
            }
            lineaFase2[pos] = '\0';

            bool estaVacia = true;
            for (int k = 0; lineaFase2[k] != '\0'; k++) {
                if (lineaFase2[k] == '|') {
                    if (lineaFase2[k+1] != '\0') {
                        estaVacia = false;
                    }
                    break;
                }
            }
            if (!estaVacia) {
                escribirOriginal << lineaFase2 << "\n";
            }

            pos = 0;
        }
        delete[] lineaFase2;
        leerTemp.close();
        escribirOriginal.close();
    }
}

void GestorAmistades::administrar(const char* usuarioActivo, int& iteracionesGlobales, int& memoriaGlobal) {
    int opcion = 0;
    do {
        cout << "\n===============================" << endl;
        cout << "      Gestor de Amistades      " << endl;
        cout << "===============================" << endl;
        cout << "1. Ver solicitudes pendientes" << endl;
        cout << "2. Enviar solicitud directa" << endl;
        cout << "3. Ver sugerencias de amistad" << endl;
        cout << "4. Visitar perfil de un amigo" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "===============================" << endl;
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

            int capacidad = 50;
            char* linea = new char[capacidad];
            char letra;
            int pos = 0;
            bool continuar = true;

            while (continuar) {
                if (archivo.get(letra)) {
                    iteraciones++;
                    if (letra == '\r') continue;
                    if (letra != '\n') {
                        if (pos >= capacidad - 1) {
                            redimensionarLinea(linea, capacidad, iteraciones);
                        }
                        linea[pos++] = letra;
                        continue;
                    }
                }
                else {
                    continuar = false;
                    if (pos == 0) break;
                }
                linea[pos] = '\0';

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
                        }
                        else if (posSol < 24) {
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
                pos = 0;
            }

            delete[] linea;
            archivo.close();

            if (totalSol == 0) {
                cout << "No tienes solicitudes pendientes." << endl;
            }
            else {
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
            int k;
            cout << "\n--- SUGERENCIAS DE AMISTAD ---" << endl;
            cout << "Ingrese la cantidad de sugerencias que desea ver (entre 1 y 20): ";
            cin >> k;
            cin.ignore();

            if (k >= 1 && k <= 20) {
                sugerirAmigos(usuarioActivo, k, iteracionesGlobales, memoriaGlobal);
            }
            else {
                cout << "Error: El valor debe ser un numero entero entre 1 y 20." << endl;
            }
            break;
        case 4:
            visitarPerfilAmigo(string(usuarioActivo), iteracionesGlobales, memoriaGlobal);
            break;
        case 5:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

        if (opcion >= 1 && opcion <= 4) {
            cout << "\n--- METRICAS ---" << endl;
            cout << "Iteraciones consumidas : " << iteraciones << " ciclos." << endl;
            cout << "Memoria extra usada    : " << memoria << " bytes." << endl;
            cout << "--------------------------------" << endl;
        }

        iteracionesGlobales += iteraciones;
        memoriaGlobal += memoria;
    } while (opcion != 5);
}

void GestorAmistades::redimensionarLinea(char*& buffer, int& capacidadActual, int& iteraciones) {
    int nuevaCapacidad = capacidadActual * 2;
    char* nuevoBuffer = new char[nuevaCapacidad];

    for (int i = 0; i < capacidadActual; i++) {
        iteraciones++;
        nuevoBuffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = nuevoBuffer;
    capacidadActual = nuevaCapacidad;
}

void GestorAmistades::sugerirAmigos(const string &usuarioActivo, int k, int &iteraciones, int &memoria)
{
    int totalUsuarios = 0;
    ifstream archivo("amigos.txt");
    string linea;
    while (getline(archivo, linea)) {
        totalUsuarios++;
        iteraciones++;
    }
    archivo.close();

    if (totalUsuarios == 0) return;

    string* misAmigos = new string[totalUsuarios];
    string* candidatos = new string[totalUsuarios];
    int* comunes = new int[totalUsuarios];

    int numMisAmigos = 0, numCandidatos = 0;
    memoria += (sizeof(string) * totalUsuarios * 2) + (sizeof(int) * totalUsuarios);

    archivo.open("amigos.txt");
    while (getline(archivo, linea)) {
        iteraciones++;
        memoria += linea.length();
        string duenioFila = "";
        int i = 0;

        while (linea[i] != '|' && linea[i] != '\0') {
            iteraciones++;
            duenioFila += linea[i++];
        }

        if (duenioFila == usuarioActivo && linea[i] == '|') {
            i++;
            while (linea[i] != '\0') {
                string amigo = "";
                while (linea[i] != '/' && linea[i] != '\0') {
                    iteraciones++;
                    amigo += linea[i++];
                }
                if (amigo != "") {
                    misAmigos[numMisAmigos++] = amigo;
                    memoria += amigo.length();
                }
                if (linea[i] == '/') i++;
            }
            break;
        }
    }
    archivo.close();

    archivo.open("amigos.txt");
    while (getline(archivo, linea)) {
        iteraciones++;
        string duenioFila = "";
        int i = 0;

        while (linea[i] != '|' && linea[i] != '\0') {
            iteraciones++;
            duenioFila += linea[i++];
        }

        if (linea[i] == '|') {
            i++;
            bool esMiAmigo = false;
            for (int m = 0; m < numMisAmigos; m++) {
                iteraciones++;
                if (misAmigos[m] == duenioFila) {
                    esMiAmigo = true;
                    break;
                }
            }

            if (esMiAmigo) {
                while (linea[i] != '\0') {
                    string amigoDeAmigo = "";
                    while (linea[i] != '/' && linea[i] != '\0') {
                        iteraciones++;
                        amigoDeAmigo += linea[i++];
                    }

                    if (amigoDeAmigo != "" && amigoDeAmigo != usuarioActivo) {

                        bool yaEsMiAmigo = false;
                        for (int m = 0; m < numMisAmigos; m++) {
                            iteraciones++;
                            if (misAmigos[m] == amigoDeAmigo) {
                                yaEsMiAmigo = true;
                                break;
                            }
                        }

                        if (!yaEsMiAmigo) {
                            bool yaEstaEnCandidatos = false;
                            for (int c = 0; c < numCandidatos; c++) {
                                iteraciones++;
                                if (candidatos[c] == amigoDeAmigo) {
                                    comunes[c]++;
                                    yaEstaEnCandidatos = true;
                                    break;
                                }
                            }

                            if (!yaEstaEnCandidatos) {
                                candidatos[numCandidatos] = amigoDeAmigo;
                                comunes[numCandidatos] = 1;
                                numCandidatos++;
                                memoria += amigoDeAmigo.length();
                            }
                        }
                    }
                    if (linea[i] == '/') i++;
                }
            }
        }
    }
    archivo.close();

    for (int i = 0; i < numCandidatos - 1; i++) {
        iteraciones++;
        for (int j = 0; j < numCandidatos - i - 1; j++) {
            iteraciones++;
            if (comunes[j] < comunes[j + 1]) {
                int tempInt = comunes[j]; comunes[j] = comunes[j + 1]; comunes[j + 1] = tempInt;
                string tempStr = candidatos[j]; candidatos[j] = candidatos[j + 1]; candidatos[j + 1] = tempStr;
            }
        }
    }

    cout << "\n--- TOP " << k << " SUGERENCIAS DE AMISTAD ---" << endl;
    int mostrados = 0;
    for (int i = 0; i < numCandidatos && i < k; i++) {
        iteraciones++;
        cout << i + 1 << ". " << candidatos[i] << " (" << comunes[i] << " amigos en comun)" << endl;
        mostrados++;
    }

    if (mostrados > 0) {
        cout << "\nIngrese el numero del usuario para enviar solicitud (0 para salir): ";
        int seleccion;
        cin >> seleccion; cin.ignore();

        if (seleccion > 0 && seleccion <= mostrados) {
            string destino = candidatos[seleccion - 1];
            ofstream archSol("solicitudes.txt", ios::app);
            archSol << usuarioActivo << "|" << destino << "\n";
            archSol.close();
            cout << "Solicitud de amistad enviada a " << destino << "." << endl;
        }
    }
    else {
        cout << "No hay sugerencias disponibles en este momento." << endl;
    }

    delete[] misAmigos;
    delete[] candidatos;
    delete[] comunes;
}

void GestorAmistades::visitarPerfilAmigo(const string& usuarioActivo, int& iteraciones, int& memoria) {
    string amigo;
    cout << "\n--- VISITAR PERFIL ---" << endl;
    cout << "Ingrese el nombre de usuario del amigo: ";
    getline(cin, amigo);
    memoria += amigo.length();

    if (!sonAmigos(usuarioActivo.c_str(), amigo.c_str(), iteraciones)) {
        cout << "Acceso denegado: No eres amigo de " << amigo << "." << endl;
        return;
    }

    int maxAlbumes = 5;
    string* albumesDisponibles = new string[maxAlbumes];
    string* privacidades = new string[maxAlbumes];
    string* rutasAlbumes = new string[maxAlbumes];
    memoria += sizeof(string) * maxAlbumes * 3;
    int numDisp = 0;

    ifstream archAlbumes("albumes.txt");
    string linea;
    while (getline(archAlbumes, linea)) {
        iteraciones++;
        string duenio = "";
        int i = 0;
        while(linea[i] != '|' && linea[i] != '\0') {
            duenio += linea[i++];
            iteraciones++;
        }

        if (duenio == amigo && linea[i] == '|') {
            i++;
            while(linea[i] != '\0') {
                string album = "", rutaAlb = "", privacidad = "";

                while(linea[i] != '~' && linea[i] != '\0') {
                    album += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '~' && linea[i] != '\0') {
                    rutaAlb += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '^' && linea[i] != '\0') {
                    privacidad += linea[i++];
                    iteraciones++;
                }

                if (numDisp >= maxAlbumes) {
                    int nuevoMax = maxAlbumes * 2;
                    string* tempA = new string[nuevoMax];
                    string* tempP = new string[nuevoMax];
                    string* tempR = new string[nuevoMax];
                    memoria += sizeof(string) * nuevoMax * 3;

                    for (int k = 0; k < numDisp; k++) {
                        tempA[k] = albumesDisponibles[k];
                        tempP[k] = privacidades[k];
                        tempR[k] = rutasAlbumes[k];
                        iteraciones++;
                    }
                    delete[] albumesDisponibles;
                    delete[] privacidades;
                    delete[] rutasAlbumes;
                    albumesDisponibles = tempA;
                    privacidades = tempP;
                    rutasAlbumes = tempR;
                    maxAlbumes = nuevoMax;
                }

                albumesDisponibles[numDisp] = album;
                privacidades[numDisp] = privacidad;
                rutasAlbumes[numDisp] = rutaAlb;
                numDisp++;
                memoria += album.length() + privacidad.length() + rutaAlb.length();

                if(linea[i] == '^') i++;
            }
            break;
        }
    }
    archAlbumes.close();

    if (numDisp == 0) {
        cout << amigo << " no tiene albumes disponibles para ti." << endl;
        delete[] albumesDisponibles;
        delete[] privacidades;
        delete[] rutasAlbumes;
        return;
    }

    cout << "\nAlbumes de " << amigo << ":" << endl;
    for (int i = 0; i < numDisp; i++) {
        iteraciones++;
        cout << i + 1 << ". " << albumesDisponibles[i] << " [Privacidad: " << privacidades[i] << "]" << endl;
        cout << "   Ruta: " << rutasAlbumes[i] << endl;
        cout << endl;
    }

    cout << "Seleccione el numero del album a visualizar (0 para salir): ";
    int selAlbum;
    cin >> selAlbum; cin.ignore();

    if (selAlbum <= 0 || selAlbum > numDisp) {
        delete[] albumesDisponibles;
        delete[] privacidades;
        delete[] rutasAlbumes;
        return;
    }

    string albumElegido = albumesDisponibles[selAlbum - 1];
    string privElegida = privacidades[selAlbum - 1];

    delete[] albumesDisponibles;
    delete[] privacidades;
    delete[] rutasAlbumes;

    if (privElegida == "privado") {
        cout << "\nACCESO DENEGADO: El album '" << albumElegido << "' es privado." << endl;
        return;
    }

    int maxFotos = 5;
    string* rutasFotos = new string[maxFotos];
    string* nombresFotos = new string[maxFotos];
    string* fechasFotos = new string[maxFotos];
    string* tamFotos = new string[maxFotos];
    int* likesFotos = new int[maxFotos];
    memoria += (sizeof(string) * maxFotos * 4) + (sizeof(int) * maxFotos);
    int numFotosAlbum = 0;

    ifstream archFotos("fotos.txt");
    while (getline(archFotos, linea)) {
        iteraciones++;
        string duenio = "";
        int i = 0;
        while(linea[i] != '|' && linea[i] != '\0') {
            duenio += linea[i++];
            iteraciones++;
        }

        if (duenio == amigo && linea[i] == '|') {
            i++;
            while(linea[i] != '\0') {
                string alb = "", foto = "", fecha = "", tam = "", ruta = "", likesStr = "";

                while(linea[i] != '~' && linea[i] != '\0') {
                    alb += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '~' && linea[i] != '\0') {
                    foto += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '~' && linea[i] != '\0') {
                    fecha += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '~' && linea[i] != '\0') {
                    tam += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '~' && linea[i] != '\0') {
                    ruta += linea[i++];
                    iteraciones++;
                }
                if(linea[i] == '~') i++;

                while(linea[i] != '^' && linea[i] != '\0') {
                    likesStr += linea[i++];
                    iteraciones++;
                }

                if (alb == albumElegido) {
                    if (numFotosAlbum >= maxFotos) {
                        int nuevoMax = maxFotos * 2;
                        string* tempRutas = new string[nuevoMax];
                        string* tempNombres = new string[nuevoMax];
                        string* tempFechas = new string[nuevoMax];
                        string* tempTams = new string[nuevoMax];
                        int* tempLikes = new int[nuevoMax];
                        memoria += (sizeof(string) * nuevoMax * 4) + (sizeof(int) * nuevoMax);

                        for(int k = 0; k < numFotosAlbum; k++) {
                            tempRutas[k] = rutasFotos[k];
                            tempNombres[k] = nombresFotos[k];
                            tempFechas[k] = fechasFotos[k];
                            tempTams[k] = tamFotos[k];
                            tempLikes[k] = likesFotos[k];
                            iteraciones++;
                        }

                        delete[] rutasFotos;
                        delete[] nombresFotos;
                        delete[] fechasFotos;
                        delete[] tamFotos;
                        delete[] likesFotos;
                        rutasFotos = tempRutas;
                        nombresFotos = tempNombres;
                        fechasFotos = tempFechas;
                        tamFotos = tempTams;
                        likesFotos = tempLikes;
                        maxFotos = nuevoMax;
                    }

                    rutasFotos[numFotosAlbum] = ruta;
                    nombresFotos[numFotosAlbum] = foto;
                    fechasFotos[numFotosAlbum] = fecha;
                    tamFotos[numFotosAlbum] = tam;

                    int likes = 0;
                    for(int j = 0; likesStr[j] != '\0'; j++) {
                        likes = likes * 10 + (likesStr[j] - '0');
                        iteraciones++;
                    }
                    likesFotos[numFotosAlbum] = likes;

                    numFotosAlbum++;
                }
                if(linea[i] == '^') i++;
            }
            break;
        }
    }
    archFotos.close();

    if (numFotosAlbum == 0) {
        cout << "Este album esta vacio." << endl;
        delete[] rutasFotos;
        delete[] nombresFotos;
        delete[] fechasFotos;
        delete[] tamFotos;
        delete[] likesFotos;
        return;
    }

    int indiceActual = 0;
    int opcionCarrusel = 0;
    bool likesModificados = false;

    do {
        string fCruda = fechasFotos[indiceActual];
        string fVisual = "";
        for (int m = 0; fCruda[m] != '\0'; m++) {
            iteraciones++;
            fVisual += fCruda[m];
            if (m == 3 || m == 5) {
                fVisual += '/';
            }
        }
        memoria += fVisual.length();

        cout << "\n===============================" << endl;
        cout << "FOTO " << (indiceActual + 1) << " DE " << numFotosAlbum << endl;
        cout << "Nombre: " << nombresFotos[indiceActual] << endl;
        cout << "Fecha : " << fVisual << "  |  Tamano: " << tamFotos[indiceActual] << endl;
        cout << "Ruta  : " << rutasFotos[indiceActual] << endl;
        cout << "Likes : " << likesFotos[indiceActual] << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Siguiente foto" << endl;
        cout << "2. Foto previa" << endl;
        cout << "3. Dar Like" << endl;
        cout << "4. Quitar Like" << endl;
        cout << "5. Salir del album" << endl;
        cout << "Opcion: ";
        cin >> opcionCarrusel;
        cin.ignore();

        switch (opcionCarrusel) {
        case 1:
            indiceActual = (indiceActual + 1) % numFotosAlbum;
            iteraciones++;
            break;
        case 2:
            indiceActual = (indiceActual - 1 + numFotosAlbum) % numFotosAlbum;
            iteraciones++;
            break;
        case 3:
            likesFotos[indiceActual]++;
            likesModificados = true;
            cout << "Le diste Like a esta foto!" << endl;
            break;
        case 4:
            if (likesFotos[indiceActual] > 0) {
                likesFotos[indiceActual]--;
                likesModificados = true;
                cout << "Le quitaste el Like a esta foto." << endl;
            }
            else {
                cout << "Esta foto ya tiene 0 likes, no puedes quitar mas." << endl;
            }
            break;
        case 5:
            cout << "Saliendo del carrusel..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (opcionCarrusel != 5);

    if (likesModificados) {
        ifstream archivoLeer("fotos.txt");
        ofstream archivoTemp("temp_fotos.txt");

        while (getline(archivoLeer, linea)) {
            iteraciones++;
            string duenio = "";
            int i = 0;
            while(linea[i] != '|' && linea[i] != '\0') {
                duenio += linea[i++];
                iteraciones++;
            }

            if (duenio == amigo) {
                archivoTemp << duenio << "|";
                i++;
                bool primeraFoto = true;

                while(linea[i] != '\0') {
                    string p_alb = "", p_foto = "", p_fecha = "", p_tam = "", p_ruta = "", p_likes = "";

                    while(linea[i] != '~' && linea[i] != '\0') { p_alb += linea[i++]; iteraciones++; }
                    if(linea[i] == '~') i++;

                    while(linea[i] != '~' && linea[i] != '\0') { p_foto += linea[i++]; iteraciones++; }
                    if(linea[i] == '~') i++;

                    while(linea[i] != '~' && linea[i] != '\0') { p_fecha += linea[i++]; iteraciones++; }
                    if(linea[i] == '~') i++;

                    while(linea[i] != '~' && linea[i] != '\0') { p_tam += linea[i++]; iteraciones++; }
                    if(linea[i] == '~') i++;

                    while(linea[i] != '~' && linea[i] != '\0') { p_ruta += linea[i++]; iteraciones++; }
                    if(linea[i] == '~') i++;

                    while(linea[i] != '^' && linea[i] != '\0') { p_likes += linea[i++]; iteraciones++; }

                    if (!primeraFoto) archivoTemp << "^";
                    primeraFoto = false;

                    int likeAImprimir = -1;
                    if (p_alb == albumElegido) {
                        for(int j = 0; j < numFotosAlbum; j++) {
                            if (nombresFotos[j] == p_foto) {
                                likeAImprimir = likesFotos[j];
                                break;
                            }
                        }
                    }

                    archivoTemp << p_alb << "~" << p_foto << "~" << p_fecha << "~" << p_tam << "~" << p_ruta << "~";

                    if (likeAImprimir != -1) {
                        archivoTemp << likeAImprimir;
                    }
                    else {
                        archivoTemp << p_likes;
                    }

                    if(linea[i] == '^') i++;
                }
                archivoTemp << "\n";
            }
            else {
                archivoTemp << linea << "\n";
            }
        }
        archivoLeer.close();
        archivoTemp.close();
        remove("fotos.txt");
        rename("temp_fotos.txt", "fotos.txt");
    }

    delete[] rutasFotos;
    delete[] nombresFotos;
    delete[] fechasFotos;
    delete[] tamFotos;
    delete[] likesFotos;
}

void GestorAmistades::mostrarRuletaFotos(const string& usuarioActivo, int& iteraciones, int& memoria) {
    int maxAmigos = 50;
    string* misAmigos = new string[maxAmigos];
    int* comunes = new int[maxAmigos];
    int numMisAmigos = 0;
    memoria += (sizeof(string) * maxAmigos) + (sizeof(int) * maxAmigos);

    ifstream archivo("amigos.txt");
    string linea;
    while (getline(archivo, linea)) {
        iteraciones++;
        string duenio = "";
        int i = 0;
        while (linea[i] != '|' && linea[i] != '\0') {
            duenio += linea[i++];
            iteraciones++;
        }

        if (duenio == usuarioActivo && linea[i] == '|') {
            i++;
            while (linea[i] != '\0') {
                string amigo = "";
                while (linea[i] != '/' && linea[i] != '\0') {
                    amigo += linea[i++];
                    iteraciones++;
                }
                if (amigo != "") {
                    misAmigos[numMisAmigos] = amigo;
                    comunes[numMisAmigos] = 0;
                    numMisAmigos++;
                    memoria += amigo.length();
                }
                if (linea[i] == '/') i++;
            }
            break;
        }
    }
    archivo.close();

    if (numMisAmigos == 0) {
        cout << "\nNo tienes amigos aun para mostrar fotos destacadas." << endl;
        delete[] misAmigos;
        delete[] comunes;
        return;
    }

    archivo.open("amigos.txt");
    while (getline(archivo, linea)) {
        iteraciones++;
        string duenio = "";
        int i = 0;
        while (linea[i] != '|' && linea[i] != '\0') duenio += linea[i++];

        if (linea[i] == '|') {
            i++;
            int indexAmigo = -1;
            for (int k = 0; k < numMisAmigos; k++) {
                if (misAmigos[k] == duenio) {
                    indexAmigo = k;
                    break;
                }
            }

            if (indexAmigo != -1) {
                while (linea[i] != '\0') {
                    string amigoDeAmigo = "";
                    while (linea[i] != '/' && linea[i] != '\0') amigoDeAmigo += linea[i++];

                    if (amigoDeAmigo != "" && amigoDeAmigo != usuarioActivo) {
                        for (int k = 0; k < numMisAmigos; k++) {
                            if (misAmigos[k] == amigoDeAmigo) {
                                comunes[indexAmigo]++;
                                break;
                            }
                        }
                    }
                    if (linea[i] == '/') i++;
                }
            }
        }
    }
    archivo.close();

    int* pesos = new int[numMisAmigos];
    memoria += sizeof(int) * numMisAmigos;

    for (int i = 0; i < numMisAmigos; i++) {
        iteraciones++;
        if (comunes[i] <= 10) pesos[i] = 10;
        else if (comunes[i] <= 20) pesos[i] = 25;
        else pesos[i] = 35;
    }

    int cantidadAMostrar = (numMisAmigos < 3) ? numMisAmigos : 3;
    srand(time(0));
    int opcionRuleta = 0;

    do {
        cout << "\n=============================================" << endl;
        cout << "     FOTOS DESTACADAS DE TUS AMIGOS          " << endl;
        cout << "=============================================" << endl;

        bool* mostradosEnEsteGiro = new bool[numMisAmigos];
        int pesoTotalGiro = 0;
        memoria += sizeof(bool) * numMisAmigos;

        for(int i = 0; i < numMisAmigos; i++) {
            mostradosEnEsteGiro[i] = false;
            pesoTotalGiro += pesos[i];
            iteraciones++;
        }

        for (int k = 0; k < cantidadAMostrar; k++) {
            if (pesoTotalGiro <= 0) break;

            int randomVal = rand() % pesoTotalGiro;
            int acumulado = 0;

            for (int i = 0; i < numMisAmigos; i++) {
                iteraciones++;
                if (!mostradosEnEsteGiro[i]) {
                    acumulado += pesos[i];
                    if (randomVal < acumulado) {
                        mostradosEnEsteGiro[i] = true;
                        pesoTotalGiro -= pesos[i];

                        string rutaFoto = "Sin foto";
                        ifstream archInfo("informacion.txt");
                        string lineaInfo;
                        while(getline(archInfo, lineaInfo)) {
                            iteraciones++;
                            int idx = 0;
                            string dInfo = "";
                            while(lineaInfo[idx] != '|' && lineaInfo[idx] != '\0') {
                                dInfo += lineaInfo[idx++];
                                iteraciones++;
                            }

                            if(dInfo == misAmigos[i] && lineaInfo[idx] == '|') {
                                idx++;
                                string tempStr = "";
                                while(lineaInfo[idx] != '~' && lineaInfo[idx] != '\0') {
                                    idx++;
                                    iteraciones++;
                                }
                                if(lineaInfo[idx] == '~') idx++;
                                while(lineaInfo[idx] != '~' && lineaInfo[idx] != '\0') {
                                    idx++;
                                    iteraciones++;
                                }
                                if(lineaInfo[idx] == '~') idx++;
                                while(lineaInfo[idx] != '~' && lineaInfo[idx] != '\0') {
                                    tempStr += lineaInfo[idx++];
                                    iteraciones++;
                                }
                                rutaFoto = tempStr;
                                memoria += rutaFoto.length();
                                break;
                            }
                        }
                        archInfo.close();

                        cout << "    " << misAmigos[i] << endl;
                        cout << "    Foto: " << rutaFoto << endl;
                        cout << "    Amigos en comun: " << comunes[i] << endl;
                        cout << "---------------------------------------------" << endl;
                        break;
                    }
                }
            }
        }

        delete[] mostradosEnEsteGiro;

        if (numMisAmigos > 3) {
            cout << "\n1. Actualizar por otro grupo de fotos" << endl;
            cout << "2. Continuar al menu principal" << endl;
            cout << "Opcion: ";
            cin >> opcionRuleta;
            cin.ignore();
        }
        else {
            cout << "\n(Mostrando a todos tus amigos actuales)" << endl;
            opcionRuleta = 2;
        }

    } while (opcionRuleta == 1);

    delete[] misAmigos;
    delete[] comunes;
    delete[] pesos;
}