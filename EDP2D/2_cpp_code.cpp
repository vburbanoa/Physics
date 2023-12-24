//Difusión en 2D
#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Función para calcular la nueva temperatura de la placa
vector<vector<float> > calcular_temperatura(vector<vector<float> > &placa, float v, float dt, float dx, string tipo_frontera) {
    int N = placa.size();

    vector<vector<float> > nueva_placa = placa;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (i == 0) {
                nueva_placa[0][j] = tipo_frontera == "periodica" ? placa[N-2][j] : (tipo_frontera == "abierta" ? placa[1][j] : placa[0][j]);
            }
            else if (i == N-1) {
                nueva_placa[N-1][j] = tipo_frontera == "periodica" ? placa[1][j] : (tipo_frontera == "abierta" ? placa[N-2][j] : placa[N-1][j]);
            }
            else if (j == 0) {
                nueva_placa[i][0] = tipo_frontera == "periodica" ? placa[i][N-2] : (tipo_frontera == "abierta" ? placa[i][1] : placa[i][0]);
            }
            else if (j == N-1) {
                nueva_placa[i][N-1] = tipo_frontera == "periodica" ? placa[i][1] : (tipo_frontera == "abierta" ? placa[i][N-2] : placa[i][N-1]);
            }
            else { 
                nueva_placa[i][j] = placa[i][j] + v * dt / (dx * dx) * (placa[i+1][j] + placa[i-1][j] + placa[i][j+1] + placa[i][j-1] - 4 * placa[i][j]);
            }
        }
           
    }

    return nueva_placa;
}


int main(){

    // Parámetros
    float L = 1.0; // Longitud del lado de la placa en metros
    float v = 1E-4; // en m^2/s
    float dx = 0.01; // Espaciado de la grilla
    float dt = 0.1 * dx * dx / v; // Paso de tiempo en segundos
    cout<<"dt = "<<dt<<endl;
    int N = L/dx; // Número de puntos en la grilla
    cout<<"N = "<<N<<endl;
    float t_0 = 0.0; // Tiempo inicial
    float t_f = 2500.0; // Tiempo final
    int steps = (t_f - t_0) / dt;
    cout<<"steps = "<<steps<<endl;

    // Temperaturas
    float T_0 = 50.0; // Temperatura inicial de la placa
    float T_1 = 100.0; // Temperatura del cuadrado

    // Posiciones del cuadrado
    float a = 0.2/dx, b = a + 0.2/dx; // Posiciones x del cuadrado
    float c = ((L/2) - 0.1)/dx, d = c + 0.2/dx; // Posiciones y del cuadrado
    // Matriz de la placa
    vector<vector<float> >  placa(N, vector<float>(N, T_0)); 
 
    // Establecer condiciones iniciales
    for (int i = c; i <=d; i++) {
        for(int j = a; j <= b; j++) {
            placa[i][j] = T_1;
        }
    }

    string tipo_frontera = "periodica"; // "fija", "periodica", "abierta"
    
    for (int c = 0; c <= steps; c++) {
        float t = c * dt;
        // imprimir cada 1000 pasos 
        if (c % 1000 == 0) {
        //cout << "t = " << t << endl;
        ofstream file;
        string folder = tipo_frontera; // nombre de la carpeta es el tipo de frontera
        string filename = folder + "/t_" + to_string(static_cast<int>(t)) + ".txt";
        file.open(filename);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                file << placa[i][j] << " ";
            }
            file << "\n";
        }
        file.close();
}
    // Actualizar la placa con la nueva temperatura
    placa = calcular_temperatura(placa, v, dt, dx, tipo_frontera);
}
}