#ifndef CLASES_H
#define CLASES_H
using namespace std;


class Persona{
    public:
    string nombre;
    int rut;
    string correo;

// Persona con atributos comunes 
// como nombre, RUT y correo, y métodos apropiados. 
    virtual void metodo() const = 0;
    virtual void mostrarInfo() const = 0;
    virtual ~Persona(){}
};

//  implementando sus propias versiones del método mostrar_info() 
// y comportamientos particulares.
class Profesor : public Persona {
    public:


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