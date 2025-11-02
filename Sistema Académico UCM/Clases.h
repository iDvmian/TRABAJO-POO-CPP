#ifndef CLASES_H
#define CLASES_H
#include <iostream>

using namespace std;


// Clase abstracata Persona y clase padre
class Persona{
    private:
    string nombre;
    string rut;
    string correo;

    public:
    Persona(string n, string r, string c) :  nombre(n), rut(r), correo(c){}
    virtual ~Persona(){}
    // Metodos
    virtual void mostrarInfo() const = 0;
    string getNombre() const { return nombre; }
    string getRut() const { return rut; }
    string getCorreo() const { return correo; }


    
};

//  implementando sus propias versiones del método mostrar_info() 
// y comportamientos particulares.
class Profesor : public Persona {
    public:
    Profesor (string n, string r, string c){}
    void mostrarInfo() const override;

};

class Estudiante: public Persona {
    public:

};



//  implementando sus propias versiones del método mostrar_info() 
// y comportamientos particulares.
class Asignatura{
    public:
    string nombre;
    string codigo;
    int cupoMaximo;
    string ProfeAcargo;
    //lista estudaintes;

};

class Carrera {
    public:
    string nombre;

    Carrera(string n) : nombre(n){}




};






#endif