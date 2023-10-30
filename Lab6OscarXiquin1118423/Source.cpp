#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class StopWatch {
public:
	void start() {
		start_time = std::chrono::high_resolution_clock::now();
		is_running = true;
	}

	void stop() {
		end_time = std::chrono::high_resolution_clock::now();
		is_running = false;
	}

	double elapsed_seconds() {
		std::chrono::duration<double> elapsed;
		if (is_running) {
			elapsed = std::chrono::high_resolution_clock::now() - start_time;
		}
		else {
			elapsed = end_time - start_time;
		}
		return elapsed.count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
	bool is_running = false;
};

struct ord {
	int nationalnumber;
	string namepokemon;
	int generacion;
};

class Ordenar {
public:
	void selectionSort(vector<ord>& lista, const string& eleccion){
		int n = lista.size();

		for (int i = 0; i < n - 1; ++i) {
			int minimo = i;

			for (int j = i + 1; j < n; ++j) {
				if (eleccion == "nationalnumber") {
					if (lista[j].nationalnumber < lista[minimo].nationalnumber) {
						minimo = j;
					}
				}
				if (eleccion == "namepokemon") {
					if (lista[j].namepokemon < lista[minimo].namepokemon) {
						minimo = j;
					}
				}
				if (eleccion == "generacion") {
					if (lista[j].generacion < lista[minimo].generacion) {
						minimo = j;
					}
				}


			}

			swap(lista[i], lista[minimo]);

		}
	}

	void QuickSort(vector<ord>& pokemonList, const string& key, int left, int right) {
		if (left < right) {
			int pivotIndex = left;
			int pivotNewIndex = left;

			for (int i = left + 1; i <= right; i++) {
				if (key == "nationalnumber") {
					if (pokemonList[i].nationalnumber< pokemonList[pivotIndex].nationalnumber) {
						pivotNewIndex++;
						std::swap(pokemonList[i], pokemonList[pivotNewIndex]);
					}
				}
				else if (key == "namepokemon") {
					if (pokemonList[i].namepokemon < pokemonList[pivotIndex].namepokemon) {
						pivotNewIndex++;
						std::swap(pokemonList[i], pokemonList[pivotNewIndex]);
					}
				}
				else if (key == "generacion") {
					if (pokemonList[i].generacion < pokemonList[pivotIndex].generacion) {
						pivotNewIndex++;
						std::swap(pokemonList[i], pokemonList[pivotNewIndex]);
					}
				}
			}

			std::swap(pokemonList[pivotIndex], pokemonList[pivotNewIndex]);

			QuickSort(pokemonList, key, left, pivotNewIndex - 1);
			QuickSort(pokemonList, key, pivotNewIndex + 1, right);
		}

	}

	void shellsort(vector<ord>& pokemonList, const string& key) {
		int n = pokemonList.size();
		for (int gap = n / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i++) {
				ord temp = pokemonList[i];
				int j = i;
				if (key == "nationalnumber") {
					while (j >= gap && pokemonList[j - gap].nationalnumber > temp.nationalnumber) {
						pokemonList[j] = pokemonList[j - gap];
						j -= gap;
					}
				}
				else if (key == "namepokemon") {
					while (j >= gap && pokemonList[j - gap].namepokemon > temp.namepokemon) {
						pokemonList[j] = pokemonList[j - gap];
						j -= gap;
					}
				}
				else if (key == "generacion") {
					while (j >= gap && pokemonList[j - gap].generacion > temp.generacion) {
						pokemonList[j] = pokemonList[j - gap];
						j -= gap;
					}
				}
				pokemonList[j] = temp;
			}
		}
	}

	void PrintPokemonList(const vector<ord>& pokemonList) {
		for (const ord& pokemon : pokemonList) {
			cout << pokemon.nationalnumber << ", " << pokemon.namepokemon << ", " << pokemon.generacion << std::endl;
		}
	}
};


class list {
private:
	struct Node {
		string element;
		Node* next = nullptr;
	};

	Node* head = nullptr;
	Node* tail = nullptr;

	int size = 0;

public:

	bool isEmpty() {
		return head == nullptr;
	}

	void add(string n) {
		++size;

		if (isEmpty()) {
			head = tail = new Node{ n };
		}
		else {
			tail->next = new Node{ n };
			tail = tail->next;
		}

	}


	void limpiar() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}

	void print() {
		Node* current = head;
		while (current) {
			cout<< current->element << " ";
			current = current->next;
		}
		cout << endl;
	}
	

	void leerarchivo() {
		int s = 1;
		ifstream archivo("GenercionPokemon.txt");

		if (!archivo.is_open()) {
			cerr << "No se pudo abrir el archivo: " << endl;
		}

		string linea;

		vector <string> cancion;

		while (getline(archivo, linea)) {
			cancion.push_back(linea);
			s++;
		}

		
		for (int i = 0; i < cancion.size(); i++) {
			add(cancion[i]);
		}
		archivo.close();
	}

	vector<string> convertiravector() {
		vector<string> VectorCanciones;

		Node* current = head;
		while (current != nullptr) {
			VectorCanciones.push_back(current->element);
			current = current->next;
		}

		
		return VectorCanciones;
	}


	
	
};




void escribir(int veces) {
	ofstream archivo;
	string nombre, nationalnumber, generacion;
	int contador = 0;

	archivo.open("BasePokemon.txt", ios::out);
	if (archivo.fail()) {
		cout << "No se pudo crear el archivo";
		exit(1);
	}
	
	while(contador < veces){

		bool digitos;

		do {

			cout << "Ingrese el numero nacional del pokemon" << endl;
			cin >> nationalnumber;

			digitos = true;

			for (char caracter : nationalnumber) {
				if (!isdigit(caracter)) {
					digitos = false;
					break;
				}
			}

		} while (!digitos);
		
		archivo << nationalnumber << ", ";


		cout << "Ingrese el nombre del pokemon" << endl;
		cin >> nombre;
		archivo << nombre << ", ";

		bool condicion = false;
		bool digit = false;
		do {
			cout << "Ingrese la generacion del pokemon" << endl;
			cin >> generacion;

			if (generacion.length() == 1) {
				condicion = true;
			}
			else {
				condicion = false; 
			}

			for (char caracter2 : generacion) {
				if (!isdigit(caracter2)) {
					digitos = true;
					break;
				}
			}
			
		} while (!condicion);

		archivo << generacion << "-" << endl;
		
		cout << endl;

		contador++;

	}
	
	archivo.close();
	
	
}


void pausa() {
	string uno;
	cin >> uno;
}

int main() {
	/*int numero;
	cout << "Ingrese el numero de pokemons que desea :) " << endl;
	cin >> numero;
	escribir(numero);*/




	list mylyst;

	mylyst.leerarchivo();

	vector<string> milista = mylyst.convertiravector();

	vector<ord> pokemones;
	for (int i = 0; i < milista.size(); i++) {
		size_t posdoblebarra = milista[i].find(",");

		ord list;

		string can = milista[i].substr(0, posdoblebarra);

		if (milista[i].substr(0, posdoblebarra).find_first_not_of("0123456789") == string::npos) {
			list.nationalnumber = stoi(can);
		}
		

		size_t posprimerabarra = milista[i].find(",");
		size_t possegundabarra = milista[i].find(",", posprimerabarra + 1);
		string art = milista[i].substr(posprimerabarra + 2, possegundabarra - posprimerabarra - 2);
		list.namepokemon = art;

		size_t postercera = milista[i].find(",", milista[i].find(",") + 2);


		string duracion = milista[i].substr(postercera + 2);
		list.generacion = stoi(duracion);
	

		pokemones.push_back(list);
	}

	StopWatch stopwatch;
	
	Ordenar resultado;
	
	int opcion = 0;

	while (opcion != 5) {
		system("cls");
		cout << "MENU DE ELECCION" << endl;
		cout << "1. Mostrar lista original" << endl;
		cout << "2. Ordenar por nationalnumber" << endl;
		cout << "3. Ordenar por nombre del pokemon" << endl;
		cout << "4. Ordenar por generacion" << endl;
		cout << "5. Salir" << endl;
		cout << "Elija una opcion" << endl;

		cin >> opcion;

		switch (opcion) {
		case 1:
			system("cls");

			cout << "Archivo" << endl;
			resultado.PrintPokemonList(pokemones);
			cout << "presione cualquier letra para regresar al menu" << endl;

			pausa();
			break;
		case 2:
			system("cls");

			cout << "Ordenado por nationalnumber" << endl;
			cout << endl;
			cout << "selection sort" << endl;
			stopwatch.start();
			resultado.selectionSort(pokemones, "nationalnumber");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);

			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;
			cout << "Quick sort" << endl;

			stopwatch.start();
			resultado.QuickSort(pokemones, "nationalnumber", 0, pokemones.size() - 1);
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;
			cout << "Shellsort" << endl;

			stopwatch.start();
			resultado.shellsort(pokemones, "nationalnumber");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << "presione cualquier letra para regresar al menu" << endl;

			pausa();

			break;
		case 3:
			system("cls");


			cout << "Ordenado por namepokemon" << endl;
			cout << endl;
			cout << "selection sort" << endl;
			stopwatch.start();
			resultado.selectionSort(pokemones, "namepokemon");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			

			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;
			cout << "Quick sort" << endl;
			stopwatch.start();
			resultado.QuickSort(pokemones, "namepokemon", 0, pokemones.size() - 1);
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;

			cout << "Shellsort" << endl;
			stopwatch.start();
			resultado.shellsort(pokemones, "namepokemon");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << "presione cualquier letra para regresar al menu" << endl;
			pausa();

			break;
		case 4:
			system("cls");

			cout << "Ordenado por generacion" << endl;
			cout << endl;
			cout << "selection sort" << endl;
			stopwatch.start();
			resultado.selectionSort(pokemones, "generacion");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;

			cout << "Quick sort" << endl;
			stopwatch.start();
			resultado.QuickSort(pokemones, "generacion", 0, pokemones.size() - 1);
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << endl;


			cout << "Shellsort" << endl;
			stopwatch.start();
			resultado.shellsort(pokemones, "generacion");
			stopwatch.stop();
			resultado.PrintPokemonList(pokemones);
			cout << "Tiempo de ejecucion fue: " << stopwatch.elapsed_seconds() << " segundos" << endl;
			cout << "presione cualquier letra para regresar al menu" << endl;

			pausa();

			break;
		case 5:
			break;
		default:
			system("cls");

			cout << "La opcion elegida no es correcta" << endl;
			cout << "presione cualquier letra para regresar al menu" << endl;

			pausa();

			break;
		}
		
	}
	


	

	
	

	



	


	


	


	




}
