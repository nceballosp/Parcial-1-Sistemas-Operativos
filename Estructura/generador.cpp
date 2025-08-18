#include "generador.h"
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // std::mt19937, std::uniform_real_distribution
#include <vector>
#include <algorithm> // std::find_if
#include <unordered_map>
#include <iostream>
#include <tuple>
// Bases de datos para generación realista

// Nombres femeninos comunes en Colombia
const std::vector<std::string> nombresFemeninos = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
    "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Diana", "Lucía", "Ximena"
};

// Nombres masculinos comunes en Colombia
const std::vector<std::string> nombresMasculinos = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Nestor", "Gertridis"
};

// Apellidos comunes en Colombia
const std::vector<std::string> apellidos = {
    "Gómez", "Rodríguez", "Martínez", "López", "García", "Pérez", "González", "Sánchez", "Ramírez", "Torres",
    "Díaz", "Vargas", "Castro", "Ruiz", "Álvarez", "Romero", "Suárez", "Rojas", "Moreno", "Muñoz", "Valencia",
};

// Principales ciudades colombianas
const std::vector<std::string> ciudadesColombia = {
    "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
    "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
};

/**
 * Implementación de generarFechaNacimiento.
 * 
 * POR QUÉ: Simular fechas de nacimiento realistas.
 * CÓMO: Día (1-28), mes (1-12), año (1960-2009).
 * PARA QUÉ: Atributo fechaNacimiento de Persona.
 */
std::tuple<int,int,int> generarFechaNacimiento() {
    int dia = 1 + rand() % 28;       // Día: 1 a 28 (evita problemas con meses)
    int mes = 1 + rand() % 12;        // Mes: 1 a 12
    int anio = 1960 + rand() % 50;    // Año: 1960 a 2009
    return {dia,mes,anio};
}

/**
 * Implementación de generarID.
 * 
 * POR QUÉ: Generar identificadores únicos y secuenciales.
 * CÓMO: Contador estático que inicia en 1000000000 y se incrementa.
 * PARA QUÉ: Simular números de cédula.
 */
std::string generarID() {
    static long contador = 1000000000; // Inicia en 1,000,000,000
    return std::to_string(contador++); // Convierte a string e incrementa
}

/**
 * Implementación de randomDouble.
 * 
 * POR QUÉ: Generar números decimales aleatorios en un rango.
 * CÓMO: Mersenne Twister (mejor que rand()) y distribución uniforme.
 * PARA QUÉ: Valores de ingresos, patrimonio, etc.
 */
double randomDouble(double min, double max) {
    static std::mt19937 generator(time(nullptr)); // Semilla basada en tiempo
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

/**
 * Implementación de generarPersona.
 * 
 * POR QUÉ: Crear una persona con datos aleatorios.
 * CÓMO: Seleccionando aleatoriamente de las bases de datos y generando números.
 * PARA QUÉ: Generar datos de prueba.
 */
Persona generarPersona() {
    // Decide si es hombre o mujer
    Persona p;
    bool esHombre = rand() % 2;
    
    // Selecciona nombre según género
    p.nombre = esHombre ? 
        nombresMasculinos[rand() % nombresMasculinos.size()] :
        nombresFemeninos[rand() % nombresFemeninos.size()];
    
    // Construye apellido compuesto (dos apellidos aleatorios)
    p.apellido = apellidos[rand() % apellidos.size()];
    p.apellido += " ";
    p.apellido += apellidos[rand() % apellidos.size()];
    
    // Genera los demás atributos
    p.id = generarID();
    p.ciudadResidencia = ciudadesColombia[rand() % ciudadesColombia.size()];
    p.fechaNacimiento = generarFechaNacimiento();
    
    // Genera datos financieros realistas
    p.ingresosAnuales = randomDouble(10000000, 500000000);   // 10M a 500M COP
    p.patrimonio = randomDouble(0, 2000000000);       // 0 a 2,000M COP
    p.deudas = randomDouble(0, p.patrimonio * 0.7);     // Deudas hasta el 70% del patrimonio
    std::string grupo;
    int lastDigits = std::stoi(p.id.substr(p.id.length()-2));
    if(lastDigits < 40 ){
        grupo = "A";
    }
    else if (lastDigits > 39 && lastDigits < 80)
    {
        grupo = "B";
    }
        else if (lastDigits > 79 && lastDigits < 100)
    {
        grupo = "C";
    }
    
    p.grupoDeclaracion = grupo;
    
    return p;
}

/**
 * Implementación de generarColeccion.
 * 
 * POR QUÉ: Generar un conjunto de n personas.
 * CÓMO: Reservando espacio y agregando n personas generadas.
 * PARA QUÉ: Crear datasets para pruebas.
 */
std::vector<Persona> generarColeccion(int n) {
    std::vector<Persona> personas;
    personas.reserve(n); // Reserva espacio para n personas (eficiencia)
    
    for (int i = 0; i < n; ++i) {
        personas.push_back(generarPersona());
    }
    
    return personas;
}

Persona buscarLongevaPaisValor(const std::vector<Persona> personas){
    Persona personaLongeva = personas[0];
    for(const auto &persona : personas){
        auto [diaP,mesP,anioP] =  persona.fechaNacimiento;
        auto [diaPL,mesPL,anioPL] =  personaLongeva.fechaNacimiento;
        if(anioP!=anioPL){
            personaLongeva = anioP < anioPL ? persona : personaLongeva; 
        }
        else if (mesP!=mesPL)
        {
            personaLongeva = mesP < mesPL ? persona : personaLongeva;
        }
        else{
            personaLongeva = diaP < diaPL ? persona : personaLongeva;
        }
    }
    return personaLongeva;
}

const Persona* buscarLongevaPaisReferencia(const std::vector<Persona> &personas){
    const Persona* personaLongeva = &personas[0];
    for(const auto &persona : personas){
        auto [diaP,mesP,anioP] =  persona.fechaNacimiento;
        auto [diaPL,mesPL,anioPL] =  personaLongeva->fechaNacimiento;
        if(anioP!=anioPL){
            personaLongeva = anioP < anioPL ? &persona : personaLongeva;
        }
        else if (mesP!=mesPL)
        {
            personaLongeva = mesP < mesPL ? &persona : personaLongeva;
        }
        else{
            personaLongeva = diaP < diaPL ? &persona : personaLongeva;
        }
    }
    return personaLongeva;
}

std::unordered_map<std::string,const Persona*> mostrarPersonasLongevasCiudadReferencia(const std::vector<Persona> &personas){
    std::unordered_map<std::string,const Persona*> personaLongevaCiudad;
    
    for(const auto &persona : personas){
        auto [diaP,mesP,anioP] =  persona.fechaNacimiento;
        //revisa si ya existe una llave para la ciudad evaluada
        if(personaLongevaCiudad.count(persona.ciudadResidencia) == 0){
            personaLongevaCiudad[persona.ciudadResidencia] = &persona;
        }
        else
        {
            auto [diaPL,mesPL,anioPL] =  personaLongevaCiudad[persona.ciudadResidencia]->fechaNacimiento;
            if(anioP!=anioPL){
                personaLongevaCiudad[persona.ciudadResidencia] = anioP < anioPL ? &persona : personaLongevaCiudad[persona.ciudadResidencia]; 
            }
            else if (mesP!=mesPL)
            {
                personaLongevaCiudad[persona.ciudadResidencia] = mesP < mesPL ? &persona : personaLongevaCiudad[persona.ciudadResidencia];
            }
            else{
                personaLongevaCiudad[persona.ciudadResidencia] = diaP < diaPL ? &persona : personaLongevaCiudad[persona.ciudadResidencia];
            }
        }
        
    }
    return personaLongevaCiudad;
}
std::unordered_map<std::string,Persona> mostrarPersonasLongevasCiudadValor(const std::vector<Persona> personas){
    //arreglar no constructor default
    std::unordered_map<std::string,Persona> personaLongevaCiudad;
    
    for(const auto &persona : personas){
        auto [diaP,mesP,anioP] =  persona.fechaNacimiento;
        //revisa si ya existe una llave para la ciudad evaluada
        if(personaLongevaCiudad.count(persona.ciudadResidencia) == 0){
            personaLongevaCiudad.emplace(persona.ciudadResidencia,persona);
        }
        else
        {
            auto [diaPL,mesPL,anioPL] =  personaLongevaCiudad[persona.ciudadResidencia].fechaNacimiento;
            if(anioP!=anioPL){
                personaLongevaCiudad[persona.ciudadResidencia] = anioP < anioPL ? persona : personaLongevaCiudad[persona.ciudadResidencia]; 
            }
            else if (mesP!=mesPL)
            {
                personaLongevaCiudad[persona.ciudadResidencia] = mesP < mesPL ? persona : personaLongevaCiudad[persona.ciudadResidencia];
            }
            else{
                personaLongevaCiudad[persona.ciudadResidencia] = diaP < diaPL ? persona : personaLongevaCiudad[persona.ciudadResidencia];
            }
        }
        
    }
    return personaLongevaCiudad;
}
const Persona* buscarMayorPatrimonioPaisReferencia(const std::vector<Persona> &personas){
    const Persona* personaRica = &personas[0];
    for(const auto &persona : personas){
        double patrimonioNetoPR = personaRica->patrimonio - personaRica->deudas;
        double patrimonioNetoP = persona.patrimonio - persona.deudas; 
        if(patrimonioNetoPR<patrimonioNetoP){
            personaRica = &persona;
        }
    }
    return personaRica;
}
const Persona buscarMayorPatrimonioPaisValor(const std::vector<Persona> personas){
    Persona personaRica = personas[0];
    for(const auto &persona : personas){
        double patrimonioNetoPR = personaRica.patrimonio - personaRica.deudas;
        double patrimonioNetoP = persona.patrimonio - persona.deudas; 
        if(patrimonioNetoPR<patrimonioNetoP){
            personaRica = persona;
        }
    }
    return personaRica;
}
std::unordered_map<std::string,const Persona*> buscarMayorPatrimonioCiudadReferencia(const std::vector<Persona> &personas){
    std::unordered_map<std::string,const Persona*> personaRicaCiudad;
    for(const auto &persona : personas){
        if(personaRicaCiudad.count(persona.ciudadResidencia)==0){
            personaRicaCiudad[persona.ciudadResidencia] = &persona; 
        }
        else{
            const Persona* personaRica = personaRicaCiudad[persona.ciudadResidencia];
            double patrimonioNetoPR = personaRica->patrimonio - personaRica->deudas;
            double patrimonioNetoP = persona.patrimonio - persona.deudas; 
            if(patrimonioNetoPR<patrimonioNetoP){
                personaRicaCiudad[persona.ciudadResidencia] = &persona;
            }
        }
    }
    return personaRicaCiudad;
}
std::unordered_map<std::string,Persona> buscarMayorPatrimonioCiudadValor(const std::vector<Persona> personas){
    std::unordered_map<std::string,Persona> personaRicaCiudad;
    for(const auto &persona : personas){
        if(personaRicaCiudad.count(persona.ciudadResidencia)==0){
            personaRicaCiudad[persona.ciudadResidencia] = persona; 
        }
        else{
            Persona personaRica = personaRicaCiudad[persona.ciudadResidencia];
            double patrimonioNetoPR = personaRica.patrimonio - personaRica.deudas;
            double patrimonioNetoP = persona.patrimonio - persona.deudas; 
            if(patrimonioNetoPR<patrimonioNetoP){
                personaRicaCiudad[persona.ciudadResidencia] = persona;
            }
        }
    }
    return personaRicaCiudad;
}
std::unordered_map<std::string,const Persona*> buscarMayorPatrimonioGrupoReferencia(const std::vector<Persona> &personas){
    std::unordered_map<std::string,const Persona*> personaRicaGrupo;
    for(const auto &persona : personas){
        if(personaRicaGrupo.count(persona.grupoDeclaracion)==0){
            personaRicaGrupo[persona.grupoDeclaracion] = &persona; 
        }
        else{
            const Persona* personaRica = personaRicaGrupo[persona.grupoDeclaracion];
            double patrimonioNetoPR = personaRica->patrimonio - personaRica->deudas;
            double patrimonioNetoP = persona.patrimonio - persona.deudas; 
            if(patrimonioNetoPR<patrimonioNetoP){
                personaRicaGrupo[persona.grupoDeclaracion] = &persona;
            }
        }
    }
    return personaRicaGrupo;
}
std::unordered_map<std::string,Persona> buscarMayorPatrimonioGrupoValor(const std::vector<Persona> personas){
    std::unordered_map<std::string,Persona> personaRicaGrupo;
    for(const auto &persona : personas){
        if(personaRicaGrupo.count(persona.grupoDeclaracion)==0){
            personaRicaGrupo[persona.grupoDeclaracion] = persona; 
        }
        else{
            Persona personaRica = personaRicaGrupo[persona.grupoDeclaracion];
            double patrimonioNetoPR = personaRica.patrimonio - personaRica.deudas;
            double patrimonioNetoP = persona.patrimonio - persona.deudas; 
            if(patrimonioNetoPR<patrimonioNetoP){
                personaRicaGrupo[persona.grupoDeclaracion] = persona;
            }
        }
    }
    return personaRicaGrupo;
}
const std::unordered_map<std::string,std::vector<const Persona*>> listarPersonasGrupoReferencia(const std::vector<Persona> &personas){
    std::unordered_map<std::string,std::vector<const Persona*>> personasPorGrupo;
    for(const auto &persona : personas){
         personasPorGrupo[persona.grupoDeclaracion].push_back(&persona);
    }
    return personasPorGrupo;
}
std::unordered_map<std::string,std::vector<Persona>> listarPersonasGrupoValor(std::vector<Persona> personas){
    std::unordered_map<std::string,std::vector<Persona>> personasPorGrupo;
    for(const auto &persona : personas){
         personasPorGrupo[persona.grupoDeclaracion].push_back(persona);
    }
    return personasPorGrupo;
}
const Persona* buscarMayorDeudaPaisReferencia(const std::vector<Persona> &personas){
    const Persona* personaEndeudada = &personas[0];
    for(const auto &persona : personas){
        if(personaEndeudada->deudas<persona.deudas){
            personaEndeudada = &persona;
        }
    }
    return personaEndeudada;
}
Persona buscarMayorDeudaPaisValor(std::vector<Persona> personas){
    Persona personaEndeudada = personas[0];
    for(const auto &persona : personas){
        if(personaEndeudada.deudas<persona.deudas){
            personaEndeudada = persona;
        }
    }
    return personaEndeudada;
}

const std::pair<std::string,long double> buscarCiudadMayorPatrimonioReferencia(const std::vector<Persona> &personas){
    std::pair<std::string,long double> ciudadRica = {"",0};
    std::unordered_map<std::string,long double> ciudadesPatrimonio;
    for(const auto& persona:personas){
        if (ciudadesPatrimonio.count(persona.ciudadResidencia)==0)
        {
            ciudadesPatrimonio[persona.ciudadResidencia] = persona.patrimonio;
        }
        else{
            ciudadesPatrimonio[persona.ciudadResidencia] += persona.patrimonio;
        }
    }
    for(auto const &pair:ciudadesPatrimonio){
        if(pair.second > ciudadRica.second){
            ciudadRica = pair;
        }

    }

    
    return ciudadRica;
}
const std::pair<std::string,long double> buscarCiudadMayorPatrimonioValor(const std::vector<Persona> personas){
    std::pair<std::string,long double> ciudadRica = {"",0};
    std::unordered_map<std::string,long double> ciudadesPatrimonio;
    for(const auto& persona:personas){
        if (ciudadesPatrimonio.count(persona.ciudadResidencia)==0)
        {
            ciudadesPatrimonio[persona.ciudadResidencia] = persona.patrimonio;
        }
        else{
            ciudadesPatrimonio[persona.ciudadResidencia] += persona.patrimonio;
        }
    }
    for(auto const &pair:ciudadesPatrimonio){
        if(pair.second > ciudadRica.second){
            ciudadRica = pair;
        }

    }
    return ciudadRica;
}

std::unordered_map<std::string,std::vector<const Persona*>> listarPersonasConPatrimonioMayor1000Referencia(const std::vector<Persona> &personas){
    std::unordered_map<std::string,std::vector<const Persona*>> personaRica;
    long long umbral = 1'000'000'000LL;
    for(const auto &persona : personas){
        if (persona.patrimonio > umbral) {
            personaRica[persona.ciudadResidencia].push_back(&persona);
        }
    }
    return personaRica;
}

std::unordered_map<std::string,std::vector<Persona>> listarPersonasConPatrimonioMayor1000Valor(std::vector<Persona> personas){
    std::unordered_map<std::string,std::vector<Persona>> personaRica;
    long long umbral = 1'000'000'000LL;
    for(const auto &persona : personas){
        if (persona.patrimonio > umbral) {
            personaRica[persona.ciudadResidencia].push_back(persona);
        }
    }
    return personaRica;
}
