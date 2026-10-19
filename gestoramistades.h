#ifndef GESTORAMISTADES_H
#define GESTORAMISTADES_H

#include <string>
using namespace std;

class GestorAmistades
{
private:
    bool existeUsuario(const char* nombreUsuario, int& iteraciones);
    bool existeSolicitud(const char* emisor, const char* receptor, int& iteraciones);
    void guardarElemento(const char* nombreArchivo, const char* duenio, const char* elemento, int& iteraciones);
    void eliminarSolicitudPendiente(const char* emisor, const char* receptor, int& iteraciones);
    void redimensionarLinea(char*& buffer, int& capacidadActual, int& iteraciones);
    void sugerirAmigos(const string& usuarioActivo, int k, int& iteraciones, int& memoria);
    void visitarPerfilAmigo(const string& usuarioActivo, int& iteraciones, int& memoria);

public:
    GestorAmistades();
    bool sonAmigos(const char* usuario1, const char* usuario2, int& iteraciones); 
    void mostrarRuletaFotos(const string& usuarioActivo, int& iteraciones, int& memoria);
    void administrar(const char* usuarioActivo, int& iteracionesGlobales, int& memoriaGlobal);
};

#endif // GESTORAMISTADES_H
