#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

//initialisation du mersenne twister
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);

const int size = 29;
//influence de la visibilité
const int infVisi = 2;
//Influence des phéromones
const int infPhero = 1;
//taux d'avopration des phéromones
const float tEvap = 0.5;

double distances [] [size] = {
    {0, 97, 165, 260, 259, 303, 1330, 1450, 1370, 1270, 1970, 2340, 2640, 2120, 1750, 1960, 1840, 1600, 1470, 1470, 1260, 1270, 1100, 980, 642, 476, 540, 481, 439},
    {97, 0, 81, 262, 199, 246, 1230, 1480, 1400, 1300, 2010, 2360, 2670, 2130, 1780, 1970, 1860, 1570, 1450, 1450, 1250, 1260, 1100, 941, 612, 408, 456, 406, 409},
    {165, 81, 0, 204, 126, 165, 1180, 1430, 1360, 1290, 1970, 2340, 2630, 2090, 1750, 194, 1820, 1550, 1390, 1390, 1190, 1190, 1030, 845, 535, 318, 378, 330, 449},
    {260, 262, 204, 0, 120, 121, 1010, 1260, 1170, 1100, 1790, 2140, 2450, 1920, 1560, 1750, 1630, 1370, 1230, 1230, 1030, 1030, 870, 752, 407, 362, 423, 449, 640},
    {259, 199, 126, 120, 0, 50, 1070, 1350, 1270, 1210, 1870, 2240, 2540, 1990, 1660, 1840, 1710, 1460, 1270, 1270, 1070, 1080, 909, 734, 421, 255, 310, 332, 566},
    {303, 246, 165, 121, 50, 0, 1070, 1350, 1270, 1210, 1870, 2240, 2540, 1990, 1660, 1840, 1710, 1460, 1270, 1270, 1070, 1080, 909, 734, 421, 255, 310, 332, 566},
    {1330, 1230, 1180, 1010, 1070, 1070, 0, 396, 342, 534, 835, 1170, 1500, 913, 664, 776, 649, 368, 338, 338, 243, 201, 282, 713, 717, 1140, 1150, 1320, 1640},
    {1450, 1480, 1430, 1260, 1350, 1350, 396, 0, 87, 314, 522, 889, 1180, 693, 288, 409, 358, 344, 622, 622, 631, 605, 685, 1110, 1060, 1470, 1490, 1630, 1890},
    {1370, 1400, 1360, 1170, 1270, 1270, 342, 87, 0, 278, 601, 982, 1260, 757, 380, 583, 487, 372, 593, 593, 572, 534, 616, 1030, 967, 1390, 1410, 1560, 1800},
    {1270, 1300, 1290, 1100, 1210, 1210, 534, 314, 278, 0, 768, 1140, 1390, 962, 530, 790, 719, 640, 844, 844, 771, 735, 768, 1140, 989, 1370, 1390, 1520, 1700},
    {1970, 2010, 1970, 1790, 1870, 1870, 835, 522, 601, 768, 0, 345, 657, 231, 242, 132, 218, 522, 886, 886, 997, 955, 1110, 1540, 1550, 1980, 1990, 2140, 2420},
    {2340, 2360, 2340, 2140, 2240, 2240, 1170, 889, 982, 1140, 345, 0, 345, 263, 606, 390, 502, 812, 1130, 1130, 1280, 1240, 1410, 1820, 1880, 2310, 2320, 2480, 2760},
    {2640, 2670, 2630, 2450, 2540, 2540, 1500, 1180, 1260, 1390, 657, 345, 0, 594, 880, 719, 833, 1130, 1480, 1480, 1620, 1580, 1740, 2160, 2210, 2630, 2640, 2810, 3070},
    {2120, 2130, 2090, 1920, 1990, 1990, 913, 693, 757, 962, 231, 263, 594, 0, 444, 170, 272, 555, 871, 871, 1020, 989, 1150, 1560, 1630, 2060, 2060, 2230, 2550},
    {1750, 1780, 1750, 1560, 1660, 1660, 664, 288, 380, 530, 242, 606, 880, 444, 0, 280, 237, 427, 786, 786, 848, 811, 941, 1370, 1350, 1770, 1780, 1930, 2180},
    {1960, 1970, 194, 1750, 1840, 1840, 776, 409, 583, 790, 132, 390, 719, 170, 280, 0, 120, 432, 781, 781, 901, 871, 1030, 1450, 1500, 1910, 1930, 2080, 2380},
    {1840, 1860, 1820, 1630, 1710, 1710, 649, 358, 487, 719, 218, 502, 833, 272, 237, 120, 0, 301, 667, 667, 785, 752, 905, 1320, 1370, 1790, 1790, 1960, 2260},
    {1600, 1570, 1550, 1370, 1460, 1460, 368, 344, 372, 640, 522, 812, 1130, 555, 427, 432, 301, 0, 374, 374, 493, 455, 613, 1030, 1090, 1520, 1520, 1700, 2020},
    {1470, 1450, 1390, 1230, 1270, 1270, 338, 622, 593, 844, 886, 1130, 1480, 871, 786, 781, 667, 374, 0, 0, 210, 204, 360, 711, 855, 1270, 1270, 1440, 1840},
    {1470, 1450, 1390, 1230, 1270, 1270, 338, 622, 593, 844, 886, 1130, 1480, 871, 786, 781, 667, 374, 0, 0, 210, 204, 360, 711, 855, 1270, 1270, 1440, 1840},
    {1260, 1250, 1190, 1030, 1070, 1070, 243, 631, 572, 771, 997, 1280, 1620, 1020, 848, 901, 785, 493, 210, 210, 0, 43, 157, 542, 666, 1080, 1070, 1260, 1640},
    {1270, 1260, 1190, 1030, 1080, 1080, 201, 605, 534, 735, 955, 1240, 1580, 989, 811, 871, 752, 455, 204, 204, 43, 0, 160, 575, 671, 1090, 1100, 1270, 1650},
    {1100, 1100, 1030, 870, 909, 909, 282, 685, 616, 768, 1110, 1410, 1740, 1150, 941, 1030, 905, 613, 360, 360, 157, 160, 0, 426, 506, 925, 931, 1100, 1490},
    {980, 941, 845, 752, 734, 734, 713, 1110, 1030, 1140, 1540, 1820, 2160, 1560, 1370, 1450, 1320, 1030, 711, 711, 542, 575, 426, 0, 351, 636, 613, 799, 1250},
    {642, 612, 535, 407, 421, 421, 717, 1060, 967, 989, 1550, 1880, 2210, 1630, 1350, 1500, 1370, 1090, 855, 855, 666, 671, 506, 351, 0, 431, 434, 596, 985},
    {476, 408, 318, 362, 255, 255, 1140, 1470, 1390, 1370, 1980, 2310, 2630, 2060, 1770, 1910, 1790, 1520, 1270, 1270, 1080, 1090, 925, 636, 431, 0, 58, 178, 635},
    {540, 456, 378, 423, 310, 310, 1150, 1490, 1410, 1390, 1990, 2320, 2640, 2060, 1780, 1930, 1790, 1520, 1270, 1270, 1070, 1100, 931, 613, 434, 58, 0, 175, 658},
    {481, 406, 330, 449, 332, 332, 1320, 1630, 1560, 1520, 2140, 2480, 2810, 2230, 1930, 2080, 1960, 1700, 1440, 1440, 1260, 1270, 1100, 799, 596, 178, 175, 0, 492},
    {439, 409, 449, 640, 566, 566, 1640, 1890, 1800, 1700, 2420, 2760, 3070, 2550, 2180, 2380, 2260, 2020, 1840, 1840, 1640, 1650, 1490, 1250, 985, 635, 658, 492, 0}
};

int RWS(double* regle, vector<int> remainingCities){
    
    bool citiesVisited = true;
    int j;

    double random = mt_rand()%1000;
    j = 0;
    while(random > 0){
        random-=regle[remainingCities.at(j)]*1000;
        if(random > 0){
            j++;
        }
    }

    return remainingCities.at(j);
}

int main() {
    int depart=100;
    int nbFourmis = 0;
    while(depart>28 || depart<0){
        cout << "Point de depart (0-28) : ";
        cin >> depart;
    }
    cout << "Nombre de fourmis ? : ";
    cin >> nbFourmis;
    //stock l'itinéraire des fourmis
    vector<int> pathFourmis;
    //tableau contenant les phéromones
    double pheromones[size] [size];
    //Initualisation du tableau avec des 1;
    for(int i=0;i<size;i++){
        for(int j=0;j<size; j++){
            pheromones [i] [j] = 1;
        }
    }
    //tableau des villes visitées 
    bool visitedCities[size];
    //initialisation du talbeau sur false
    for(int i=0; i<size; i++){
        visitedCities[i] = false;
    }

    int incr = 0;
    int currentCity = depart;
    //liste des villes restantes (car sinon roue biaisé tourne en boucle avec juste le tableau des true/false)
    vector<int> remainingCities = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};

    while(incr < nbFourmis){
                
        bool allCitiesVisited = false;

        //initialisation des pheromones déposée par la fourmis actuelle
        double pheromonesFourmis [size] [size];
        for(int i=0;i<size;i++){
            for(int j=0;j<size; j++){
                pheromonesFourmis [i] [j] = 0;
            }
        }

        //nettoyage du tableau contenant l'itinéraire de la fourmis
        pathFourmis.clear();

        //tant que toutes les villes ne sont pas visitées on continue avec la fourmis
        while(!allCitiesVisited){
            pathFourmis.push_back(currentCity);

            //on mar que la ville comme visité
            visitedCities[currentCity] = true;
            for(int i=0; i<remainingCities.size(); i++){
                if(remainingCities.at(i)==currentCity){
                    remainingCities.erase(remainingCities.begin()+i);
                }
            }

            //si la somme est égale à 0 alors toutes les villes on étée visitée
            if(remainingCities.size()==0){
                allCitiesVisited = true;
            }
            //si toutes les villes ne sont pas visitées, la fourmis continue
            if(!allCitiesVisited){
                //somme des arrête pondérée 
                double somme=0;
                for(int i=0; i<size; i++){
                    if(!visitedCities[i]){
                        somme+=(pow(pheromones[currentCity] [i], infPhero)*pow(1/distances[currentCity][i], infVisi));
                    }
                }
                //tableau contenant les resultats de la régle aléatoire de transition proportionelle
                double regle[size];
                //on calculte les régles pour chaque villes. à noter que la somme des régles fait 1 (probabilité oblige)
                for(int i=0; i<size; i++){
                    if(!visitedCities[i]){
                        regle[i] = (pow(pheromones[currentCity] [i], infPhero)*pow(1/distances[currentCity][i], infVisi))/somme;
                    }else{
                        regle[i]=0;
                    }
                }

                int nextCity = RWS(regle, remainingCities);

                pheromonesFourmis[currentCity] [nextCity] += infPhero/(distances[currentCity] [nextCity]);

                currentCity = nextCity;

            }else{
                remainingCities.clear();
                remainingCities = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};

                //réinitialisation du tableau des villes visitées
                for(int i=0; i<size; i++){
                    visitedCities[i] = false;
                }
                //on évapore les phéromones précédentes
                for(int i=0;i<size;i++){
                    for(int j=0;j<size; j++){
                        pheromones [i] [j] *= tEvap;
                    }
                }
                //on ajoute les phéromes de la fourmis au autres phéromones précédement déposées
                for(int i=0;i<size;i++){
                    for(int j=0;j<size; j++){
                        pheromones [i] [j] += pheromonesFourmis[i] [j];
                    }
                }                
            }
        }

        ///////////////////////
        incr++;
        //cout << "Itération n°" << incr << endl;
    }

    cout << "Itinéraire optimal" << endl;
    //à la fin de l'algorithme on affiche le chemin parcouru par la dernière fourmis
    for(int i=0; i<pathFourmis.size(); i++){
        if(i == pathFourmis.size()-1){
            cout << pathFourmis.at(i) << endl;
        }else{
            cout << pathFourmis.at(i) << " -> ";
        }
    }
    /*
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout << pheromones[i] [j] << " - ";
        }
        cout << endl;
    }*/

    return 0;
}
