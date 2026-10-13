#ifndef PLATAFORMA_H
#define PLATAFORMA_H

class Plataforma
{
private:
    char usuarioActivo[25];
    bool sesionIniciada;

public:
    Plataforma();
    void iniciar();
    bool procesarInicioSesion(int& iteraciones, int& memoriaEnUso);
    void menuInterno();
    ~Plataforma();
};

#endif // PLATAFORMA_H
