#include "GestorMensajes.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

GestorMensajes::GestorMensajes() {}

string GestorMensajes::obtenerFechaActual() {
    time_t tiempoAhora = time(0);
    tm* tiempoLocal = localtime(&tiempoAhora);

    int anio = 1900 + tiempoLocal->tm_year;
    int mes = 1 + tiempoLocal->tm_mon;
    int dia = tiempoLocal->tm_mday;

    string fecha = to_string(anio);
    if (mes < 10) fecha += "0";
    fecha += to_string(mes);

    if (dia < 10) fecha += "0";
    fecha += to_string(dia);

    return fecha;
}

int GestorMensajes::convertirFechaEntero(const string& fechaStr, int& iteraciones) {
    int valor = 0;
    for (int i = 0; fechaStr[i] != '\0'; i++) {
        iteraciones++;
        if (fechaStr[i] >= '0' && fechaStr[i] <= '9') {
            valor = (valor * 10) + (fechaStr[i] - '0');
        }
    }
    return valor;
}

void GestorMensajes::enviarMensaje(const string& emisor, const string& receptor, const string& mensaje, int& iteraciones, int& memoria) {
    string fecha = obtenerFechaActual();

    string nuevoBloque = emisor + "~" + fecha + "~0~" + mensaje + "^";
    memoria += emisor.length() + receptor.length() + mensaje.length() + nuevoBloque.length();

    ifstream archivoLeer("mensajes.txt");
    ofstream archivoTemp("temp.txt");

    bool buzonEncontrado = false;
    string linea;

    if (archivoLeer.is_open()) {
        while (getline(archivoLeer, linea)) {
            iteraciones++;

            if (!buzonEncontrado) {
                string duenioFila = "";
                int i = 0;
                while (linea[i] != '|' && linea[i] != '\0') {
                    iteraciones++;
                    duenioFila += linea[i];
                    i++;
                }

                if (duenioFila == receptor) {
                    linea += nuevoBloque;
                    buzonEncontrado = true;
                }
            }
            archivoTemp << linea << "\n";
        }
        archivoLeer.close();
    }

    if (!buzonEncontrado) {
        string nuevaLinea = receptor + "|" + nuevoBloque;
        archivoTemp << nuevaLinea << "\n";
        memoria += nuevaLinea.length();
    }

    archivoTemp.close();

    remove("mensajes.txt");
    rename("temp.txt", "mensajes.txt");
}

void GestorMensajes::leerNuevosMensajes(const string& usuarioActivo, int& iteraciones, int& memoria) {
    ifstream archivoLeer("mensajes.txt");
    ofstream archivoTemp("temp.txt");

    if (!archivoLeer.is_open()) {
        cout << "\nTu bandeja de entrada esta vacia." << endl;
        return;
    }

    string linea;
    bool mensajesEncontrados = false;
    int cantidadNuevos = 0;

    cout << "\n--- MENSAJES NUEVOS ---" << endl;

    while (getline(archivoLeer, linea)) {
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
                string emisor = "", fecha = "", estado = "", contenido = "";

                while (linea[i] != '~' && linea[i] != '\0') {
                    emisor += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                while (linea[i] != '~' && linea[i] != '\0') {
                    fecha += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                int posicionEstado = i;
                while (linea[i] != '~' && linea[i] != '\0') {
                    estado += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                while (linea[i] != '^' && linea[i] != '\0') {
                    contenido += linea[i++]; iteraciones++;
                }
                if (linea[i] == '^') i++;

                if (estado == "0") {
                    cout << "Fecha: " << fecha << " | De: " << emisor << "\n";
                    cout << "Mensaje: " << contenido << "\n";
                    cout << "---------------------------" << endl;

                    linea[posicionEstado] = '1';
                    cantidadNuevos++;
                    mensajesEncontrados = true;
                }
            }
        }
        archivoTemp << linea << "\n";
    }

    archivoLeer.close();
    archivoTemp.close();

    remove("mensajes.txt");
    rename("temp.txt", "mensajes.txt");

    if (!mensajesEncontrados) {
        cout << "No tienes mensajes nuevos sin leer." << endl;
    }
    else {
        cout << "Has leido " << cantidadNuevos << " mensajes nuevos." << endl;
    }
}

void GestorMensajes::buscarPorRango(const string& usuarioActivo, int fechaInicio, int fechaFin, int& iteraciones, int& memoria) {
    ifstream archivoLeer("mensajes.txt");
    if (!archivoLeer.is_open()) {
        cout << "\nNo hay historial de mensajes." << endl;
        return;
    }

    string linea;
    bool mensajesEncontrados = false;

    cout << "\n--- HISTORIAL DE MENSAJES (" << fechaInicio << " - " << fechaFin << ") ---" << endl;

    while (getline(archivoLeer, linea)) {
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
                string emisor = "", fechaStr = "", estado = "", contenido = "";

                while (linea[i] != '~' && linea[i] != '\0') {
                    emisor += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                while (linea[i] != '~' && linea[i] != '\0') {
                    fechaStr += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                while (linea[i] != '~' && linea[i] != '\0') {
                    estado += linea[i++]; iteraciones++;
                }
                if (linea[i] == '~') i++;

                while (linea[i] != '^' && linea[i] != '\0') {
                    contenido += linea[i++]; iteraciones++;
                }
                if (linea[i] == '^') i++;

                int fechaMensaje = convertirFechaEntero(fechaStr, iteraciones);

                if (fechaMensaje >= fechaInicio && fechaMensaje <= fechaFin) {
                    string txtEstado = (estado == "1") ? "Leido" : "No leido";
                    cout << "[" << fechaStr << "] " << emisor << " (" << txtEstado << "):\n" << contenido << "\n";
                    cout << "---------------------------" << endl;
                    mensajesEncontrados = true;
                }
            }
            break;
        }
    }

    archivoLeer.close();

    if (!mensajesEncontrados) {
        cout << "No se encontraron mensajes en ese rango de fechas." << endl;
    }
}

void GestorMensajes::administrar(const string& usuarioActivo, GestorAmistades& gestorAmigos, int& iteracionesGlobales, int& memoriaGlobal) {
    int opcion = 0;
    do {
        cout << "\n--- GESTOR DE MENSAJES ---" << endl;
        cout << "1. Enviar mensaje" << endl;
        cout << "2. Leer nuevos mensajes" << endl;
        cout << "3. Buscar mensajes por fecha" << endl;
        cout << "4. Volver" << endl;
        cout << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;
        cin.ignore();

        int iteraciones = 0;
        int memoria = 0;

        switch (opcion) {
        case 1: {
            char usuarioDestino[25];
            cout << "Ingrese el usuario destino: ";
            cin.getline(usuarioDestino, 25);

            if (!gestorAmigos.sonAmigos(usuarioActivo.c_str(), usuarioDestino, iteraciones)) {
                cout << "No eres amigo de " << usuarioDestino << ". No puedes enviarle mensajes." << endl;
            }
            else {
                char mensajeBuffer[513];
                cout << "Mensaje (Max 512): ";
                cin.getline(mensajeBuffer, 513);

                enviarMensaje(usuarioActivo, string(usuarioDestino), string(mensajeBuffer), iteraciones, memoria);
                cout << "[EXITO] Mensaje enviado." << endl;

                cout << "Nota de consumo: Para esta funcionalidad se invoco el componente externo <ctime>." << endl;
            }
            break;
        }
        case 2:
            leerNuevosMensajes(usuarioActivo, iteraciones, memoria);
            break;
        case 3: {
            string strInicio, strFin;

            cout << "Ingrese fecha de inicio (Ej: 2026/10/01): ";
            getline(cin, strInicio);

            cout << "Ingrese fecha de fin (Ej: 2026/10/31): ";
            getline(cin, strFin);

            memoria += strInicio.length() + strFin.length();

            int fInicio = convertirFechaEntero(strInicio, iteraciones);
            int fFin = convertirFechaEntero(strFin, iteraciones);

            buscarPorRango(usuarioActivo, fInicio, fFin, iteraciones, memoria);
            break;
        }
        case 4:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

        iteracionesGlobales += iteraciones;
        memoriaGlobal += memoria;
    } while (opcion != 4);
}