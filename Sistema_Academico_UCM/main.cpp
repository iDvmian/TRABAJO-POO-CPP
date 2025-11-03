#include "Clases.h"
#include <iostream>
using namespace std;

// Persona
string Persona::getNombre() const { 
    return nombre;
 }
string Persona::getRut() const { 
    return rut; 
}
string Persona::getCorreo() const {
     return correo; 
    }

// Profesor
void Profesor::agregarAsignatura(Asignatura* a) { asignaturas.push_back(a); }

void Profesor::listarAsignaturas() const {
    cout << "Asignaturas dictadas por " << getNombre() << ":\n";
    for (auto a : asignaturas)
        cout << " - " << a->getNombre() << "\n";
}

void Profesor::mostrar_info() const {
    cout << "[Profesor] " << getNombre() << " | RUT: " << getRut()
         << " | Correo: " << getCorreo() << "\n";
}

// Estudiante
void Estudiante::inscribir(Asignatura* a) {
    a->inscribirEstudiante(this);
    inscripciones.push_back(a);
}

vector<Asignatura*> Estudiante::getInscripciones() const {
     return inscripciones;
     }

int Estudiante::operator()(Asignatura& a) { 
    return a.calcularPromedio(this);
 }

double Estudiante::operator+() {
    if (inscripciones.empty()) return 0;
    double suma = 0; int cont = 0;
    for (auto a : inscripciones) {
        int p = a->calcularPromedio(this);
        if (p > 0) { suma += p; cont++; }
    }
    return cont == 0 ? 0 : suma / cont;
}

void Estudiante::mostrar_info() const {
    cout << "Estudiante " << getNombre() << " | RUT: " << getRut()
         << " | Correo: " << getCorreo() << "\n";
    if (!inscripciones.empty()) {
        cout << "  Inscrito en:\n";
        for (auto a : inscripciones)
            cout << "   - " << a->getNombre() << "\n";
    }
}

// Asignatura
string Asignatura::getNombre() const {
     return nombre;
     }
string Asignatura::getCodigo() const {
    return codigo; 
}
string Asignatura::getAbreviado() const {
     return abreviado;
     }
int Asignatura::getCupoMaximo() const {
     return cupoMaximo; 
    }
int Asignatura::getCuposDisponibles() const {
     return cupoMaximo - (int)estudiantes.size(); 
    }
Profesor* Asignatura::getProfesor() const {
     return profesor; 
    }
vector<Estudiante*> Asignatura::getEstudiantes() const {
     return estudiantes; 
    }

void Asignatura::asignarProfesor(Profesor* p) {
    profesor = p;
    p->agregarAsignatura(this);
}

void Asignatura::inscribirEstudiante(Estudiante* e) {
    for (auto est : estudiantes)
        if (est == e) throw InscripcionDuplicadaError("Ya inscrito en " + nombre);
    if (getCuposDisponibles() <= 0)
        throw CupoLlenoError("Cupo lleno en " + nombre);
    estudiantes.push_back(e);
    notas.push_back(vector<int>());
}

void Asignatura::agregarNota(Estudiante* e, int nota) {
    if (nota < 10 || nota > 70)
        throw NotaInvalidaError("Nota fuera de rango (10-70) en " + nombre);
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i] == e) {
            notas[i].push_back(nota);
            return;
        }
    }
    throw runtime_error("El estudiante no esta inscrito en " + nombre);
}

int Asignatura::calcularPromedio(Estudiante* e) {
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i] == e) {
            if (notas[i].empty()) return 0;
            int suma = 0;
            for (int n : notas[i]) suma += n;
            return suma / notas[i].size();
        }
    }
    return 0;
}

// Carrera
string Carrera::getNombre() const { 
    return nombre;
 }
void Carrera::agregarAsignatura(Asignatura* a) { 
    asignaturas.push_back(a); 
}
vector<Asignatura*> Carrera::getAsignaturas() const { 
    return asignaturas; 
}

void Carrera::mostrarAsignaturas() const {
    cout << "Carrera: " << nombre << "\n";
    for (auto a : asignaturas)
        cout << " - " << a->getNombre() << "\n";
}

// Main
int main() {
    Carrera carrera("Ingenieria Civil Informatica");

    Asignatura poo("Programacion Orientada a Objetos", "ICE234", "POO", 2);
    Asignatura bd("Bases de Datos", "ICE221", "BD", 2);
    Asignatura ed("Estructuras de Datos", "ICE222", "ESD", 2);

    carrera.agregarAsignatura(&poo);
    carrera.agregarAsignatura(&bd);
    carrera.agregarAsignatura(&ed);

    Profesor p1("Ana Soto", "11.111.111-1", "ana@ucm.cl");
    Profesor p2("Luis Perez", "22.222.222-2", "luis@ucm.cl");
    Profesor p3("Marta Diaz", "33.333.333-3", "marta@ucm.cl");

    poo.asignarProfesor(&p1);
    bd.asignarProfesor(&p2);
    ed.asignarProfesor(&p3);

    Estudiante e1("Dami", "44.444.444-4", "dami@ucm.cl");
    Estudiante e2("Fernando", "55.555.555-5", "fena@ucm.cl");
    Estudiante e3("Francisco", "66.666.666-6", "fran@ucm.cl");

    try { e1.inscribir(&poo); e1.inscribir(&bd); } catch (const exception& ex) { cout << "[Error] " << ex.what() << "\n"; }
    try { e2.inscribir(&poo); e2.inscribir(&ed); } catch (const exception& ex) { cout << "[Error] " << ex.what() << "\n"; }
    try { e3.inscribir(&bd);  e3.inscribir(&ed); } catch (const exception& ex) { cout << "[Error] " << ex.what() << "\n"; }

    try {
        poo.agregarNota(&e1, 60); poo.agregarNota(&e1, 55);
        bd.agregarNota(&e1, 70); bd.agregarNota(&e1, 68);
        poo.agregarNota(&e2, 50); poo.agregarNota(&e2, 45);
        ed.agregarNota(&e2, 65); ed.agregarNota(&e2, 70);
        bd.agregarNota(&e3, 55); bd.agregarNota(&e3, 60);
        ed.agregarNota(&e3, 58); ed.agregarNota(&e3, 62);
    } catch (const exception& ex) { cout << "[Error Nota] " << ex.what() << "\n"; }

    cout << "\n-- INFORMACION DE ESTUDIANTES --\n";
    e1.mostrar_info(); e2.mostrar_info(); e3.mostrar_info();

    cout << "\n-- ASIGNATURAS POR PROFESOR --\n";
    p1.listarAsignaturas(); p2.listarAsignaturas(); p3.listarAsignaturas();

    cout << "\n-- PROMEDIOS --\n";
    cout << "Promedio general de " << e1.getNombre() << ": " << +e1 << "\n";
    cout << "Promedio general de " << e2.getNombre() << ": " << +e2 << "\n";
    cout << "Promedio general de " << e3.getNombre() << ": " << +e3 << "\n";

    cout << "\n-- LISTA DE ESTUDIANTES POR ASIGNATURA --\n";
    for (auto a : carrera.getAsignaturas()) {
        cout << "- " << a->getNombre() << " (" << a->getCuposDisponibles()
             << "/" << a->getCupoMaximo() << " cupos disponibles)\n";
        for (auto e : a->getEstudiantes())
            cout << "   * " << e->getNombre() << "\n";
    }

    return 0;
}
