#ifndef GESTORMENSAJES_H
#define GESTORMENSAJES_H

#include "GestorAmistades.h"
#include <string>

using namespace std;

class GestorMensajes
{

private:
    string obtenerFechaActual();

    int convertirFechaEntero(const string& fechaStr, int& iteraciones);
public:
    GestorMensajes();
    // a. Enviar mensaje (Max 512 caracteres)
    void enviarMensaje(const std::string& emisor, const std::string& receptor, const std::string& mensaje, int& iteraciones, int& memoria);

    // b. Leer nuevos mensajes (Muestra los no leidos y cambia estado de 0 a 1)
    void leerNuevosMensajes(const std::string& usuarioActivo, int& iteraciones, int& memoria);

    // c. Buscar mensajes por rango de fecha
    void buscarPorRango(const std::string& usuarioActivo, int fechaInicio, int fechaFin, int& iteraciones, int& memoria);

    // Menu del modulo
    void administrar(const std::string& usuarioActivo, GestorAmistades& gestorAmigos, int& iteracionesGlobales, int& memoriaGlobal);
};

#endif // GESTORMENSAJES_H
