#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Clase para medir tiempo y memoria en Linux
class Monitor {
public:
    // Inicia la medición de tiempo
    void iniciar_tiempo();
    // Detiene la medición de tiempo y devuelve milisegundos
    double detener_tiempo();
    // Obtiene el consumo de memoria actual en KB usando /proc/self/statm
    long obtener_memoria();
    
    // Registra estadísticas para una operación
    void registrar(const std::string& operacion, double tiempo, long memoria);
    
    // Muestra estadísticas de una operación
    void mostrar_estadistica(const std::string& operacion, double tiempo, long memoria);
    
    // Muestra todas las estadísticas registradas
    void mostrar_resumen();
    // Exporta las estadísticas a un archivo CSV
    void exportar_csv(const std::string& nombre_archivo = "estadisticas.csv");

private:
    struct Registro {
        std::string operacion;
        double tiempo;
        long memoria;
    };
    
    std::chrono::high_resolution_clock::time_point inicio;
    std::vector<Registro> registros;
    double total_tiempo = 0;
    long max_memoria = 0;
};

#endif // MONITOR_H