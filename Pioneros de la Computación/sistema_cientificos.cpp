#include "sistema_cientificos.h"

// =========================================================
//                  MANEJO DE EXCEPCIONES
// =========================================================

CientificoYaAsociadoError::CientificoYaAsociadoError(const string& cientifico_nombre, const string& proyecto_nombre)
    : runtime_error("Error: El cientifico '" + cientifico_nombre + "' ya esta asociado al proyecto '" + proyecto_nombre + "'.") {}

ProyectoNoEncontradoError::ProyectoNoEncontradoError(const string& nombre_proyecto, const string& institucion_nombre)
    : runtime_error("Error: El proyecto '" + nombre_proyecto + "' no se encuentra en la institucion '" + institucion_nombre + "'.") {}

// =========================================================
//                     CLASE CIENTIFICO
// =========================================================

Cientifico::Cientifico(const string& nombre, const string& pais, const string& campo_estudio)
    : nombre_(nombre), pais_(pais), campo_estudio_(campo_estudio) {}

void Cientifico::agregar_proyecto(Proyecto* proyecto) {
    if (find(proyectos_asociados_.begin(), proyectos_asociados_.end(), proyecto) == proyectos_asociados_.end()) {
        proyectos_asociados_.push_back(proyecto);
    }
}

string Cientifico::resumen() const {
    string proy_str = "";
    for (const auto& p : proyectos_asociados_) {
        proy_str += p->get_nombre() + ", ";
    }
    if (!proy_str.empty()) proy_str.pop_back(); 
    if (!proy_str.empty()) proy_str.pop_back(); 

    return "**" + nombre_ + "** (" + get_clase() + ") de " + pais_ +
           ". Campo: " + campo_estudio_ + ". Proyectos: [" + (proy_str.empty() ? "N/A" : proy_str) + "].";
}

// Sobrecarga de Operador <<
ostream& operator<<(ostream& os, const Cientifico& c) {
    // Usamos el metodo get_clase() virtual para el polimorfismo
    return os << c.nombre_ << " | " << c.get_clase() << " | " << c.pais_; 
}

// =========================================================
//                 CLASES HEREDADAS (SUBCLASES)
// =========================================================

// Matematico
Matematico::Matematico(const string& nombre, const string& pais, const string& campo_estudio, const string& teorema_famoso)
    : Cientifico(nombre, pais, campo_estudio), teorema_famoso_(teorema_famoso) {}

string Matematico::contribucion() const {
    return "Su trabajo fundamental en matematicas, como su teorema sobre '" + teorema_famoso_ + "', "
           "sento las bases teoricas y logicas para los algoritmos y la programacion.";
}

string Matematico::resumen() const {
    return Cientifico::resumen() + " Teorema Famoso: " + teorema_famoso_ + ".";
}

string Matematico::calcular_impacto() const { // Sobrecarga 1
    return "Impacto Calculado (Teorico): Alto.";
}

string Matematico::calcular_impacto(double factor_historico) const { // Sobrecarga 2
    double impacto = 5.0 * factor_historico;
    return "Impacto Calculado (Factor " + to_string(factor_historico) + "): " + to_string(impacto) + " unidades de influencia.";
}

// Ingeniero
Ingeniero::Ingeniero(const string& nombre, const string& pais, const string& campo_estudio, const string& diseno_clave)
    : Cientifico(nombre, pais, campo_estudio), diseno_clave_(diseno_clave) {}

string Ingeniero::contribucion() const {
    return "Su contribucion radica en la arquitectura de hardware, siendo clave en el diseno de la **" + diseno_clave_ + "** ";
}

string Ingeniero::resumen() const {
    return Cientifico::resumen() + " Diseno Clave: " + diseno_clave_ + ".";
}

// Criptografo
Criptografo::Criptografo(const string& nombre, const string& pais, const string& campo_estudio, const string& logro_militar)
    : Cientifico(nombre, pais, campo_estudio), logro_militar_(logro_militar) {}

string Criptografo::contribucion() const {
    return "Pionero en la logica algoritmica y la decodificacion. "
           "Su mayor logro fue el descifrado de **" + logro_militar_ + "**, "
           "lo que acelero la guerra y sento las bases de la inteligencia artificial.";
}

string Criptografo::resumen() const {
    return Cientifico::resumen() + " Logro Clave: " + logro_militar_ + ".";
}

// =========================================================
//                       CLASE PROYECTO
// =========================================================

Proyecto::Proyecto(const string& nombre, int anio, Institucion* institucion)
    : nombre_(nombre), anio_(anio), institucion_(institucion) {}

void Proyecto::agregar_cientifico(Cientifico* cientifico) {
    if (cientificos_.count(cientifico)) {
        throw CientificoYaAsociadoError(cientifico->get_nombre(), nombre_);
    }
    
    // Agregacion
    cientificos_.insert(cientifico);
    // Asociacion
    cientifico->agregar_proyecto(this);
}

void Proyecto::listar_cientificos_involucrados() const {
    cout << "\nCientificos en **" << nombre_ << " (" << anio_ << ")**:" << endl;
    if (cientificos_.empty()) {
        cout << "No hay cientificos asignados aun." << endl;
        return;
    }
    for (const auto& cientifico : cientificos_) {
        cout << "- " << *cientifico << endl;
    }
}

Cientifico* Proyecto::buscar_cientifico_por_nombre(const string& nombre) const {
    for (const auto& cientifico : cientificos_) {
        if (cientifico->get_nombre() == nombre) {
            return cientifico;
        }
    }
    return nullptr;
}


// =========================================================
//                      CLASE INSTITUCION
// =========================================================

Institucion::Institucion(const string& nombre, const string& pais, const string& descripcion)
    : nombre_(nombre), pais_(pais), descripcion_(descripcion) {}

void Institucion::agregar_proyecto(unique_ptr<Proyecto> proyecto) {
    proyectos_.push_back(move(proyecto));
}

void Institucion::operator+=(unique_ptr<Proyecto> proyecto) {
    agregar_proyecto(move(proyecto));
}

Proyecto* Institucion::buscar_proyecto_por_nombre(const string& nombre) const {
    for (const auto& proyecto : proyectos_) {
        if (proyecto->get_nombre() == nombre) {
            return proyecto.get();
        }
    }
    throw ProyectoNoEncontradoError(nombre, nombre_);
}

void Institucion::listar_proyectos() const {
    cout << "\nProyectos en **" << nombre_ << " (" << proyectos_.size() << " en total) ---" << endl;
    for (const auto& proyecto : proyectos_) {
        cout << "- " << proyecto->get_nombre() << " (" << proyecto->get_anio() << ")" << endl;
    }
}

void Institucion::listar_cientificos_asociados() const {
    set<Cientifico*> cientificos_unicos;
    for (const auto& proyecto : proyectos_) {
        const auto& cientificos_proyecto = proyecto->get_cientificos();
        cientificos_unicos.insert(cientificos_proyecto.begin(), cientificos_proyecto.end());
    }

    cout << "\nCientificos Asociados a **" << nombre_ << "** (" << cientificos_unicos.size() << " unicos) ---" << endl;
    if (cientificos_unicos.empty()) {
        cout << "No hay cientificos asociados aun." << endl;
        return;
    }
    for (const auto& cientifico : cientificos_unicos) {
        cout << "- " << *cientifico << endl;
    }
}

// =========================================================
//                   BLOQUE PRINCIPAL (MAIN)
// =========================================================

int main() {
    cout << "========================================================" << endl;
    cout << "## Creacion de Entidades y Verificacion del Modelo POO" << endl;
    cout << "========================================================" << endl;

    // 3. Cientificos (Herencia)
    auto turing = make_unique<Criptografo>("Alan Turing", "Reino Unido", "Logica y Criptografia", "Maquina Enigma");
    auto lovelace = make_unique<Matematico>("Ada Lovelace", "Reino Unido", "Matematica Aplicada", "Numeros de Bernoulli");
    auto neumann = make_unique<Ingeniero>("John von Neumann", "Hungria/EE.UU.", "Arquitectura de Hardware", "Arquitectura Von Neumann");
    
    Cientifico* c_turing = turing.get();
    Cientifico* c_lovelace = lovelace.get();
    Cientifico* c_neumann = neumann.get();

    cout << "Cientificos Creados:" << endl;
    cout << "- " << *c_turing << endl;
    cout << "- " << *c_lovelace << endl;
    cout << "- " << *c_neumann << endl;

    cout << "\n--------------------------------------------------------" << endl;
    
    // 1. Institucion (Composicion)
    Institucion eniac_lab("ENIAC Lab", "EE.UU.", "Laboratorio de la Universidad de Pensilvania");
    cout << "Institucion Creada: " << eniac_lab.get_nombre() << endl;

    // 2. Proyectos (Composicion y Asociacion)
    auto eniac = make_unique<Proyecto>("ENIAC", 1945, &eniac_lab);
    auto bombe = make_unique<Proyecto>("Bombe", 1940, &eniac_lab);

    // Asignacion de Cientificos a Proyectos (Agregacion)
    try {
        eniac->agregar_cientifico(c_neumann);
        eniac->agregar_cientifico(c_lovelace);
        bombe->agregar_cientifico(c_turing);
        bombe->agregar_cientifico(c_lovelace); 

        cout << "Cientificos asignados a proyectos." << endl;

        // 4. Validacion y Errores: Intento de agregar el mismo cientifico dos veces
        cout << "\nVerificacion de Error (Manejo de Excepciones) ---" << endl;
        eniac->agregar_cientifico(c_neumann);

    } catch (const CientificoYaAsociadoError& e) {
        cout << "Excepcion Capturada: " << e.what() << endl;
    }

    // Transferir la propiedad de los proyectos a la institucion (Composicion final)
    eniac_lab += move(eniac);
    eniac_lab += move(bombe);
    
    cout << "\n========================================================" << endl;
    cout << "## Verificacion de Salidas y Polimorfismo" << endl;
    cout << "========================================================" << endl;

    // 5.c. Mostrar todos los proyectos de una institucion
    eniac_lab.listar_proyectos();
    
    // 5.a. Listar cientificos involucrados en cada proyecto
    Proyecto* p_eniac = nullptr;
    Proyecto* p_bombe = nullptr;
    try {
        p_eniac = eniac_lab.buscar_proyecto_por_nombre("ENIAC");
        p_bombe = eniac_lab.buscar_proyecto_por_nombre("Bombe");

        p_eniac->listar_cientificos_involucrados();
        p_bombe->listar_cientificos_involucrados();
        
    } catch (const ProyectoNoEncontradoError& e) {
        cout << "Excepcion Capturada: " << e.what() << endl;
    }


    // 5.b. Mostrar resumen de contribuciones (Polimorfismo: Sobrescritura de metodos)
    cout << "\nResumen de Contribuciones (Polimorfismo) ---" << endl;
    vector<Cientifico*> cientificos_lista = {c_turing, c_lovelace, c_neumann};

    for (const auto& c : cientificos_lista) {
        cout << "\n" << c->resumen() << endl; 
        cout << "**Contribucion Historica**: " << c->contribucion() << endl;
    }

    // Verificacion de Sobrecarga de Metodos
    cout << "\nPolimorfismo: Sobrecarga de Metodos (calcular_impacto) ---" << endl;
    auto* mat = dynamic_cast<Matematico*>(c_lovelace);
    if (mat) {
        cout << lovelace->get_nombre() << ": " << mat->calcular_impacto() << endl; 
        cout << lovelace->get_nombre() << ": " << mat->calcular_impacto(4.5) << endl; 
    }


    // 5.d. Mostrar todos los cientificos asociados a una institucion
    eniac_lab.listar_cientificos_asociados();

    cout << "\nPolimorfismo: Sobrecarga de Operadores (<< y +=) ---" << endl;
    cout << "Salida de 'cout << *turing': " << *c_turing << endl; 
    cout << "Uso de operador += para agregar proyectos a Institucion: OK" << endl;

    cout << "\nDestruccion de objetos al salir del scope (Composicion: Proyectos destruidos con Institucion)." << endl;

    return 0;
}