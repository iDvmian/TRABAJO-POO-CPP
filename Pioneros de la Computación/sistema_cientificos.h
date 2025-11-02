#ifndef SISTEMA_CIENTIFICOS_H
#define SISTEMA_CIENTIFICOS_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <algorithm>

using namespace std;

// =========================================================
//                  MANEJO DE EXCEPCIONES
// =========================================================

class CientificoYaAsociadoError : public runtime_error {
public:
    CientificoYaAsociadoError(const string& cientifico_nombre, const string& proyecto_nombre);
};

class ProyectoNoEncontradoError : public runtime_error {
public:
    ProyectoNoEncontradoError(const string& nombre_proyecto, const string& institucion_nombre);
};

// =========================================================
//                   DECLARACIONES ADELANTADAS
// =========================================================

class Proyecto;
class Institucion;

// =========================================================
//                     CLASE CIENTIFICO (ABSTRACTA)
// =========================================================

class Cientifico {
private:
    // Encapsulamiento
    string nombre_;
    string pais_;
    string campo_estudio_;
    vector<Proyecto*> proyectos_asociados_; // Asociación

public:
    Cientifico(const string& nombre, const string& pais, const string& campo_estudio);
    virtual ~Cientifico() = default;

    // Getters
    string get_nombre() const { return nombre_; }
    string get_pais() const { return pais_; }
    
    // Método virtual puro
    virtual string get_clase() const = 0; 
    
    void agregar_proyecto(Proyecto* proyecto);

    // Polimorfismo: Sobrescritura de método (Función virtual pura)
    virtual string contribucion() const = 0;

    // Polimorfismo: Sobrescritura de método (Función virtual con implementación base)
    virtual string resumen() const;

    // Polimorfismo: Sobrecarga de Operador: operator<< 
    friend ostream& operator<<(ostream& os, const Cientifico& c);
};

// =========================================================
//                 CLASES HEREDADAS (SUBCLASES)
// =========================================================

class Matematico : public Cientifico {
private:
    string teorema_famoso_;
public:
    Matematico(const string& nombre, const string& pais, const string& campo_estudio, const string& teorema_famoso);

    string get_clase() const override { return "Matematico"; }

    string contribucion() const override;
    string resumen() const override;

    // Polimorfismo: Sobrecarga de Método 1
    string calcular_impacto() const;

    // Polimorfismo: Sobrecarga de Método 2
    string calcular_impacto(double factor_historico) const;
};

class Ingeniero : public Cientifico {
private:
    string diseno_clave_;
public:
    Ingeniero(const string& nombre, const string& pais, const string& campo_estudio, const string& diseno_clave);

    string get_clase() const override { return "Ingeniero"; }

    string contribucion() const override;
    string resumen() const override;
};

class Criptografo : public Cientifico {
private:
    string logro_militar_;
public:
    Criptografo(const string& nombre, const string& pais, const string& campo_estudio, const string& logro_militar);

    string get_clase() const override { return "Criptografo"; }

    string contribucion() const override;
    string resumen() const override;
};


// =========================================================
//                       CLASE PROYECTO
// =========================================================

class Proyecto {
private:
    string nombre_;
    int anio_;
    set<Cientifico*> cientificos_; // Agregación
    Institucion* institucion_;     // Asociación

public:
    Proyecto(const string& nombre, int anio, Institucion* institucion);

    // Getters
    string get_nombre() const { return nombre_; }
    int get_anio() const { return anio_; }
    const set<Cientifico*>& get_cientificos() const { return cientificos_; }

    void agregar_cientifico(Cientifico* cientifico);

    void listar_cientificos_involucrados() const;

    Cientifico* buscar_cientifico_por_nombre(const string& nombre) const;
};


// =========================================================
//                      CLASE INSTITUCION
// =========================================================

class Institucion {
private:
    string nombre_;
    string pais_;
    string descripcion_;
    // Composición: unique_ptr para gestionar la vida de los proyectos
    vector<unique_ptr<Proyecto>> proyectos_; 

public:
    Institucion(const string& nombre, const string& pais, const string& descripcion);
    ~Institucion() = default; // La destrucción de unique_ptr asegura la Composición

    string get_nombre() const { return nombre_; }

    void agregar_proyecto(unique_ptr<Proyecto> proyecto);

    // Polimorfismo: Sobrecarga de Operador: operator+=
    void operator+=(unique_ptr<Proyecto> proyecto);

    Proyecto* buscar_proyecto_por_nombre(const string& nombre) const;

    void listar_proyectos() const;

    void listar_cientificos_asociados() const;
};

#endif // SISTEMA_CIENTIFICOS_H