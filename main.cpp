#include <iostream>
#include <vector>
using namespace std;

struct node {
  node(char name_1, vector<int> &distV_) {
    name = name_1;
    distV = distV_;
  }
  bool visited = false;
  vector<node *> otherN;
  vector<int> distV;
  char name;
};

vector<vector<char>> kruskalF(vector<node *> nGeneral, int nodoInit) {
  node *startN = nGeneral[nodoInit];
  startN->visited = true;
  int distMin;
  vector<vector<char>> Rt = {};
  vector<node *> listN = {startN};
  int ci = 0;
  int cj = 0;
  while (true) {
    vector<char> resultStep = {};
    distMin = 100;
    for (int j = 0; j < listN.size(); j++) {
      for (int i = 0; i < listN[j]->otherN.size(); i++) {
        if (listN[j]->distV[i] < distMin) {
          if (!listN[j]->otherN[i]->visited) {
            distMin = listN[j]->distV[i];
            ci = i;
            cj = j;
          }
        }
      }
    }
    node *nodoSec = listN[cj]->otherN[ci];
    nodoSec->visited = true;
    listN.push_back(nodoSec);
    resultStep.push_back(listN[cj]->name);
    resultStep.push_back(nodoSec->name);
    Rt.push_back(resultStep);
    if (listN.size() == nGeneral.size()) {
      break;
    }
  }
  return Rt;
}

int main() {
  vector<node *> nodosG;
  vector<vector<char>> conectionS = {{'B', 'D'},                // A
                                     {'A', 'C', 'D', 'E'},      // B
                                     {'B', 'E'},                // C
                                     {'A', 'B', 'E', 'F'},      // D
                                     {'B', 'F', 'C', 'D', 'G'}, // E
                                     {'D', 'E', 'G'},           // F
                                     {'F', 'E'}};               // G

  vector<vector<int>> distVr = {{7, 5},        {7, 8, 9, 7},     {8, 5},
                                {5, 9, 15, 6}, {7, 8, 5, 15, 9}, {6, 8, 11},
                                {11, 9}};
  vector<char> nameN = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  // Creamos nodos
  for (int i = 0; i < nameN.size(); i++) {
    nodosG.push_back(new node(nameN[i], distVr[i]));
  }
  // Conexiones
  for (int i = 0; i < conectionS.size(); i++) {
    for (int j = 0; j < conectionS[i].size(); j++) {
      for (int k = 0; k < nodosG.size(); k++) {
        if (nodosG[k]->name == conectionS[i][j]) {
          nodosG[i]->otherN.push_back(nodosG[k]);
        }
      }
    }
  }

  int nodoInit = 0;
  vector<vector<char>> valorR = kruskalF(nodosG, nodoInit);
  for (int i = 0; i < valorR.size(); i++) {
    cout << "(" << valorR[i][0] << " -> " << valorR[i][1] << ")";
  }
  return 0;
}
