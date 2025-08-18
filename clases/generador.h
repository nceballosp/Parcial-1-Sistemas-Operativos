#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"
#include <vector>
#include <unordered_map>

// Funciones para generación de datos aleatorios

/**
 * Genera una fecha de nacimiento aleatoria entre 1960 y 2010.
 * 
 * POR QUÉ: Simular fechas realistas para personas.
 * CÓMO: Combinando números aleatorios para día, mes y año.
 * PARA QUÉ: Inicializar el atributo fechaNacimiento de Persona.
 */
std::tuple<int,int,int> generarFechaNacimiento();

/**
 * Genera un ID único secuencial.
 * 
 * POR QUÉ: Necesidad de identificadores únicos para cada persona.
 * CÓMO: Usando un contador estático que incrementa en cada llamada.
 * PARA QUÉ: Garantizar unicidad en los IDs.
 */
std::string generarID();

/**
 * Genera un número decimal aleatorio en un rango [min, max].
 * 
 * POR QUÉ: Necesidad de valores realistas para ingresos, patrimonio, etc.
 * CÓMO: Usando un generador Mersenne Twister y una distribución uniforme.
 * PARA QUÉ: Producir valores financieros aleatorios pero dentro de rangos lógicos.
 */
double randomDouble(double min, double max);

/**
 * Crea una persona con datos aleatorios.
 * 
 * POR QUÉ: Automatizar la creación de registros de personas.
 * CÓMO: Combinando las funciones generadoras y bases de datos de nombres, apellidos, etc.
 * PARA QUÉ: Poblar el sistema con datos de prueba.
 */
Persona generarPersona();

/**
 * Genera una colección (vector) de n personas.
 * 
 * POR QUÉ: Crear conjuntos de datos de diferentes tamaños.
 * CÓMO: Llamando a generarPersona() n veces.
 * PARA QUÉ: Pruebas de rendimiento y funcionalidad con volúmenes variables.
 */
std::vector<Persona> generarColeccion(int n);

/**
 * Busca una persona por ID en un vector de personas.
 * 
 * POR QUÉ: Recuperar una persona específica de una colección.
 * CÓMO: Usando un algoritmo de búsqueda lineal (o binaria si se ordena).
 * PARA QUÉ: Implementar funcionalidad de búsqueda en la aplicación.
 * 
 * @param personas Vector de personas donde buscar.
 * @param id ID a buscar.
 * @return Puntero a la persona encontrada o nullptr si no se encuentra.
 */
Persona buscarLongevaPaisValor(const std::vector<Persona> personas);

const Persona* buscarLongevaPaisReferencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,const Persona*> mostrarPersonasLongevasCiudadReferencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,Persona> mostrarPersonasLongevasCiudadValor(const std::vector<Persona> personas);

const Persona* buscarMayorPatrimonioPaisReferencia(const std::vector<Persona> &personas);

const Persona buscarMayorPatrimonioPaisValor(const std::vector<Persona> personas);

std::unordered_map<std::string,const Persona*> buscarMayorPatrimonioCiudadReferencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,Persona> buscarMayorPatrimonioCiudadValor(const std::vector<Persona> personas);

std::unordered_map<std::string,const Persona*> buscarMayorPatrimonioGrupoReferencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,Persona> buscarMayorPatrimonioGrupoValor(const std::vector<Persona> personas);

const std::unordered_map<std::string,std::vector<const Persona*>> listarPersonasGrupoReferencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,std::vector<Persona>> listarPersonasGrupoValor(std::vector<Persona> personas);

const Persona* buscarMayorDeudaPaisReferencia(const std::vector<Persona> &personas);

Persona buscarMayorDeudaPaisValor(std::vector<Persona> personas);

const std::pair<std::string,long double> buscarCiudadMayorPatrimonioReferencia(const std::vector<Persona> &personas);

const std::pair<std::string,long double> buscarCiudadMayorPatrimonioValor(const std::vector<Persona> personas);

std::unordered_map<std::string,std::vector<const Persona*>> listarPersonasConPatrimonioMayor1000Referencia(const std::vector<Persona> &personas);

std::unordered_map<std::string,std::vector<Persona>> listarPersonasConPatrimonioMayor1000Valor(std::vector<Persona> personas);

#endif // GENERADOR_H