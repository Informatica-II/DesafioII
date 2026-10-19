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
    string formatearFechaVisual(const string& fechaCruda, int& iteraciones, int& memoria);
    void enviarMensaje(const string& emisor, const string& receptor, const string& mensaje, int& iteraciones, int& memoria);
    void leerNuevosMensajes(const string& usuarioActivo, int& iteraciones, int& memoria);
    void buscarPorRango(const string& usuarioActivo, int fechaInicio, int fechaFin, int& iteraciones, int& memoria);
public:
    GestorMensajes();
    void administrar(const string& usuarioActivo, GestorAmistades& gestorAmigos, int& iteracionesGlobales, int& memoriaGlobal);
};

#endif // GESTORMENSAJES_H
