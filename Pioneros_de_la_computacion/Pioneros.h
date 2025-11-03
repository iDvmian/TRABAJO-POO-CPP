#ifndef PIONEROS_H
#define PIONEROS_H

#include <iostream>
#include <vector>
#include <stdexcept> 
#include <string>

using namespace std;

class Proyecto; // Declaracion adelantada

// Excepciones Personalizadas
struct CientificoDuplicadoError : public runtime_error { 
    using runtime_error::runtime_error; 
};

// Clase Abstracta
class Cientifico {
private:
    string nombre;
    string pais;
    string campo_estudio;
    vector<Proyecto*> proyectos; // Asociacion

public:
    Cientifico(string n, string p, string c) : nombre(n), pais(p), campo_estudio(c) {}
    virtual ~Cientifico() {} 

    string getNombre() const;
    void agregarProyecto(Proyecto* p);

    virtual string contribucion() const = 0; // Virtual pura
    virtual string resumen() const;

    friend ostream& operator<<(ostream& os, const Cientifico& c);
};

// Clases Heredadas
class Matematico : public Cientifico {
private:
    string teorema_clave;
public:
    Matematico(string n, string p, string c, string t) 
        : Cientifico(n, p, c), teorema_clave(t) {}

    string contribucion() const override;
    string resumen() const override;
    
    // Sobrecarga de Metodo
    void mostrarLogros() const;
    void mostrarLogros(bool con_detalle) const;
};

class Ingeniero : public Cientifico {
private:
    string diseno_clave;
public:
    Ingeniero(string n, string p, string c, string d) 
        : Cientifico(n, p, c), diseno_clave(d) {}

    string contribucion() const override;
    string resumen() const override;

    // Sobrecarga de Metodo
    void mostrarLogros() const;
    void mostrarLogros(bool con_detalle) const;
};

class Criptografo : public Cientifico {
private:
    string logro_clave;
public:
    Criptografo(string n, string p, string c, string l) 
        : Cientifico(n, p, c), logro_clave(l) {}

    string contribucion() const override;
    string resumen() const override;

    // Sobrecarga de Metodo
    void mostrarLogros() const;
    void mostrarLogros(bool con_detalle) const;
};


class Proyecto {
private:
    string nombre;
    int anio;
    vector<Cientifico*> cientificos; // Agregacion

public:
    Proyecto(string n, int a) : nombre(n), anio(a) {}

    string getNombre() const;
    vector<Cientifico*> getCientificos() const; // Getter para los cientificos
    
    void agregarCientifico(Cientifico* c);
    void listarCientificos() const;
};


class Institucion {
private:
    string nombre;
    vector<Proyecto*> proyectos; // Composicion

public:
    Institucion(string n) : nombre(n) {}

    void agregarProyecto(Proyecto* p);

    void listarProyectos() const;
    void listarCientificosGlobales() const;
};

#endif