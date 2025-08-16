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
    std::cout << "\n2. Mostrar persona mas longeva en el país(Referencia)";
    std::cout << "\n3. Mostrar persona mas longeva en el país(Valor)";
    std::cout << "\n4. Mostrar persona mas longeva por ciudad(Referencia)";
    std::cout << "\n5. Mostrar persona mas longeva por ciudad(Valor)";
    std::cout << "\n6. Mostrar persona con mayor patrimonio en el país(Referencia)";
    std::cout << "\n7. Mostrar persona con mayor patrimonio en el país(Valor)";
    std::cout << "\n8. Mostrar persona con mayor patrimonio por ciudad(Referencia)";
    std::cout << "\n9. Mostrar persona con mayor patrimonio por ciudad(Valor)";
    std::cout << "\n10. Mostrar persona con mayor patrimonio por grupo de declaración(Referencia)";
    std::cout << "\n11. Mostrar persona con mayor patrimonio por grupo de declaración(Valor)";
    std::cout << "\n12. Listar declarantes de renta(Referencia)";   
    std::cout << "\n13. Listar declarantes de renta(Valor)";   
    std::cout << "\n14. Persona con mayor endeudamiento en el país(Referencia)";   
    std::cout << "\n15. Persona con mayor endeudamiento en el país(Valor)";   
    std::cout << "\n16. Ciudad con mayor patrimonio agregado(Referencia)";   
    std::cout << "\n17. Ciudad con mayor patrimonio agregado(Valor)";   
    std::cout << "\n18. Personas tienen patrimonio superior a 1.000 millones(Referencia)";   
    std::cout << "\n19. Personas tienen patrimonio superior a 1.000 millones(Valor)";   
    std::cout << "\n20. Mostrar estadisticas";
    std::cout << "\n21. Exportar estadisticas";
    std::cout << "\n22. Salir";
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
                
                
            case 2: { 
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                
                
                if(const Persona* encontrada = buscarLongevaPaisReferencia(*personas)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona " << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas más longeva del país(Referencia)", tiempo_busqueda, memoria_busqueda);
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
                monitor.registrar("Mostrar personas más longeva del país(Valor)", tiempo_busqueda, memoria_busqueda);
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
            case 6: { 
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                
                
                if(const Persona* encontrada = buscarMayorPatrimonioPaisReferencia(*personas)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona " << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas más rica del país(Referencia)", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 7: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                Persona encontrada = buscarMayorPatrimonioPaisValor(*personas);
                encontrada.mostrar();
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas más rica del país(Valor)", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 8: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                
                std::unordered_map<std::string,const Persona*> resultado = buscarMayorPatrimonioCiudadReferencia(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second->mostrar();
                }
                
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas ricas por ciudad (Referencia)", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 9: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                std::unordered_map<std::string,Persona> resultado = buscarMayorPatrimonioCiudadValor(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second.mostrar();
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas ricas por ciudad (Valor)", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 10: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                
                std::unordered_map<std::string,const Persona*> resultado = buscarMayorPatrimonioGrupoReferencia(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second->mostrar();
                }
                
            
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas ricas por Grupo (Referencia)", tiempo_busqueda, memoria_busqueda);
                break;
            }
            case 11: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }                

                std::unordered_map<std::string,Persona> resultado = buscarMayorPatrimonioGrupoValor(*personas);
                for (const auto &pair : resultado)
                {
                    std::cout <<"\n" << pair.first << ":";
                    pair.second.mostrar();
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar personas mas ricas por Grupo (Valor)", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 20: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 21: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
                
            case 22: // Salir
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
        
    } while(opcion != 22);
    
    return 0;
}