#ifndef CLASES_H
#define CLASES_H
using namespace std;


class Persona{
    public:
    string nombre;
    string rut;
    string correo;

// Persona con atributos comunes 
// como nombre, RUT y correo, y métodos apropiados.
    Persona(string n, string r, string c) :  nombre(n), rut(r), correo(c){}
    virtual ~Persona(){} 
    virtual void metodo() const = 0;
    virtual void mostrarInfo() const = 0;

    
};

//  implementando sus propias versiones del método mostrar_info() 
// y comportamientos particulares.
class Profesor : public Persona {
    public:
    Profesor (string n, string r, string c){}


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