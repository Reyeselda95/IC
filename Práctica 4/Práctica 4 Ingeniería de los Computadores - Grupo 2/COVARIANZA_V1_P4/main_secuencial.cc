// Tareas 1-Aplicación en OpenMP
// 2 - Salida por fichero de los resultados.
// 

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

vector<vector<vector<double> > > matrices;

//Muestra el tiempo de uso de la CPU desde el comienzo de la aplicación
void mostrarMatriz(vector<vector<double> >& dst);

double CPU_time(clock_t start)
{
  double devolver;
  devolver=(start-clock())/ (double)CLOCKS_PER_SEC;
  if(devolver<0){
    return -1*devolver;
  }
  else{
    return devolver;
  }
}

//computes row[i] - val for all i;
// sustrae a un vector un valor que se para por parametro que normalmente es su media
void subtract(vector<double> row, double val, vector<double>& dst) {
    int chunk=1000;
    unsigned i = 0;
    for(i = 0; i < row.size(); i++) { 
      dst.push_back( row[i] - val);
    }
}

//calcula la media de un vector
double mean(vector<double> &data) {
    double mean = 0.0;
    unsigned i=0;
    int chunk=1000;
    
    for(i=0; (i < data.size());i++) {
      mean =mean+ data[i];
    }

    mean = mean/data.size();
    return mean;
}



// Crea la traspuesta en otro vector que se para por parametro
void traspuesta(vector<vector<double> > & m,vector<vector<double> > & t){
    int colLim=m[0].size();
    int filLim=m.size();
    int i=0;
    for( i=0;i<colLim; i++){
      vector <double> relleno;
      int j=0;
      
      for( j=0;j<filLim;j++){
	relleno.push_back( m[j][i]);
      }
      t.push_back(relleno);
    }   
}

//multiplica una matriz por otra, se da por supuesto que las matrices son compatibles,
//ya que normalmente se multiplica por su trapuesta
void multiplicarMatrices(vector<vector<double> > & m,vector<vector<double> > & t,vector<vector<double> > & resul){
  int colLim=m[0].size();
  int filLim=m.size();  
  int i=0;
  
  for (i=0;i<filLim;i++){
    int j=0;
    vector <double> relleno;  
    for (j=0;j<filLim;j++) { 
      int k=0;
      int chunk=1000;
      relleno.push_back(0);
      for (k=0;k<colLim;k++){
	relleno[j]=relleno[j]+m[i][k]*t[k][j];
      }       
    }
    resul.push_back(relleno);
  }
}

//multiplica la matriz final por un valor
void matrizCovarianza(vector<vector<double> > & m,double valor,vector<vector<double> > & t){
  int colLim=m[0].size();
  int filLim=m.size();
  
  for(int i=0;i<filLim; i++){
    vector <double> relleno;
    for(int j=0;j<colLim;j++){
      relleno.push_back( m[i][j]*valor);
    }
    t.push_back(relleno);
  }   
}

//ejecuta las ordenes para sacar covarianza de una matriz
void compute_covariance_matrix(vector<vector<double> > & d, vector<vector<double> > & dst) {
  
  //Aqui se guarda la traspuesta
  vector<vector<double> > t0;
  
  traspuesta(d,t0);//se saca la trapuesta para poner orden en t0
  
  vector<vector<double> > t1; 
  //se crea una matriz con la resta de la medias de cada vector
  for(unsigned i = 0; i < t0.size(); i++) {
    double y_bar = mean(t0[i]);
    vector<double> d_d_bar;
    subtract(t0[i], y_bar, d_d_bar);
    
    t1.push_back(d_d_bar);
  } 
  //multiplicar por su trapuesta
  vector<vector<double> > t2; 
  //se obtiene la trapuesta para multiplicar
  traspuesta(t1,t2);
  
  vector<vector<double> > t3;
      
  // se multiplica y se obtine el resultado en t3
  multiplicarMatrices(t1,t2,t3);
    
  double valor=(float)1/((float)t0[0].size());
  
  matrizCovarianza(t3,valor,dst);
}

//No es necesario paralelizar ya que no estamos teniendo en cuenta el tiempo de la lectura del fichero
vector<double> procesarLinea(string linea){
  vector<double> numeros;
  string sb;
  size_t p1=0;
  size_t p2=linea.find(" ");
  size_t p3;
  float num;
  bool terminar=false;
  while(terminar==false){
    if(p2==string::npos){
      terminar=true;
    }else{
      p3=p2-p1;
      sb=linea.substr(p1,p3);

      num=atof(sb.c_str());
      numeros.push_back(num);
      p1=p2;
      p2=linea.find(" ",p1+1);
    }
  }
  size_t tam=linea.length();
  p3=tam-p1;
  sb=linea.substr(p1,p3);
  num=atof(sb.c_str());
  numeros.push_back(num);
  
  return numeros;
}

//Lee las matrices que le pasas por parametro
//No es necesario de paralelizar ya que no estamos teniendo en cuenta el tiempo de lectura para el problema
void readMatrices(string nombre_fichero)
{
  int num_matriz = 0;
  string linea;
  ifstream file(nombre_fichero.c_str());

  if(file.is_open())
  {
    getline( file,linea);
    vector< vector <double> > matriz;
    while(!file.eof() || !linea.empty())
    {
      if(!linea.empty())
      {
	vector<double> numeros=procesarLinea(linea);
	matriz.push_back(numeros);
      }else{
	matrices.push_back(matriz);
	matriz.clear();
      }
      
      getline( file,linea);
    }
    file.close();
  }
  else
  {
    cout << "Problema al abrir el fichero" <<endl;
  }
}

//cambiar a salida por fichero
void mostrarMatriz(vector<vector<double> > & matriz)
{
  for(unsigned int i= 0;i<matriz.size();i++){
    for(unsigned int j=0;j<matriz[i].size();j++){
      cout << matriz[i][j] <<" ";
    }
    cout <<endl;
  }
  cout <<endl;
}

int main(int argc,const char* argv[])
{
  if(argc == 2)
  {
    clock_t start;
    readMatrices(argv[1]);
    start = clock();
    cout << "Tiempo de comienzo de la aplicacion: " <<CPU_time(start) <<endl;
    start = clock();
    
    int chunk=10;
    
    unsigned int i=0;
    vector< vector <double> > resuelta;

    for(i=0;i<matrices.size();i++)
    {
      compute_covariance_matrix(matrices[i],resuelta);
      resuelta.clear();
    }
    cout << "Tiempo de finalización de la aplicación: " << (double)CPU_time(start) <<endl;
  }else{
    cout << "Número de parámetros incorrecto" <<endl;
    cout << "Formato $./main nombre_de_fichero" <<endl;
    return -1;
  }
  return 0;
}
