#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

struct Person {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    bool was_king;
    bool is_king;

    Person* left_child = nullptr;  // Primogénito
    Person* right_child = nullptr; // Segundo hijo
};

// Crear un nuevo nodo
Person* createNode(int id, const string& name, const string& last_name, char gender, int age, int id_father, bool is_dead, bool was_king, bool is_king) {
    Person* new_person = new Person{id, name, last_name, gender, age, id_father, is_dead, was_king, is_king};
    return new_person;
}

// Insertar nodo en el árbol
void insertNode(Person*& root, Person* new_person) {
    if (!root) {
        root = new_person;
        return;
    }

    if (new_person->id_father == root->id) {
        if (!root->left_child) {
            root->left_child = new_person;
        } else if (!root->right_child) {
            root->right_child = new_person;
        } else {
            cerr << "Error: Un nodo no puede tener más de dos hijos.\n";
        }
    } else {
        insertNode(root->left_child, new_person);
        insertNode(root->right_child, new_person);
    }
}

// Cargar árbol desde archivo CSV
void loadFromCSV(Person*& root, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "No se pudo abrir el archivo " << filename << ".\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, last_name, gender, age, id_father, is_dead, was_king, is_king;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, last_name, ',');
        getline(ss, gender, ',');
        getline(ss, age, ',');
        getline(ss, id_father, ',');
        getline(ss, is_dead, ',');
        getline(ss, was_king, ',');
        getline(ss, is_king, ',');

        Person* new_person = createNode(
            stoi(id),
            name,
            last_name,
            gender[0],
            stoi(age),
            stoi(id_father),
            stoi(is_dead),
            stoi(was_king),
            stoi(is_king)
        );
        insertNode(root, new_person);
    }
    file.close();
    cout << "Datos cargados desde " << filename << " exitosamente.\n";
}

// Mostrar línea de sucesión
void showSuccession(Person* node) {
    if (!node) return;

    if (!node->is_dead) {
        cout << "ID: " << node->id << ", Nombre: " << node->name << " " << node->last_name << ", Edad: " << node->age << endl;
    }

    showSuccession(node->left_child);
    showSuccession(node->right_child);
}

// Función auxiliar: encontrar primogénito vivo
Person* findFirstAliveChild(Person* node) {
    if (!node) return nullptr;
    if (node->left_child && !node->left_child->is_dead) return node->left_child;
    if (node->right_child && !node->right_child->is_dead) return node->right_child;
    return nullptr;
}

// Función auxiliar: buscar sucesor en los hermanos o ancestros
Person* findSuccessor(Person* node) {
    if (!node) return nullptr;

    // Buscar entre hermanos
    if (node->right_child && !node->right_child->is_dead) return node->right_child;

    // Subir al ancestro
    return findSuccessor(node->left_child);
}

// Asignar nuevo rey
void assignNewKing(Person* root) {
    if (!root) return;

    Person* current_king = nullptr;

    // Encontrar al rey actual
    function<void(Person*)> findKing = [&](Person* node) {
        if (!node) return;
        if (node->is_king) {
            current_king = node;
        }
        findKing(node->left_child);
        findKing(node->right_child);
    };

    findKing(root);

    if (!current_king) {
        cout << "No se encontró un rey actual.\n";
        return;
    }

    // Si el rey murió o es demasiado viejo
    if (current_king->is_dead || current_king->age > 70) {
        cout << "El rey actual ha muerto o ha superado los 70 años.\n";
        current_king->is_king = false;

        // Aplicar reglas de sucesión
        Person* new_king = nullptr;

        // Regla 1: Si tiene hijos, asignar primogénito vivo
        new_king = findFirstAliveChild(current_king);
        if (!new_king) {
            // Regla 2: Si no tiene hijos, buscar en el árbol del hermano
            new_king = findSuccessor(current_king->right_child);
        }
        if (!new_king) {
            // Regla 3: Si no hay sucesor directo, buscar entre ancestros
            new_king = findSuccessor(root);
        }

        if (new_king) {
            new_king->is_king = true;
            cout << "El nuevo rey es: " << new_king->name << " " << new_king->last_name << ".\n";
        } else {
            cout << "No se encontró un sucesor vivo.\n";
        }
    } else {
        cout << "El rey actual sigue vivo y no ha superado los 70 años.\n";
    }
}

// Modificar nodo
void modifyNode(Person* root, int id) {
    if (!root) return;

    if (root->id == id) {
        cout << "Modificando a: " << root->name << " " << root->last_name << endl;
        cout << "Nuevo nombre: ";
        cin >> root->name;
        cout << "Nuevo apellido: ";
        cin >> root->last_name;
        cout << "Nueva edad: ";
        cin >> root->age;
        cout << "Estado (0 = vivo, 1 = muerto): ";
        cin >> root->is_dead;
        cout << "Cambios realizados.\n";
        return;
    }

    modifyNode(root->left_child, id);
    modifyNode(root->right_child, id);
}

// Menú interactivo
void menu(Person*& root) {
    int option;
    do {
        cout << "\n=== Menú ===\n";
        cout << "1. Cargar árbol desde archivo CSV\n";
        cout << "2. Mostrar línea de sucesión\n";
        cout << "3. Asignar nuevo rey\n";
        cout << "4. Modificar nodo\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        cin >> option;

        switch (option) {
        case 1:
            loadFromCSV(root, "bin/family_tree.csv");
            break;
        case 2:
            showSuccession(root);
            break;
        case 3:
            assignNewKing(root);
            break;
        case 4: {
            int id;
            cout << "ID del nodo a modificar: ";
            cin >> id;
            modifyNode(root, id);
            break;
        }
        case 5:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (option != 5);
}

int main() {
    Person* root = nullptr;
    menu(root);
    return 0;
}
