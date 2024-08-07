#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "ValidacionCedula.h"
#include "Lista.h"
#include "ManejoArchivos.cpp"
#include "SetConsole - UTF8.h"
#include "IngresoDatos.h"
#include "Materia.h"
#include "ordenamiento.h"
#include "busquedaBinaria.h"
#include "TablaHash.h"
#include "MetodosExternos.cpp"
#include "Estudiante.h"

using namespace std;
long long int validar(long long int &x);

class Menu {
public:
    Menu();
    void MostrarMenuPrincipal();
	void MostrarMenuInicioSesion();

private:
    int numNotas;
    int numeroEstudiantes;
    TablaHash<float, Estudiante> tablaHash;
    ManejoArchivos manejoArchivos;
    string nombreDocente;
    string cedulaDocente;
    string materia;
    string NRC;
    IngresoDatos crearUsuario;
    Lista<double> notas;
    Lista<Estudiante>estudiantes;
    Profesor profesor;
    Materia materia1;

    float* arrPromedios;
    bool profesorLogueado;
    bool materiaIngresada;
    bool estudiantesIngresados;
    bool notasIngresadas;
    bool datosAlmacenados;

    void Login();
    void PedirDatosDocente();
    void PedirMateriaNRC();
    void PedirNumeroEstudiantes();
    void escribirNotasOrdenadasEnArchivo(const double* arrPromedios, int numeroEstudiantes, const string& metodoOrdenamiento);
    void guardar_informacion();
    float* IngresarNotas();
    void AlmacenarDatos();
    void OrdenarNotas();
    void OrdenamientoExterno();
    void BuscarCalificacion();

    float CalcularPromedio();
    float CalcularPromedio(float* n, int numNotas);
    QuickSort<double> quickSort;
    ShellSort<double> shellSort;
    BucketSort bucketSort; 
    RadixSort<double> radixSort;
};

string crearCorreo(const string& nombre, const string& apellido) {
    string correo;
    string nombreC= nombre;
    string apellidoC = apellido;

    for (char& c : nombreC) c = tolower(c);
    for (char& c : apellidoC) c = tolower(c);

    // Construir la dirección de correo
    correo = nombreC.substr(0, 1) + apellidoC + "@espe.edu.ec";
    
    return correo;
}

Menu::Menu() : profesorLogueado(false), materiaIngresada(false), estudiantesIngresados(false),
               notasIngresadas(false), datosAlmacenados(false), numeroEstudiantes(0), arrPromedios(nullptr) {}
void imprimirNotasOrdenadas(const double* arrPromedios, int numeroEstudiantes) {
    cout << "Notas ordenadas:" << endl;
    for (int i = 0; i < numeroEstudiantes; i++) {
        cout << arrPromedios[i] << " ";
    }
    cout << endl;
}
void Menu::MostrarMenuInicioSesion() {
    int opcion;
    cout << "           ~ INICIO DE SESION   ~            " << endl;
    if (!profesorLogueado) {
        cout << "1. Registro de docente" << endl;
        Login();
    }
    MostrarMenuPrincipal();
}

void Menu::MostrarMenuPrincipal() {
    int opcion;
    do {
        system("cls");

        cout << "           ~  Menu Principal   ~             " << endl;
        cout << "1. Registro de materia y NRC" << endl;
        cout << "2. Registro de número de estudiantes y numero de notas" << endl;
        cout << "3. Ingresar las notas por cada estudiante" << endl;
        cout << "4. Almacenar datos" << endl;
        cout << "5. Ordenar notas" << endl;
        cout << "6. Buscar calificación" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                PedirMateriaNRC();
                system("pause");
                break;
            case 2:
                PedirNumeroEstudiantes();
                system("pause");
                break;
            case 3:
                if (estudiantesIngresados) {
                    guardar_informacion();
                } else {
                    cout << "No puede realizar esta acción ahora." << endl;
                }
                system("pause");
                break;
            case 4:
                AlmacenarDatos();
                system("pause");
                break;
            case 5:
                OrdenarNotas();
                system("pause");
                break;
            case 6:
                BuscarCalificacion();
                system("pause");
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                exit(0);
                break;
            default:
                cout << "Opción inválida, por favor intente nuevamente." << endl;
                system("pause");
        }
    } while (opcion != 0);
}
void Menu::OrdenarNotas() {
    string ordenamiento = "";
    int opcion;

    cout << "Valores de arrPromedios antes de la conversión:" << endl;
    for (int i = 0; i < numeroEstudiantes; ++i) {
        cout << arrPromedios[i] << " ";
    }
    cout << endl;

	double* arrPromediosDouble = new double[numeroEstudiantes];
		for (int i = 0; i < numeroEstudiantes; ++i) {
    arrPromediosDouble[i] = static_cast<double>(arrPromedios[i]);
}
    do {
    	system("cls");
        cout << "        ~ Submenú de Ordenamiento ~         " << endl;
        cout << ">> 1. BucketSort" << endl;
        cout << ">> 2. QuickSort" << endl;
        cout << ">> 3. ShellSort" << endl;
        cout << ">> 4. RadixSort" << endl;
        cout << ">> 5. Métodos Externos " << endl;
        cout << ">> 0. Volver al menú principal" << endl;

        cout << "Seleccione una opción de ordenamiento: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ordenamiento = "BucketSort";
                bucketSort.ordenar(arrPromediosDouble, numeroEstudiantes);
                imprimirNotasOrdenadas(arrPromediosDouble, numeroEstudiantes);
                escribirNotasOrdenadasEnArchivo(arrPromediosDouble, numeroEstudiantes, "BucketSort");
                system("pause");
                break;
            case 2:
                ordenamiento = "QuickSort";
                quickSort.ordenar(arrPromediosDouble, numeroEstudiantes);
                imprimirNotasOrdenadas(arrPromediosDouble, numeroEstudiantes);
                escribirNotasOrdenadasEnArchivo(arrPromediosDouble, numeroEstudiantes, "QuickSort");
                system("pause");
				break;
            case 3:
                ordenamiento = "ShellSort";
                shellSort.ordenar(arrPromediosDouble, numeroEstudiantes);
                imprimirNotasOrdenadas(arrPromediosDouble, numeroEstudiantes);
                escribirNotasOrdenadasEnArchivo(arrPromediosDouble, numeroEstudiantes, "ShellSort");
                system("pause");
                break;
            case 4:
                ordenamiento = "RadixSort";
                radixSort.ordenar(arrPromediosDouble, numeroEstudiantes);
                imprimirNotasOrdenadas(arrPromediosDouble, numeroEstudiantes);
                escribirNotasOrdenadasEnArchivo(arrPromediosDouble, numeroEstudiantes, "RadixSort");
                system("pause");
                break;
            case 5:
                ordenamiento = "Métodos Externos";
                OrdenamientoExterno();
                system("pause");
                break;
            case 0:
                MostrarMenuPrincipal();
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                system("pause");
        }
    } while (opcion != 0);

    //manejoArchivos.escribir_ResumenOrdenamiento(ordenamiento, estudiantes, profesor);
    delete[] arrPromediosDouble;
}
void Menu::escribirNotasOrdenadasEnArchivo(const double* arrPromedios, int numeroEstudiantes, const string& metodoOrdenamiento) {
    ofstream archivo("notas_ordenadas_" + metodoOrdenamiento + ".txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }
     archivo << "UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE\n";
    archivo << "REPORTE DE CALIFICACIONES\n\n";
    archivo << "Periodo: Mayo 2024 – Septiembre 2024\n";
    archivo << "Materia: " << materia1.getNombre() << "\n";
    archivo << "NRC: " << materia1.getCodigo() << "\n\n";
    archivo << "Notas ordenadas con " << metodoOrdenamiento << ":" << endl;
    archivo << left << setw(5) << "N°" << " || " << setw(15) << "Promedio" << " || " << setw(15) << "Nombre" << " || " << setw(30) << "Apellido" << " || ";
    archivo << "\n=====================================================================================" << endl;

    Nodo<Estudiante>* actual = estudiantes.getCabeza();
    int i = 0;
    while (actual != nullptr) {
        archivo << left << setw(5) << i + 1 << " || " << setw(15) << arrPromedios[i] << " || " << setw(15) << actual->dato.getNombre() << " || " << setw(30) << actual->dato.getApellido() << endl;
        actual = actual->siguiente;
        i++;
    }

    archivo.close();
    cout << "Notas ordenadas guardadas en 'notas_ordenadas_" << metodoOrdenamiento << ".txt'." << endl;
}
void Menu::OrdenamientoExterno() {
    MetodoExterno metodo("OrdenamientoDirecto.txt");
    for (int i=0;i<this->numeroEstudiantes;i++){
    	metodo.insertar(this->arrPromedios[i],"OrdenamientoDirecto.txt");
	}
	metodo.setN(this->numeroEstudiantes);
	metodo.ordenarPorDirecta();
    cout << "Realizando ordenamiento externo..." << endl;
    cout << "Archivos creados: particion1.txt, particion2.txt, OrdenExterno.txt" << endl;
}

void Menu::BuscarCalificacion(){

    int opcion;

    do {
    	system("cls");
        cout << "         ~ Submenú de Búsqueda ~              " << endl;
        cout << ">> 1. Búsqueda Binaria" << endl;
        cout << ">> 2. Busqueda Hash" << endl;
        cout << ">> 0. Volver al menú principal" << endl;

        cout << "Seleccione una opción de búsqueda: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            cout << "               ~ BUSQUEDA BINARIA ~            " << endl;
            cout << "Ingrese el promedio a buscar: ";

			float promedioBuscado;
			//cin >> promedioBuscado;
			Estudiante aux;
		//	promedioBuscado=this->crearUsuario.IngresoEnteros("promedio>>  ");
			cin>>promedioBuscado;
			busquedaBinaria(estudiantes, promedioBuscado,aux);
			//busquedaBinaria(estudiantes, promedioBuscado);
			if(aux.getNombre()!=""){
				
				cout<<"Se ha creado su informe de búsqueda con nombre Busqueda_Busqueda Binaria_Reporte_Calificaciones_2024.txt"<<endl;
				manejoArchivos.escribir_ResumenBusqueda("Busqueda Binaria",promedioBuscado,aux,profesor);
			}
			system("pause");
            break;
        }
        case 2: {
            cout << "               ~ BUSQUEDA HASH ~               " << endl;
            Estudiante aux;
            float promedioBuscado;
            cout << "Ingrese el promedio a buscar: ";
            cin >> promedioBuscado;
            try {
                tablaHash.buscar(promedioBuscado,aux);
                if(aux.getNombre()!=""){
				cout<<"Se ha creado su informe de búsqueda con nombre Busqueda_Busqueda Hash_Reporte_Calificaciones_2024.txt"<<endl;
				manejoArchivos.escribir_ResumenBusqueda("Busqueda Hash",promedioBuscado,aux,profesor);
				}
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
			system("pause");

            break;

        }
        case 0:
            // Volver al menú principal
            break;
        default:
            cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
            break;
        }
    } while (opcion != 0);  // Repetir mientras la opción no sea 0
}

// ... (resto de los métodos como antes)
/*void Menu::Login() {
    PedirDatosDocente();
    profesorLogueado = true;
    cout << "Login exitoso." << endl;
}*/
void Menu::Login() {
    /*cout << "Ingrese el nombre del docente: ";
    cin.ignore();
    nombreDocente=crearUsuario.leerLetras();

    long long int cedula;
    do {
        cedula = crearUsuario.IngresoEnteros("Ingrese la cedula del docente: ");
        //cedula = validar(cedula);
    } while (cedula == 0);

    cedulaDocente = to_string(cedula);*/
    profesor.leerDatosProfesor();
    profesorLogueado = true;
}

void Menu::PedirMateriaNRC() {
	this->profesor.registrarMateria();
}

void Menu::PedirNumeroEstudiantes() {
    cout << "Ingrese el numero de estudiantes: "<<endl;
    numeroEstudiantes=crearUsuario.IngresoEnteros("Numero alumnos: ");
    cout << "Ingrese el numero de notas a registrar: "<<endl;
    this->numNotas=crearUsuario.IngresoEnteros("Numero notas: ");
    notas.clear();
    delete[] arrPromedios;
    arrPromedios = new float[numeroEstudiantes];
    estudiantesIngresados = true;

}

void Menu::guardar_informacion(){
	string nombre,apellido,correo;
	float *notas_= new float(this->numNotas);
	float prom=0;
	int id=0;
	materia1=profesor.seleccionarMateria();
	for(int i=0; i< this->numeroEstudiantes;i++){
		cout<<endl;
		cout<<"R E G I S T R O "<<i+1<<endl;
		cout<<"Nombre:   ";
		nombre=this->crearUsuario.leerLetras();
		cout<<"Apellido: ";
		apellido=this->crearUsuario.leerLetras();
		//puedo poner que ingrese su correo
		notas_=IngresarNotas();
		cout<<endl;
        prom=this->CalcularPromedio(notas_, this->numNotas);
        arrPromedios[i]=prom;
        correo=crearCorreo(nombre,apellido);
        id=i+1;
        Estudiante estudiante(nombre,apellido,notas_,correo,prom,id);
        this->estudiantes.insertarAlFinal(estudiante);
        this->tablaHash.insertar(prom, estudiante); 

	}
}
float* Menu::IngresarNotas() {
	float *notas=new float(this->numNotas);
	float suma=0;
	float val=0;
        for(int i=0; i<this->numNotas; i++){
        cout<<"Nota "<<i+1<<" : ";
        //val=this->crearUsuario.leerFlotantes();
        cin>>val;
        while(val>20 || val<= 0){
        	cout<<" Fuera de rango, admite valores entre 1-20"<<endl;
        	//val=this->crearUsuario.leerFlotantes();
        	cout<<"Nota "<<i+1<<" : ";
        	cin>>val;
		}
			notas[i]=val;
		}
    return notas;
}

void Menu::AlmacenarDatos() {
 
	manejoArchivos.escribir_Encabezado(materia1.getNombre(),materia1.getCodigo(), numNotas);
    arrPromedios = new float[numeroEstudiantes];

    Nodo<Estudiante>* actual = estudiantes.getCabeza();
    int i = 0;

    while (actual != nullptr) {
        float promedio = CalcularPromedio(actual->dato.get_notas(), numNotas);
        arrPromedios[i] = promedio;

        manejoArchivos.escribir_Info_Alumnos(i, actual->dato.getNombre(), actual->dato.getApellido(), actual->dato.getCorreo(), actual->dato.get_notas(), numNotas, promedio);

        actual = actual->siguiente;
        i++;
    }
	manejoArchivos.escribir_Resumen(arrPromedios, numeroEstudiantes, profesor.getNombre(), std::to_string(profesor.getCedula()));


    std::cout << "Datos almacenados exitosamente." << std::endl;
}

float Menu::CalcularPromedio() {
    float suma = 0.0;
    for (int i = 0; i < numeroEstudiantes; ++i) {
        suma += arrPromedios[i];
    }
    return suma / numeroEstudiantes;
}

float Menu::CalcularPromedio(float* n, int numNotas) {
    float suma = 0.0;
    for (int i = 0; i < numNotas; ++i) {
        suma += n[i];
    }
    return suma / numNotas;
}


#endif // MENU_H
