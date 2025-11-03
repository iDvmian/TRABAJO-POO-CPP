#ifndef CLASES_H
#define CLASES_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

class Asignatura;

// Excepciones 
struct CupoLlenoError : public runtime_error { 
    using runtime_error::runtime_error; 
};
struct InscripcionDuplicadaError : public runtime_error { 
    using runtime_error::runtime_error; 
};
struct NotaInvalidaError : public runtime_error {
     using runtime_error::runtime_error; 
    };

// Clase Persona abtracat y padre
class Persona {
private:
    string nombre;
    string rut;
    string correo;
public:
    Persona(string n, string r, string c) : nombre(n), rut(r), correo(c) {}
    virtual ~Persona() {}

    string getNombre() const;
    string getRut() const;
    string getCorreo() const;
    virtual void mostrar_info() const = 0;
};

// Clase Profesor
class Profesor : public Persona {
private:
    vector<Asignatura*> asignaturas;
public:
    Profesor(string n, string r, string c) : Persona(n, r, c) {}
    void agregarAsignatura(Asignatura* a);
    void listarAsignaturas() const;
    void mostrar_info() const override;
};

// Clase Estudiante
class Estudiante : public Persona {
private:
    vector<Asignatura*> inscripciones;
public:
    Estudiante(string n, string r, string c) : Persona(n, r, c) {}
    void inscribir(Asignatura* a);
    vector<Asignatura*> getInscripciones() const;
    int operator()(Asignatura& a);
    double operator+();
    void mostrar_info() const override;
};

// Clase Asignatura
class Asignatura {
private:
    string nombre;
    string codigo;
    string abreviado;
    int cupoMaximo;
    Profesor* profesor;
    vector<Estudiante*> estudiantes;
    vector<vector<int>> notas;
public:
    Asignatura(string n, string c, string ab, int cupo)
        : nombre(n), codigo(c), abreviado(ab), cupoMaximo(cupo), profesor(nullptr) {}

    string getNombre() const;
    string getCodigo() const;
    string getAbreviado() const;
    int getCupoMaximo() const;
    int getCuposDisponibles() const;
    Profesor* getProfesor() const;
    vector<Estudiante*> getEstudiantes() const;

    void asignarProfesor(Profesor* p);
    void inscribirEstudiante(Estudiante* e);
    void agregarNota(Estudiante* e, int nota);
    int calcularPromedio(Estudiante* e);
};

// Clase Carrera
class Carrera {
private:
    string nombre;
    vector<Asignatura*> asignaturas;
public:
    Carrera(string n) : nombre(n) {}
    string getNombre() const;
    void agregarAsignatura(Asignatura* a);
    vector<Asignatura*> getAsignaturas() const;
    void mostrarAsignaturas() const;
};

#endif
