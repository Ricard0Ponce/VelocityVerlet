//
// Created by rich on 25/10/24.
//

#include "Sim.h"
#include "math.h"
#include "Atomo.h"

Sim::Sim()
{

}

// Esto es un destructor que libera memoria
Sim::~Sim()
{

}


int Sim::prin()
{
    cout << endl;
    cout << "Sim::prin " << endl;
    Datos();
    EscribirDatos();
    IniciarAtomos();
    //EscribirDatos();
    //EscribirPosVel();
    Simulacion();
    Aceleraciones();
    double pp;
    return 0;
}

void Sim::Datos()
{
    cout << endl;
    cout << "Sim::Datos" << endl;

     temp = 1.0;
     dens = 0.65;

    na = 216; // Numero de atomos
    nd = 3; // Numero de dimensiones
    nc = 100; // Numero de configuraciones

    dt = 0.01; // Delta de tiempo
    d= 1.0;
    L = pow((na/ dens),1.0/nd);
    r = d / 2.0;
    rc = 3.0;
    v0 = 1;

    ncp =10;// Numero de configuraciones parciales
    nci = nc / ncp;

    //p[100][100], v[100][100]; // Matrices
}


void Sim :: EscribirDatos() {

    cout << endl;
    cout << "Sim::EscribirDatos " << endl;

    // Escribir datos iniciales
    cout << endl;
    cout << "Datos iniciales" << endl;
    cout << "na,nd,nc " << na << " "
                        << nd << " "
                        << nc << endl;

    cout << "temp,dens " << temp << " "
                        << dens << endl;

    cout << "dt,L,d,r " << dt << " "
                    << L << " "
                    << d << " "
                        << r << endl;

    cout << "v0 rc" << v0 << " "
                << rc << endl;
    cout << "ncp,nci " << ncp << " " << nci << endl;

}

void Sim::IniciarAtomos() {
    cout << endl;
    cout << "Sim::IniciarAtomos " << endl;

    double pv[3]; // Vector de 3 dimensiones que funciona como auxiliar

    // Definir los objetos atomos
    for(int ia=0; ia < na; ia ++ ) {
        Atomo *att = new Atomo;
        atomos.push_back(att);
    }
    int an = atomos.size();
    cout << "an " << an << endl;

    // Iniciar posiciones y velocidades al azar.
    for(int ia = 0; ia < na; ia ++ ) {
        for(int id = 0; id < nd; id++ ) {
            pv[id] = rand() % 10000 / 10000.;
            // atomos[ia] -> p[id] = pv[id];
            atomos[ia] -> p.push_back(pv[id]);
        }
    }

    for(int ia = 0; ia < na; ia ++ ) {
        for(int id = 0; id < nd; id++ ) {
            double r = rand() % 10000 / 10000.;
            r = (r * 2.0) - 1;
            pv[id] = v0 * r;
            // atomos[ia] -> v[id] = pv[id];
            atomos[ia] -> v.push_back(pv[id]);
        }
    }
}

void Sim::EscribirPosVel() {
    cout << endl;
    cout << "Sim::EscribirPosVel " << endl;

    //Escribir posiciones y velocidades iniciales

    cout << endl;
    cout << "Posiciones y velocidades iniciales" << endl;
    for(int ia=0; ia < na; ia ++ ) {
        cout << "ia " << ia << endl;
        for(int id = 0; id < nd; id ++ ) {
            double pi = atomos[ia] -> p[id];
            cout << pi << " " << endl;
        }
        for (int id = 0; id < nd; id++ ) {
            double vi = atomos[ia] -> v[id];
            cout << vi << " ";
        }
        cout << endl;
    }
}

void Sim ::Simulacion() {
    cout << endl;
    cout << "Sim::Simulacion " << endl;

    double pp;

    // SImulacion
    // Ciclo de configuraciones
    for (int ic = 0; ic < nc; ic++) {
        // Ciclo de los atomos
        for(int ia = 0; ia < na; ia ++) {
            // Ciclo de las dimensiones
            for(int id = 0; id < nd; id ++ ) {
                pp = atomos[ia] -> p[id] +
                    dt * atomos[ia] -> v[id] + dt * dt * atomos[ia] -> a[id] * 0.5;

                if(pp > L) pp = pp - L;
                if(pp < 0) pp = pp + L;
                atomos[ia] -> p[id] = pp; // Se desplazan los atomos
            }
            //Ciclo de las dimensiones
        }
        //Ciclo de los atomos
        if(ic % nci == 0) {
            cout << "ic,ia" << ic << " " << "1" << " "
            << atomos[0] ->p[0] << " "
            << atomos[0] ->p[1] << " "
            << atomos[0] ->p[2] << " " << endl;
        }
    }
    //Ciclo de las configuraciones
}

void Sim::Aceleraciones() {
    cout << endl;
    cout << "Sim::Aceleraciones " << endl;

    for (int ia = 0; ia < na; ia++) {
        for (int id = 0; id < nd; id++) {
            atomos[ia] -> a[id] = 0.0;
        }
    }

    double u=0;

    for (int ia = 0; ia < na - 1; ia++) {
        for (int ja = ia+1; ja < na; ja++) {
            double r = Dist(ia,ja); // Se calculo la distancia
            u = u + LJ(r);

        for(int id = 0; id < nd; id++) {
            atomos[ia] -> a[id] =
                atomos[ia] -> a[id] + f * dis[id] / r ; // Cuidado aquí con la f
            atomos[ja] -> a[id] =
                atomos[ja] -> a[id]- f * dis[id] / r ;
        }
        }
    }
}

double Sim::LJ(double r) {
    cout << endl;
    cout << "Sim::LJ " << endl;
   // double ri = 1.0 / r;
    //double r3 = ri * ri * ri;
    //double r6 = r3*r3;

    double u = 4.0 *
        (pow((1.0/r),12 ) -
            pow((1.0 / r),6));

    double f = u = 4.0 *
        (2.0 * pow((1.0/r),12 )-
            pow((1.0 / r),6))/r;


    return (u);

}

double Sim:: Dist (int i, int j) {
    cout << endl;
    cout << "Sim::Dist " << endl;
    double r;

    for(int id = 0; id < nd; id++) {
        dis[id] = atomos[i] -> p[id] -
            atomos[j] -> p[id];
        // Condiciones periodicas
        if(fabs(dis [id]) > L / 2) {
            dis[id] = dis[id] -
                fabs(dis[id]) * L;
        }

       r = r + dis[id] * dis[id];
    }
    r = sqrt(r);

    return (r);



}


