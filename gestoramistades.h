#ifndef GESTORAMISTADES_H
#define GESTORAMISTADES_H

class GestorAmistades
{
private:
    bool existeUsuario(const char* nombreUsuario, int& iteraciones);
    bool existeSolicitud(const char* emisor, const char* receptor, int& iteraciones);
    void guardarElemento(const char* nombreArchivo, const char* duenio, const char* elemento, int& iteraciones);
    void eliminarSolicitudPendiente(const char* emisor, const char* receptor, int& iteraciones);
    void redimensionarLinea(char*& buffer, int& capacidadActual, int& iteraciones);

public:
    GestorAmistades();
    bool sonAmigos(const char* usuario1, const char* usuario2, int& iteraciones);
    void administrar(const char* usuarioActivo, int& iteracionesGlobales, int& memoriaGlobal);
};

#endif // GESTORAMISTADES_H
