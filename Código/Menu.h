#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "IngresoDatos.h"
#include "ValidacionCedula.h"
#include "Estudiante.h"
#include "Pedido.h"
#include "Producto.h"
#include "ManejoJson.h"
#include "Lista.h"
using namespace std;
class Menu
{
private:
    Pedido pedido;
    Lista<Estudiante> Listausuarios;
    Lista<Producto> ListaProductos;
    string comprobante;
public:
    Menu(){
        ListaProductos.insertarAlFinal(Producto("Pizza", 1.00,1));
        ListaProductos.insertarAlFinal(Producto("Salchipapa", 1.50,2));
        ListaProductos.insertarAlFinal(Producto("Agua", 0.50,3));
        ListaProductos.insertarAlFinal(Producto("Hamburguesa", 2.00,4));
        ListaProductos.insertarAlFinal(Producto("Refresco", 0.40,5));
        ListaProductos.insertarAlFinal(Producto("Papipollo", 2.25,6));
        ListaProductos.insertarAlFinal(Producto("Hot dog", 1.25,7));
        ListaProductos.insertarAlFinal(Producto("Costillas de cerdo", 2.50,8));
        ListaProductos.insertarAlFinal(Producto("Chuleta", 2.50,9));
        ListaProductos.insertarAlFinal(Producto("Pechuga con papas fritas", 2.50,10));
        ListaProductos.insertarAlFinal(Producto("Alitas de BBq", 2.50,11));
        ListaProductos.insertarAlFinal(Producto("Tigrillo", 2.25,12));

    };
    void MostrarMenuPrincipal();
    bool MenuLogin();
    int obtenerIS_CC();
    void crearCuenta();
    void mostrarMenuFunciones();
    void mostrarMenuCarta();
    void mostrarCanasta();
    void pagarPedido();
    void eliminarProducto();
};

int Menu::obtenerIS_CC(){
    int cc=0;
    IngresoDatos i;
    do{
    cout<<"BIENVENIDOS A ESPExpress"<<endl;
    cout<<"Usted desea..."<<endl;
    cout<<"1. Iniciar Sesion"<<endl;
    cout<<"2. Crear Cuenta"<<endl;
    cout<<"3. Salir"<<endl;
    cc=i.IngresoEnteros("Opcion: ");
    switch(cc){
    case 1:
        if(MenuLogin()){
        	system("cls");
            mostrarMenuFunciones();
        }
        break;
    case 2:
        crearCuenta();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout<<"La opcion no existe.";
    }
    }while(cc!=3);
    return cc;
}

bool Menu::MenuLogin(){
	short min=8;
	short max=15;
	cargarEstudiantes(this->Listausuarios);
    IngresoDatos datosDelUsuario;
    std::string contrasenia;
    bool login=false;
    int ced,opcion;
    ced=datosDelUsuario.IngresoEnteros("Usuario: ");
    cout<<"Contrasenia: ";
    contrasenia=string{datosDelUsuario.ingresoContra(8,15)};
    Estudiante aux(" ",ced,contrasenia);
    Estudiante aux1;
    Listausuarios.obtenerUserBuscado(aux1,ced);
    if(aux.validarPersona_userPswd(aux,aux1)){
            pedido.setCliente(aux1);
            cout<<"Claves ingresadas correctas"<<endl;
			cout << "\nPresione  Enter  para continuar...";
			getchar();
			getchar();
        login=true;
    }else{
    	system("cls");
    	Listausuarios.~Lista();
        cout<<"Credenciales incorrectas"<<endl;
        opcion=datosDelUsuario.IngresoEnteros("1. Volver al inicio\n2. Volver a intentar\n");
        if(opcion==1){
        	system("cls");
            login= false;
        }else if(opcion == 2){

            return MenuLogin();
        }
    }
    return login;
}
void Menu::MostrarMenuPrincipal(){
    obtenerIS_CC();
}
void Menu::crearCuenta(){
	bool login=false;
	IngresoDatos datosDelUsuario;
	int opcion=0;
	system("cls");
    IngresoDatos datosCrear;
    string contrasenia, nombre;
    long long int cedula;
    cout<<"Usted a seleccionado creación de cuenta, su cédula se convertirá en su usuario para iniciar Sesión."<<endl;
    cout<<"Por favor, ingrese los siguiente sdatos."<<endl;
    cout<<"Nombre:  ";
    getline(cin,nombre);
    cedula=datosCrear.IngresoEnteros("Cédula de identidad: ");
    validar(cedula);
    cout<<"Por favor cree su contraseña (Debe contener minimo 8 digitos y máximo 15): ";
    getline(cin,contrasenia);
    if(contrasenia.size()<8 || contrasenia.size()>15){
    	cout<<"Rango no permitido, contraseña insegura"<<endl;
    	system("pause");
    	opcion=datosDelUsuario.IngresoEnteros("1. Volver al inicio\n2. Volver a intentar\n");
        if(opcion==1){
        	system("cls");
            login= false;
        }else if(opcion == 2){

            return crearCuenta();
        }
	}else{
	Estudiante aux(nombre,cedula,contrasenia);
    fflush(stdin);
    if(aux.CrearCuenta(aux)){
    	//conexión a Json usado como base de datos
        crearNuevoUsuario_BBD(aux.getUsuario(), aux.getPswd(), aux.getNombre());
    }else{
        cout<<"Vuelva a intentarlo";
    }
			cout << "\nPresione  Enter  para continuar...";
			getchar();
			getchar();
	system("cls");
	}

}
void Menu::mostrarMenuFunciones(){
	system("cls");
    int cc=0;
    IngresoDatos i;
    do{
    cout<<"ESPExpress"<<endl;
    cout<<"Usted desea..."<<endl;
    cout<<"1. Iniciar orden."<<endl;
    cout<<"2. Canasta de compras."<<endl;
    cout<<"3. Ver comprobante de pago."<<endl;
    cout<<"4. Salir."<<endl;
    cc=i.IngresoEnteros("Opcion: ");
    switch(cc){
    case 1:
        mostrarMenuCarta();
        break;
    case 2:
        mostrarCanasta();
        break;
    case 3:
    	cout<<endl;
        cout<<comprobante<<endl;
        system("pause");
			mostrarMenuFunciones();
        break;
    case 4:
        exit(0);
        break;
    default:
        cout<<"La opcion no existe.";
    }
    }while(cc!=3);
}

void Menu::mostrarMenuCarta() {
	system("cls");
	//cargar la Lista de Productos
    //aquí se debería imprimir la lista de productos

    IngresoDatos orden;
    int opcion;
    cout <<"Menu de comida: " << endl;
    ListaProductos.imprimirMenu();
    cout <<"13. Regresar" << endl;
    do {
        opcion = orden.IngresoEnteros("Ingrese las opciones que desee: ");
        cout << endl;
        switch(opcion){
            case 1:
                pedido.agregarProducto(Producto("Pizza",1.00,1));
                cout <<"Pizza agregada." << endl;
                break;
            case 2:
                pedido.agregarProducto(Producto("Salchipapa",1.50,2));
                cout <<"Salchipapa agregada." << endl;
                break;
            case 3:
                pedido.agregarProducto(Producto("Agua",0.50,3));
                cout <<"Agua agregada." << endl;
                break;
            case 4:
                pedido.agregarProducto(Producto("Hamburguesa",2.00,4));
                cout <<"Hamburguesa agregada." << endl;
                break;
            case 5:
                pedido.agregarProducto(Producto("Refresco",0.40,5));
                cout <<"Refresco agregada." << endl;
                break;
            case 6:
                pedido.agregarProducto(Producto("Papipollo", 2.25,6));
                cout <<"Papipollo agregada." << endl;
                break;
            case 7:
                pedido.agregarProducto(Producto("Hot dog", 1.25,7));
                cout <<"Hot dog agregada." << endl;
                break;
            case 8:
                pedido.agregarProducto(Producto("Costillas de cerdo", 2.50,8));
                cout <<"Costillas de cerdo agregada." << endl;
                break;
            case 9:
                pedido.agregarProducto(Producto("Chuleta", 2.50,9));
                cout <<"Chuleta agregada." << endl;
                break;
            case 10:
                pedido.agregarProducto(Producto("Pechuga con papas fritas", 2.50,10));
                cout <<"Pechuga con papas fritas agregada." << endl;
                break;
            case 11:
                pedido.agregarProducto(Producto("Alitas de BBq", 2.50,11));
                cout <<"Alitas de BBq agregada." << endl;
                break;
            case 12:
                pedido.agregarProducto(Producto("Tigrillo", 2.25,12));
                cout <<"Tigrillo agregada." << endl;
                break;
            case 13:
                mostrarMenuFunciones();
                break;
        }
    }while(opcion != 13);
}

void Menu::mostrarCanasta() {
    IngresoDatos ordenInd;
    int opcion;
	cout<<"Su pedido por ahora "<<endl;
	system("cls");
	if(pedido.calcularTotal()==0){
	cout<<"Su pedido por ahora"<<endl;
	cout<<"se encuentra vacío, primero realice su orden por favor"<<endl;
			cout << "\nPresione  Enter  para continuar...";
			getchar();
			getchar();
			system("cls");
	}else{
	pedido.mostrarPedido();
	cout<<"\n1. Continuar"<<endl;
	cout<<"2. Agregar mas comida"<<endl;
	cout<<"3. Quitar comida."<<endl;
	cout<<"4. Regresar al menu principal."<<endl;
	opcion=ordenInd.IngresoEnteros("Ingrese una opcion: ");
	switch(opcion){
    case 1:
        pagarPedido();
        break;
    case 2:
        mostrarMenuCarta();
        break;
    case 3:
        eliminarProducto();
        break;
    case 4:
        mostrarMenuFunciones();
        break;
	}
	}

}
void Menu::pagarPedido(){
    IngresoDatos orden;
    int opcion;
	if(pedido.calcularTotal()==0){
		cout<<"Su pedido está vacío, tenemos un extenso menu "<<endl;
		cout<<" Realiza tu orden primero. "<<endl;
	}else{
	cout<<endl<<"1. Pagar"<<endl;
    cout<<"2. Volver al menu principal"<<endl;
    opcion = orden.IngresoEnteros("Elija una opcion: ");
    switch(opcion){
    case 1:
        pedido.pagar();
        comprobante=pedido.generarComprobante();
        cout<<comprobante;
        cout<<"Su pedido ha sido pagado de forma exitosa."<<endl;
        guardarPedido(pedido.getCliente().getNombre(), pedido.getProductos(), pedido.calcularTotal(), "Pagado", pedido, pedido.getCliente().getUsuario());
        pedido=Pedido();
        system("pause");
        break;
    case 2:
        mostrarMenuFunciones();
        break;
    }
	}
}
void Menu::eliminarProducto() {
    IngresoDatos ordenEliminar;
    int opcion;
    cout << "Seleccione el producto que desea eliminar: " << endl;
    ListaProductos.imprimirMenu();
    cout<<"13. Ver canasta"<<endl;
    do{
    opcion = ordenEliminar.IngresoEnteros("Ingrese el número del producto que desea eliminar: ");
    Producto eliminarPlato;
    switch (opcion) {
    case 1:
        eliminarPlato = Producto("Pizza", 1.00, 1);
        break;
    case 2:
        eliminarPlato = Producto("Salchipapa", 1.50, 2);
        break;
    case 3:
        eliminarPlato = Producto("Agua", 0.50, 3);
        break;
    case 4:
        eliminarPlato = Producto("Hamburguesa", 2.00, 4);
        break;
    case 5:
        eliminarPlato = Producto("Refresco", 0.40, 5);
        break;
     case 6:
        eliminarPlato = Producto("Papipollo", 2.25,6);
        break;
     case 7:
        eliminarPlato = Producto("Hot dog", 1.25,7);
        break;       
    case 8:
        eliminarPlato = Producto("Costillas de cerdo", 2.50,8);
        break;
    case 9:
        eliminarPlato = Producto("Chuleta", 2.50,9);
        break;
    case 10:
        eliminarPlato = Producto("Pechuga con papas fritas", 2.50,10);
        break;
    case 11:
        eliminarPlato = Producto("Alitas de BBq", 2.50,11);
        break;
    case 12:
        eliminarPlato = Producto("Tigrillo", 2.25,12);
        break;
    case 13:
        mostrarCanasta();
        break;
    }
    pedido.eliminarProducto(eliminarPlato);
    }while(opcion=!13);
}
#endif
