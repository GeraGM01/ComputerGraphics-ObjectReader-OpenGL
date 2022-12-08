#include "../include/Object.hpp"
#include <GLFW/glfw3.h>
#include "../include/Transform.hpp"


Object::Object(){};

Object::Object(string file, string tipoArchivo ,float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->tipoArchivo = tipoArchivo;

    if(tipoArchivo == ".obj"|| tipoArchivo == ".Obj" || tipoArchivo == ".OBJ") 
    {

        this->vertices = {}; //ponemos el vector de vertices en vacio
	string line;
	ifstream archivoOBJ(file);
	while(getline(archivoOBJ, line))  //mienytras obtengamos lineas del archivo obj, lo va a estar regreando en la variable string
	{
		if(line.length() > 0)
		{
			vector<string> tokens = this -> split(line, " ");
			if(tokens.size() > 0)
			{
				if(tokens[0] == "v") //sabemos que estaos tratando con un vertice, el primer elemento es una v, el segundo,terver y cuarto elemento son las coordenas x,y,z
				{
					float x = std::stof(tokens[1]);
					float y = std::stof(tokens[2]);
					float z = std::stof(tokens[3]);
					Vertex v(x,y,z);
					//v.print();
					this->vertices.push_back(v);
				}
				
				if(tokens[0] == "f")
				{
					vector<unsigned int> indices = {};
					for(unsigned int i=1; i<= tokens.size()-1; i++)
					{
						unsigned int ind = stoi(this->split(tokens[i], "/")[0])-1;
						indices.push_back(ind);
					}
					Face f(indices);
					this->faces.push_back(f);
				}
			}
			
			/*
			if(line[0]=='v' || line[0]=='f')
			{
			cout << line << endl;
			}*/
		}
	}
            //this->vertices = gettingV();
        //this->faces = gettingF();
    }
    else if(tipoArchivo == ".ply" || tipoArchivo == ".PLY" || tipoArchivo == ".Ply") 
    {

    string line;
	vector<Face> faces = {};
	vector<Vertex> vertices = {}; int a = 0;
	
	ifstream archivoOBJ(file);
	
	while(getline(archivoOBJ, line))  //mienytras obtengamos lineas del archivo, lo va a estar regreando en la variable string
	{
		a++;        
		vector<string> tokens = split(line, " ");
		if(tokens.size() > 0) //mientras haya elementos 
		{
			if(tokens[0] == "3") //sabemos que estamos tratando con una cara
			{
				a=0;
				vector<unsigned int> indices = {};
				for(unsigned int i=1; i<= tokens.size()-1; i++)
				{
					unsigned int ind = stoi(this->split(tokens[i], " ")[0]);
					indices.push_back(ind);
				}
				Face f(indices);
				faces.push_back(f);
			}
			
			if(tokens[0] == "4")
			{
				a=0;
				vector<unsigned int> indicesA = {};  //vector donde voy a ir guardando todos mis indices de las caras 
				for(unsigned int i=1; i<= tokens.size(); i++)
				{
					unsigned int ind = stoi(this->split(tokens[i], " ")[0]); //sacamos el indice
					indicesA.push_back(ind);  //lo metemos a la lista
				}
				Face f(indicesA);
				faces.push_back(f);  //se agregan todos los indices a las caras 
				
			} if(a >= 11){ double x = std::stof(tokens[0]); double y = std::stof(tokens[1]); double z = std::stof(tokens[2]); Vertex v(x,y,z); vertices.push_back(v);}
			/*
			if(line[0]=='v' || line[0]=='f')
			{
			cout << line << endl;
			}*/
		}
	}
	this->vertices = vertices;  //asignacion a los vertices
	this->faces = faces;  //asignacion a las caras
    }
    this->calculoNormal();
}

vector<string> Object::split(string str, string delim)
{
	vector<string> tokens;
	size_t prev=0, pos=0;
	do
	{
		pos = str.find(delim,prev);
		if(pos==string::npos)
			pos = str.length();
		string token = str.substr(prev,pos-prev);
		if(!token.empty())
			tokens.push_back(token);
		prev = pos + delim.length();
	} while(pos<str.length() && prev <str.length());
	return tokens;
}


void Object::load(string file,string tipoArchivo,float r,float g,float b)
{
    this->tipoArchivo = tipoArchivo;
    this->r = r;
    this->g = g;
    this->b = b;

    if(tipoArchivo == ".obj"|| tipoArchivo == ".Obj" || tipoArchivo == ".OBJ")    
    {
                this->vertices = {}; //ponemos el vector de vertices en vacio
	string line;
	ifstream archivoOBJ(file);
	while(getline(archivoOBJ, line))  //mienytras obtengamos lineas del archivo obj, lo va a estar regreando en la variable string
	{
		if(line.length() > 0)
		{
			vector<string> tokens = this -> split(line, " ");
			if(tokens.size() > 0)
			{
				if(tokens[0] == "v") //sabemos que estaos tratando con un vertice, el primer elemento es una v, el segundo,terver y cuarto elemento son las coordenas x,y,z
				{
					float x = std::stof(tokens[1]);
					float y = std::stof(tokens[2]);
					float z = std::stof(tokens[3]);
					Vertex v(x,y,z);
					//v.print();
					this->vertices.push_back(v);
				}
				
				if(tokens[0] == "f")
				{
					vector<unsigned int> indices = {};
					for(unsigned int i=1; i<= tokens.size()-1; i++)
					{
						unsigned int ind = stoi(this->split(tokens[i], "/")[0])-1;
						indices.push_back(ind);
					}
					
					
					
					Face f(indices);
					this->faces.push_back(f);
				}
			}
			
			/*
			if(line[0]=='v' || line[0]=='f')
			{
			cout << line << endl;
			}*/
		}
	}
    }
    else if(tipoArchivo == ".ply" || tipoArchivo == ".Ply" || tipoArchivo == ".PLY") 
    {
                string line;
	vector<Face> faces = {};
	vector<Vertex> vertices = {}; int a = 0;
	
	ifstream archivoOBJ(file);
	
	while(getline(archivoOBJ, line))  //mienytras obtengamos lineas del archivo, lo va a estar regreando en la variable string
	{
		a++;        
		vector<string> tokens = split(line, " ");
		if(tokens.size() > 0) //mientras haya elementos 
		{
			if(tokens[0] == "3") //sabemos que estamos tratando con una cara
			{
				a=0;
				vector<unsigned int> indices = {};
				for(unsigned int i=1; i<= tokens.size()-1; i++)
				{
					unsigned int ind = stoi(this->split(tokens[i], " ")[0]);
					indices.push_back(ind);
				}
				Face f(indices);
				faces.push_back(f);
			}
			
			if(tokens[0] == "4")
			{
				a=0;
				vector<unsigned int> indicesA = {};  //vector donde voy a ir guardando todos mis indices de las caras 
				for(unsigned int i=1; i<= tokens.size(); i++)
				{
					unsigned int ind = stoi(this->split(tokens[i], " ")[0]); //sacamos el indice
					indicesA.push_back(ind);  //lo metemos a la lista
				}
				Face f(indicesA);
				faces.push_back(f);  //se agregan todos los indices a las caras 
				
			} if(a >= 11){ double x = std::stof(tokens[0]); double y = std::stof(tokens[1]); double z = std::stof(tokens[2]); Vertex v(x,y,z); vertices.push_back(v);}
			/*
			if(line[0]=='v' || line[0]=='f')
			{
			cout << line << endl;
			}*/
		}
	}
	this->vertices = vertices;  //asignacion a los vertices
	this->faces = faces;  //asignacion a las caras
    }
    this->calculoNormal();
}

void Object::draw(arma::Mat<double> MC){
    double i=1.0;
    glBegin(GL_TRIANGLES);
        for(Face f: this->faces){
            glColor3f(this->r*i,this->g*i,this->b*i);
            for(unsigned int index: f.getIndices_Vertices()){
                arma::Col<double> vp = MC * this->vertices[index].h();
                glVertex3f(vp[0]/vp[3],vp[1]/vp[3],vp[2]/vp[3]);
            }
            i = i- (1.0/this->faces.size());
        }
    glEnd();
}


vector<Face> Object::get_Faces()
{
    return this->faces;
}

vector<Vertex> Object::get_vertices()
{
    return this->vertices;
}

void Object::calculoNormal(){
    for(Face f: this->faces)
        f.vectorNormal(this->vertices);
}
