#include <ginac/ginac.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
//#include <vector>
/*#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TApplication.h>*/

using namespace std;

const double GRAV_CONSTANT = 6.67E-11;


class vector_3d {
	double x, y, z;

	public:
		vector_3d();
		vector_3d(double, double, double);
		void set(double, double, double);
		double getX();
		double getY();
		double getZ();
		vector_3d unit();
		vector_3d cross(vector_3d);
		double dot(vector_3d);
		double magnitude();
		friend vector_3d operator*(const vector_3d, const double);
		friend vector_3d operator*(const double, const vector_3d);
		friend vector_3d operator+(const vector_3d, const vector_3d);
		friend vector_3d operator-(const vector_3d, const vector_3d);
		void print();
};

vector_3d::vector_3d(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vector_3d::vector_3d(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void vector_3d::set(double xPoint, double yPoint, double zPoint){
	this->x = xPoint;
	this->y = yPoint;
	this->z = zPoint;
}

double vector_3d::getX(){
	return this->x;
}

double vector_3d::getY(){
	return this->y;
}

double vector_3d::getZ(){
	return this->z;
}

vector_3d vector_3d::unit(){
	double magnitude = this->magnitude();
	return vector_3d(this->x/magnitude, this->y/magnitude, this->z/magnitude);
}

double vector_3d::magnitude() {
	return sqrt(this->dot(*this));
}

double vector_3d::dot(vector_3d other_vector) {
	return this->x * other_vector.x + this->y * other_vector.y + this->z * other_vector.z;
}

vector_3d vector_3d::cross(vector_3d other_vector) {
	return vector_3d(this->y * other_vector.z - this->z * other_vector.y, this->x * other_vector.z - this->z * other_vector.x, this->x * other_vector.y - this->y*other_vector.x);
}

vector_3d operator*(vector_3d vec, double scalar) {
	return vector_3d(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

vector_3d operator*(double scalar, vector_3d vec) {
	return vector_3d(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

vector_3d operator+(const vector_3d vec1, const vector_3d vec2) {
	return vector_3d(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vector_3d operator-(const vector_3d vec1, const vector_3d vec2) {
	return vector_3d(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

void vector_3d::print() {
	cout << "x: " << this->x << "\ty: " << this->y << "\tz:" << this-> z << endl;
}

struct object {
	string name;
	vector_3d position;
	vector_3d velocity;
	vector_3d acceleration;
	double mass;
};

vector_3d forceGravity(object planet_from, object planet_to) {
	vector_3d r = planet_to.position - planet_from.position;

	return -GRAV_CONSTANT * planet_from.mass / r.dot(r) * r.unit();

}

//______________________________________________________________________________
//_______________________________Variables______________________________________
//______________________________________________________________________________

	double elapsedTime = 0;
	double timeStep = 120;
	double simulationTime = 1000000;

	vector<vector<double> > xPosition;
	vector<vector<double> > yPosition;
	vector<vector<double> > zPosition;

	int dimensions = 3;

	double dataPoints = simulationTime / timeStep;

	ofstream fileOutput;

	vector<string> bodyNames;

	int dataSet;

//______________________________________________________________________________
//______________________________Position Math___________________________________
//______________________________________________________________________________

void positionCalculation(void){

	cout << endl << endl << endl << "Which system would you like to model? Please input the number to the left of your choice. " << endl << "The options are:" << endl;
	cout << "1	Jupiter and its moons" << endl;
	cout << "2	Pluto and its moons" << endl;
	cin >> dataSet;
	
	if(dataSet == 1){

		static const int NUM_BODIES = 5;
			static object bodies[NUM_BODIES];

		bodies[0].name = ("Jupiter");
		bodies[0].position.set(0, 0, 0);
		bodies[0].mass = 1.898E27;
		bodies[0].velocity.set(0, 0, 0);
		//Jupiter
	
		bodies[1].name = ("Io");
		bodies[1].position.set(4.217E8, 0, 0);
		bodies[1].mass = 8.929E22;
		bodies[1].velocity.set(0, 1.73E4, 0);
		//Io
	
		bodies[2].name = ("Europa");
		bodies[2].position.set(6.709E8, 0, 0);
		bodies[2].mass = 4.799E22;
		bodies[2].velocity.set(0, 1.374E4, 0);
		//Europa
	
		bodies[3].name = ("Ganymede");
		bodies[3].position.set(1.07E9, 0, 0);
		bodies[3].mass = 1.482E23;
		bodies[3].velocity.set(0, 1.08E4, 0);
		//Ganymede
	
		bodies[4].name = ("Callisto");
		bodies[4].position.set(1.879E9, 0, 0);
		bodies[4].mass = 1.076E23;
		bodies[4].velocity.set(0, 8.202E3, 0);
		//Callisto

	}else if(dataSet == 2){

		static const int NUM_BODIES = 6;
			static object bodies[NUM_BODIES];

		bodies[0].name = ("Pluto");
		bodies[0].position.set(0, 0, 0); //kilometers
		bodies[0].mass = 1.305E22; //kilograms
		bodies[0].velocity.set(0, 0, 0); //meters/second
		bodies[0].acceleration.set(0, 0, 0);
		//Pluto

		bodies[1].name = ("Charon");
		bodies[1].position.set(17536, 1, 0);
		bodies[1].mass = 1.587E21;
		bodies[1].velocity.set(0, 210, 0);
		bodies[1].acceleration.set(0, 0, 0);
		//Charon
		
		bodies[2].name = ("Nix");
		bodies[2].position.set(-48694, 0, 0);
		bodies[2].mass = 4.5E16;
		bodies[2].velocity.set(0, -134, 0);
		//Nix

		bodies[3].name = ("Hydra");
		bodies[3].position.set(64738, 0, 0);
		bodies[3].mass = 4.8E16;
		bodies[3].velocity.set(0, 116, 0);
		//Hydra

		bodies[4].name = ("Kerberos");
		bodies[4].position.set(57783, 0, 0);
		bodies[4].mass = (1.6E16);
		bodies[4].velocity.set(0, 122.7, 0);
		//Kerberos

		bodies[5].name = ("Styx");
		bodies[5].position.set(42656, 0, 0);
		bodies[5].mass = 7.5E15;
		bodies[5].velocity.set(0, 122, 0);
		//Styx
		}

	for (int i = 0; i < NUM_BODIES; i++){
		xPosition.push_back(vector<double>());
		yPosition.push_back(vector<double>());
		zPosition.push_back(vector<double>());
	}

	while(elapsedTime < simulationTime){

		elapsedTime = elapsedTime + timeStep;


		for (int i = 0; i < NUM_BODIES; i++){
			bodies[i].acceleration.set(0, 0, 0);

			for (int j = 0; j < NUM_BODIES; j++){
				if (i != j){
					bodies[i].acceleration = bodies[i].acceleration + forceGravity(bodies[j], bodies[i]);
				}
			}

			bodies[i].position = 0.5 * bodies[i].acceleration * pow(timeStep, 2) + bodies[i].velocity * timeStep + bodies[i].position;
			bodies[i].velocity = bodies[i].acceleration * timeStep + bodies[i].velocity;

/*			double PlutoVelocity = bodies[0].velocity.getY();
			double CharonVelocity = bodies[1].velocity.getY();
			cout << "Pluto Velocity = " << PlutoVelocity << endl;
			cout << "Charon Velocity = " << CharonVelocity << endl;*/
		}

		for (int i = 0; i < NUM_BODIES; i++){

			xPosition[i].push_back(bodies[i].position.getX());
			yPosition[i].push_back(bodies[i].position.getY());
			zPosition[i].push_back(bodies[i].position.getZ());
		}
	}
}

//______________________________________________________________________________
//_________________________________Output File Building_________________________
//______________________________________________________________________________

void outputToFile(ofstream& fileOutput){

	extern const int NUM_BODIES;
	
	for(int i = 0; i < NUM_BODIES; i++){
	fileOutput.open(bodies[i].name);
			bodyNames.push_back(bodies[i].name);
		for(int j = 0; j < dataPoints; j++){
			fileOutput << xPosition[i][j] << " " << yPosition[i][j] << " " << zPosition[i][j]  << endl;
		}

		fileOutput.close();
	}

/*	for(uint i = 0; i < NUM_BODIES; i++){
		for(uint j = 0; j < dataPoints; j++){
			fileOutput << xPosition[i][j] << " " << yPosition[i][j] << " " << zPosition[i][j]  << endl;
		}
	}
	fileOutput << endl << endl;*/
}

void outputGnuplotFileCommands(void){

	extern const int NUM_BODIES;
	
	cout << endl << endl << endl << "Paste this into gnuplot:" << endl << endl;

string line;
  ifstream myfile ("3dplot.gnuplot");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
cout << endl << endl << endl;
  }

  else cout << "Unable to open file"; 

}

void outputGNUPlotFile(vector<string>* names){

	extern const int NUM_BODIES;
	
	ofstream gnuPlotFile;
	unsigned int color = 0;
	srand(100);


	gnuPlotFile.open("3dplot.gnuplot");
	gnuPlotFile << "splot ";
		color = rand() % 0x00FFFFFF;
		gnuPlotFile << "'" << (*names)[0] << "'" << " linetype 2 linecolor " << color << ",";
	for(int i = 1; i < NUM_BODIES; i++){
		color = rand() % 0x00FFFFFF;
		if(i == NUM_BODIES - 1){
			gnuPlotFile << "'" << (*names)[i] << "'" << " with lines linetype 1 linecolor " << color;
		} else {
			gnuPlotFile << "'" << (*names)[i] << "'" << " with lines linetype 1 linecolor " << color << ",";
		}
	}

}
//______________________________________________________________________________
//____________________________________Main Function_____________________________
//______________________________________________________________________________

int main(int argc, char** argv) {

	extern const int NUM_BODIES;
	
		positionCalculation();
		cout << "Plotting " << dataPoints << " points" << endl;
		outputToFile(fileOutput);

		for(int i = 0; i < NUM_BODIES; i++){
			xPosition[i].erase(xPosition[i].begin());
			yPosition[i].erase(yPosition[i].begin());
			zPosition[i].erase(zPosition[i].begin());
//		frames ++;
		}
//	}
	outputGNUPlotFile(&bodyNames);
	outputGnuplotFileCommands();
return 0;

}

