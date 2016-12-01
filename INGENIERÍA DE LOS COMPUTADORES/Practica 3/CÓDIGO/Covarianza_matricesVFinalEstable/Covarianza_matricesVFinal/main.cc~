// Tareas 1-Aplicación en OpenMP
// 2 - Salida por fichero de los resultados.
// 

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <omp.h> //Libreria OpenMP
using namespace std;

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

void outer_product(vector<double> row, vector<double> col, vector<vector<double> >& dst) {


    for(unsigned i = 0; i < row.size(); i++) {
        vector <double> relleno;
        for(unsigned j = 0; j < col.size(); j++) {
            relleno.push_back( row[i] * col[j]);
	}
	dst.push_back(relleno);
    }
    
    
    
}

//computes row[i] - val for all i;
void subtract(vector<double> row, double val, vector<double>& dst) {
    for(unsigned i = 0; i < row.size(); i++) {
        dst.push_back( row[i] - val);
    }
}


double mean(vector<double> &data) {
    double mean = 0.0;

    for(unsigned i=0; (i < data.size());i++) {
        mean += data[i];
    }

    mean = mean/data.size();
    return mean;
}




void traspuesta(vector<vector<double> > & m,vector<vector<double> > & t){
    int colLim=m[0].size();
    int filLim=m.size();
   
       
    for(int i=0;i<colLim; i++){
        vector <double> relleno;
	for(int j=0;j<filLim;j++){
	      relleno.push_back( m[j][i]);
	}
	t.push_back(relleno);
    }   
}

void multiplicarMatrices(vector<vector<double> > & m,vector<vector<double> > & t,vector<vector<double> > & resul){
  int colLim=m[0].size();
  int filLim=m.size();  
  
  for (int i=0;i<filLim;i++){
      vector <double> relleno;  
      for (int j=0;j<filLim;j++) { 
	 
	 relleno.push_back(0);

         for (int k=0;k<colLim;k++){
	      relleno[j]=relleno[j]+m[i][k]*t[k][j];

          }       

       }
       resul.push_back(relleno);
    }
}

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


void compute_covariance_matrix(vector<vector<double> > & d, vector<vector<double> > & dst) {
  
   vector<vector<double> > t0;
   
   traspuesta(d,t0);
   
   vector<vector<double> > t1; 
   
   for(unsigned i = 0; i < t0.size(); i++) {
        double y_bar = mean(t0[i]);
        vector<double> d_d_bar;
        subtract(t0[i], y_bar, d_d_bar);
    	
        t1.push_back(d_d_bar);
	
    } 
    
    //mostrarMatriz(t);
    //multiplicar por su trapuesta
    vector<vector<double> > t2; 
    
    traspuesta(t1,t2);
    
    //mostrarMatriz(t2);
    
    vector<vector<double> > t3;
        
    
    multiplicarMatrices(t1,t2,t3);
    
    //mostrarMatriz(t3);
    
 
    ;
    double valor=(float)1/((float)t0[0].size());
    
    matrizCovarianza(t3,valor,dst);
}


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
	  //cout << sb << "|";
      
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
   //cout << sb << "|";
      
      
   //cout << endl;
   
   return numeros;
}

//Lee las matrices que le pasas por parametro
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
			    vector< vector <double> > resuelta;
			    //mostrarMatriz(matriz);
			    compute_covariance_matrix(matriz,resuelta);
			    //mostrarMatriz(resuelta);
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


//TODO cambiar a salida por fichero
void mostrarMatriz(vector<vector<double> > & matriz)
{
	for(unsigned int i= 0;i<matriz.size();i++)
	{
		for(unsigned int j=0;j<matriz[i].size();j++)
		{
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

		start = clock();
		cout << "Tiempo de comienzo de la aplicacion: " <<CPU_time(start) <<endl;
		
		readMatrices(argv[1]);

		cout << "Tiempo de finalización de la aplicación: " << (double)CPU_time(start) <<endl;
	}else{
		cout << "Número de parámetros incorrecto" <<endl;
		cout << "Formato $./main nombre_de_fichero" <<endl;
		return -1;
	}
	return 0;
}
