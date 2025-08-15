#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "persona.h"
#include "generador.h"
#include "monitor.h"
#include <unordered_map>

/**
 * Muestra el menú principal de la aplicación.
 * 
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
 */
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar persona mas longeva en el país";
    std::cout << "\n3. Mostrar persona mas longeva por ciudad";
    std::cout << "\n4. Mostrar persona con mayor patrimonio en el país";
    std::cout << "\n5. Mostrar persona con mayor patrimonio por ciudad";
    std::cout << "\n6. Mostrar persona con mayor patrimonio por grupo de declaración";
    std::cout << "\n7. Listar declarantes de renta";
    std::cout << "\n8. Mostrar estadisticas";
    std::cout << "\n9. Exportar estadisticas";
    std::cout << "\n10. Salir";
    std::cout << "\nSeleccione una opción: ";
}

/**
 * Punto de entrada principal del programa.
 * 
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    
    // Puntero inteligente para gestionar la colección de personas
    // POR QUÉ: Evitar fugas de memoria y garantizar liberación automática.
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    
    Monitor monitor; // Monitor para medir rendimiento
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales para uso en los casos
        size_t tam = 0;
        std::string idBusqueda;
        
        // Iniciar medición de tiempo y memoria para la operación actual
        monitor.iniciar_tiempo();
        long memoria_inicio = monitor.obtener_memoria();
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de personas
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                
                // Mover el conjunto al puntero inteligente (propiedad única)
                personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));
                
                // Medir tiempo y memoria usada
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                // Registrar la operación
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: { // Mostrar resumen de todas las personas
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            // case 2: { // Mostrar detalle por índice
            //     if (!personas || personas->empty()) {
            //         std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
            //         break;
            //     }
                
            //     tam = personas->size();
            //     std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
            //     if(std::cin >> indice) {
            //         if(indice >= 0 && static_cast<size_t>(indice) < tam) {
            //             (*personas)[indice].mostrar();
            //         } else {
            //             std::cout << "Índice fuera de rango!\n";
            //         }
            //     } else {
            //         std::cout << "Entrada inválida!\n";
            //         std::cin.clear();
            //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //     }
                
            //     double tiempo_detalle = monitor.detener_tiempo();
            //     long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
            //     monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
            //     break;
            // }
                
            case 2: { // Buscar por ID
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                
                
                if(const Persona* encontrada = buscarLongevaPaisReferencia(*personas)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por referencia", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 3: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                Persona encontrada = buscarLongevaPaisValor(*personas);
                encontrada.mostrar();
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por valor", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 4: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                std::unordered_map<std::string,const Persona*> resultado = mostrarPersonasLongevasCiudadReferencia(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second->mostrar();
                }
                
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas longevas por ciudad (Referencia)", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 5: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                std::unordered_map<std::string,Persona> resultado = mostrarPersonasLongevasCiudadValor(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second.mostrar();
                }
                
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas longevas por ciudad (Valor)", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 8: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 9: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
                
            case 10: // Salir
                std::cout << "Saliendo...\n";
                break;
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas de la operación (excepto para opciones 4,5,6)
        if (opcion >= 0 && opcion <= 3) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 10);
    
    return 0;
}