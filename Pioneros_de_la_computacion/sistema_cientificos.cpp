#include "Pioneros.h"
#include <iostream>

using namespace std;

// Implementacion: Cientifico
string Cientifico::getNombre() const { 
    return nombre; 
}

void Cientifico::agregarProyecto(Proyecto* p) {
    // Validacion simple para evitar duplicados en la asociacion
    bool encontrado = false;
    for (auto proy : proyectos) {
        if (proy == p) {
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        proyectos.push_back(p);
    }
}

string Cientifico::resumen() const {
    string lista_proy = "";
    for (auto p : proyectos) {
        lista_proy += p->getNombre() + ", ";
    }
    // Quitar la ultima coma y espacio
    if (!lista_proy.empty()) {
        lista_proy = lista_proy.substr(0, lista_proy.length() - 2);
    }

    return "[Resumen] " + nombre + " (" + pais + ")\n"
        "  Campo: " + campo_estudio + "\n"
        "  Proyectos: " + (lista_proy.empty() ? "N/A" : lista_proy);
}

ostream& operator<<(ostream& os, const Cientifico& c) {
    os << c.nombre << " (" << c.pais << ")";
    return os;
}

// Implementacion: Matematico
string Matematico::contribucion() const {
    return "Contribucion (Matematico): Sento las bases teoricas y logicas para los algoritmos, "
        "especialmente con su trabajo en '" + teorema_clave + "'.";
}
string Matematico::resumen() const {
    return Cientifico::resumen() + "\n"
        "  Info Clave: Teorema sobre " + teorema_clave;
}
void Matematico::mostrarLogros() const {
    cout << getNombre() << " (Logro Base): " << teorema_clave << endl;
}
void Matematico::mostrarLogros(bool con_detalle) const {
    if (con_detalle) {
        cout << getNombre() << " (Logro Detallado): Famoso por su trabajo en " << teorema_clave << endl;
    } else {
        mostrarLogros();
    }
}

// Implementacion: Ingeniero
string Ingeniero::contribucion() const {
    return "Contribucion (Ingeniero): Fue clave en la arquitectura de hardware y la implementacion practica, "
        "destacando su '" + diseno_clave + "'.";
}
string Ingeniero::resumen() const {
    return Cientifico::resumen() + "\n"
        "  Info Clave: Diseno de " + diseno_clave;
}
void Ingeniero::mostrarLogros() const {
    cout << getNombre() << " (Logro Base): " << diseno_clave << endl;
}
void Ingeniero::mostrarLogros(bool con_detalle) const {
    if (con_detalle) {
        cout << getNombre() << " (Logro Detallado): Famoso por su diseno de " << diseno_clave << endl;
    } else {
        mostrarLogros();
    }
}

// Implementacion: Criptografo
string Criptografo::contribucion() const {
    return "Contribucion (Criptografo): Pionero en logica algoritmica y decodificacion, "
        "logrando el descifrado de '" + logro_clave + "'.";
}
string Criptografo::resumen() const {
    return Cientifico::resumen() + "\n"
        "  Info Clave: Descifrado de " + logro_clave;
}
void Criptografo::mostrarLogros() const {
    cout << getNombre() << " (Logro Base): " << logro_clave << endl;
}
void Criptografo::mostrarLogros(bool con_detalle) const {
    if (con_detalle) {
        cout << getNombre() << " (Logro Detallado): Famoso por descifrar " << logro_clave << endl;
    } else {
        mostrarLogros();
    }
}

// Implementacion: Proyecto
string Proyecto::getNombre() const {
    return nombre;
}

vector<Cientifico*> Proyecto::getCientificos() const {
    return cientificos;
}

void Proyecto::agregarCientifico(Cientifico* c) {
    // Validacion de duplicados
    for (auto cientifico_existente : cientificos) {
        if (cientifico_existente == c) {
            throw CientificoDuplicadoError("Error: " + c->getNombre() + " ya esta en el proyecto " + nombre);
        }
    }
    
    // Agregacion
    cientificos.push_back(c);
    // Asociacion
    c->agregarProyecto(this);
    cout << "  -> " << c->getNombre() << " agregado a " << nombre << endl;
}

void Proyecto::listarCientificos() const {
    cout << "--- Cientificos en " << nombre << " (" << anio << ") ---" << endl;
    if (cientificos.empty()) {
        cout << "   (No hay cientificos asignados)" << endl;
        return;
    }
    for (auto c : cientificos) {
        cout << "   * " << c->getNombre() << endl;
    }
}

// Implementacion: Institucion
void Institucion::agregarProyecto(Proyecto* p) {
    // Composicion
    proyectos.push_back(p);
}

void Institucion::listarProyectos() const {
    cout << "\n=== Proyectos en " << nombre << " ===" << endl;
    for (auto p : proyectos) {
        cout << " - " << p->getNombre() << endl;
    }
}

void Institucion::listarCientificosGlobales() const {
    cout << "\n=== Todos los Cientificos en " << nombre << " ===" << endl;
    
    vector<Cientifico*> unicos;

    for (auto p : proyectos) { 
        vector<Cientifico*> cientificos_del_proyecto = p->getCientificos(); 
        
        for (auto c_proy : cientificos_del_proyecto) {
            // Buscamos si ya lo agregamos
            bool encontrado = false;
            for (auto c_unico : unicos) {
                if (c_unico == c_proy) {
                    encontrado = true;
                    break;
                }
            }
            // Si no lo encontramos, lo agregamos
            if (!encontrado) {
                unicos.push_back(c_proy);
            }
        }
    }

    // Imprimimos la lista de unicos
    for (auto c : unicos) {
        cout << " * " << c->getNombre() << endl;
    }
}


// Main
int main() {
    cout << "--- Creando sistema (Ejercicio 2) ---" << endl;

    // 1. Institucion
    Institucion eniac_lab("ENIAC Lab");

    // 2. Proyectos
    Proyecto eniac("ENIAC", 1945);
    Proyecto bombe("Bombe", 1940);

    // Composicion
    eniac_lab.agregarProyecto(&eniac);
    eniac_lab.agregarProyecto(&bombe);

    // 3. Cientificos
    Matematico lovelace("Ada Lovelace", "Reino Unido", "Matematica", "Numeros de Bernoulli");
    Ingeniero von_neumann("John von Neumann", "Hungria/EE.UU.", "Arquitectura", "Arquitectura Von Neumann");
    Criptografo turing("Alan Turing", "Reino Unido", "Logica", "Maquina Enigma");

    // 4. Agregacion y Validacion
    cout << "\n--- Asignando Cientificos (Agregacion) ---" << endl;
    try {
        eniac.agregarCientifico(&von_neumann);
        bombe.agregarCientifico(&turing);
        bombe.agregarCientifico(&lovelace);
        eniac.agregarCientifico(&lovelace); // Lovelace en 2 proyectos

        // Validacion de error
        cout << "\n--- Probando Error (Cientifico Duplicado) ---" << endl;
        bombe.agregarCientifico(&turing); // Esto debe fallar

    } catch (const CientificoDuplicadoError& e) {
        cout << "[ERROR CAPTURADO] " << e.what() << endl;
    } catch (const exception& e) {
        cout << "[ERROR INESPERADO] " << e.what() << endl;
    }

    // 5. Salidas Esperadas
    
    eniac_lab.listarProyectos();

    cout << "\n";
    eniac.listarCientificos();
    bombe.listarCientificos();

    cout << "\n--- Resumenes (Polimorfismo) ---" << endl;
    vector<Cientifico*> lista_cientificos = {&lovelace, &von_neumann, &turing};
    
    for (auto c : lista_cientificos) {
        cout << "\n" << c->resumen() << endl;
        cout << c->contribucion() << endl;
    }

    eniac_lab.listarCientificosGlobales();

    // Pruebas de Sobrecarga
    cout << "\n--- Pruebas de Sobrecarga ---" << endl;
    
    cout << "Prueba Operador '<<': " << turing << endl;

    cout << "Prueba Sobrecarga Metodo:" << endl;
    lovelace.mostrarLogros();        // Version 1
    lovelace.mostrarLogros(true);    // Version 2

    cout << "\n--- Fin del Programa ---" << endl;
    return 0;
}